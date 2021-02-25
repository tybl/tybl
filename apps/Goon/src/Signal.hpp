// CC0 Public Domain: http://creativecommons.org/publicdomain/zero/1.0/
// Pulled from https://testbit.eu/~timj/blogstuff/simplesignal.cc
#ifndef SIMPLE_SIGNALS_CPP
#define SIMPLE_SIGNALS_CPP

#include <cassert>
#include <cstdint>
#include <ctime>
#include <functional>
#include <vector>

#include <unistd.h>

namespace Simple {

   namespace Lib {

      /// ProtoSignal is the template implementation for callback list.
      template<typename,typename> class ProtoSignal;   // undefined

      /// CollectorInvocation invokes signal handlers differently depending on return type.
      template<typename,typename> struct CollectorInvocation;

      /// CollectorLast returns the result of the last signal handler from a signal emission.
      template<typename Result>
      struct CollectorLast {
         typedef Result CollectorResult;

         explicit CollectorLast (void)
            : mLast()
         {
            // Intentionally left blank
         }

         inline bool operator() (Result r) {
            mLast = r;
            return true;
         }

         CollectorResult result(void) {
            return mLast;
         }
      private:
         Result mLast;
      };

      /// CollectorDefault implements the default signal handler collection behaviour.
      template<typename Result>
      struct CollectorDefault
         : CollectorLast<Result>
      {
         // Intentionally left blank
      };

      /// CollectorDefault specialisation for signals with void return type.
      template<>
      struct CollectorDefault<void> {
         typedef void CollectorResult;

         void result(void) { }

         inline bool operator() (void) {
            return true;
         }
      };

      /// CollectorInvocation specialisation for regular signals.
      template<class Collector, class R, class... Args>
      struct CollectorInvocation<Collector, R(Args...)> {
         inline bool invoke(Collector &collector, const std::function<R (Args...)> &cbf, Args... args) {
            return collector(cbf(args...));
         }
      };

      /// CollectorInvocation specialisation for signals with void return type.
      template<class Collector, class... Args>
      struct CollectorInvocation<Collector, void (Args...)> {
         inline bool invoke(Collector &collector, const std::function<void (Args...)> &cbf, Args... args) {
            cbf(args...);
            return collector();
         }
      };

      /// ProtoSignal template specialised for the callback signature and collector.
      template<class Collector, class R, class... Args>
      class ProtoSignal<R (Args...), Collector>
         : private CollectorInvocation<Collector, R (Args...)> {
      protected:
         typedef std::function<R (Args...)> CbFunction;
         typedef typename CbFunction::result_type Result;
         typedef typename Collector::CollectorResult CollectorResult;
      private:
         /// SignalLink implements a doubly-linked ring with ref-counted nodes containing the signal handlers.
         struct SignalLink {
            SignalLink *mNext;
            SignalLink *mPrev;
            CbFunction mFunction;
            int mReferenceCount;

            explicit SignalLink(const CbFunction &cbf)
               : mNext(NULL),
               mPrev(NULL),
               mFunction(cbf),
               mReferenceCount(1)
            {
               //Intentionally left blank
            }

            ~SignalLink (void) {
               assert(mReferenceCount == 0);
            }

            void IncrementReference(void) {
               mReferenceCount += 1;
               assert(mReferenceCount > 0);
            }

            void DecrementReference(void) {
               mReferenceCount -= 1;
               if (!mReferenceCount) {
                  delete this;
               } else {
                  assert(mReferenceCount > 0);
               }
            }

            void Unlink(void) {
               mFunction = NULL;
               if (mNext) {
                  mNext->mPrev = mPrev;
               }
               if (mPrev) {
                  mPrev->mNext = mNext;
               }
               DecrementReference();
               // leave intact ->mNext, ->mPrev for stale iterators
            }

            size_t add_before(const CbFunction &cb) {
               SignalLink *link = new SignalLink (cb);
               link->mPrev = mPrev; // link to last
               link->mNext = this;
               mPrev->mNext = link; // link from last
               mPrev = link;
               static_assert(sizeof (link) == sizeof (size_t), "sizeof size_t");
               return size_t (link);
            }

            bool deactivate(const CbFunction &cbf) {
               if (cbf == mFunction) {
                  mFunction = NULL;      // deactivate static head
                  return true;
               }
               for (SignalLink *link = this->mNext ? this->mNext : this; link != this; link = link->mNext) {
                  if (cbf == link->mFunction) {
                     link->Unlink();     // deactivate and unlink sibling
                     return true;
                  }
               }
               return false;
            }

            bool remove_sibling(size_t id) {
               for (SignalLink *link = this->mNext ? this->mNext : this; link != this; link = link->mNext) {
                  if (id == size_t (link)) {
                     link->Unlink();     // deactivate and unlink sibling
                     return true;
                  }
               }
               return false;
            }
         };
         SignalLink *mCallbackRing; // linked ring of callback nodes
         ProtoSignal(const ProtoSignal&) = delete;
         ProtoSignal&  operator= (const ProtoSignal&) = delete;

         void EnsureRing(void) {
            if (!mCallbackRing) {
               mCallbackRing = new SignalLink(CbFunction()); // mReferenceCount = 1
               mCallbackRing->IncrementReference(); // mReferenceCount = 2, head of ring, can be deactivated but not removed
               mCallbackRing->mNext = mCallbackRing; // ring head initialization
               mCallbackRing->mPrev = mCallbackRing; // ring tail initialization
            }
         }
      public:
         /// ProtoSignal constructor, connects default callback if non-NULL.
         ProtoSignal(const CbFunction &method)
            : mCallbackRing (NULL)
         {
            if (method != NULL) {
               EnsureRing();
               mCallbackRing->mFunction = method;
            }
         }

         /// ProtoSignal destructor releases all resources associated with this signal.
         ~ProtoSignal(void) {
            if (mCallbackRing) {
               while (mCallbackRing->mNext != mCallbackRing) {
                  mCallbackRing->mNext->Unlink();
               }
               assert(mCallbackRing->mReferenceCount >= 2);
               mCallbackRing->DecrementReference();
               mCallbackRing->DecrementReference();
            }
         }

         /// Operator to add a new function or lambda as signal handler, returns a handler connection ID.
         size_t operator+= (const CbFunction &cb) {
            EnsureRing();
            return mCallbackRing->add_before(cb);
         }

         /// Operator to remove a signal handler through it connection ID, returns if a handler was removed.
         bool operator-= (size_t connection) {
            return mCallbackRing ? mCallbackRing->remove_sibling(connection) : false;
         }

         /// Emit a signal, i.e. invoke all its callbacks and collect return types with the Collector.
         CollectorResult Emit(Args... args) {
            Collector collector;
            if (!mCallbackRing) {
               return collector.result();
            }
            SignalLink *link = mCallbackRing;
            link->IncrementReference();
            do {
               if (link->mFunction != NULL) {
                  const bool continue_emission = this->invoke(collector, link->mFunction, args...);
                  if (!continue_emission) {
                     break;
                  }
               }
               SignalLink *old = link;
               link = old->mNext;
               link->IncrementReference();
               old->DecrementReference();
            } while (link != mCallbackRing);
            link->DecrementReference();
            return collector.result();
         } // Emit(Args... args)
      }; // class ProtoSignal<R (Args...), Collector>
   } // Lib
   // namespace Simple

   /**
    * Signal is a template type providing an interface for arbitrary callback lists.
    * A signal type needs to be declared with the function signature of its callbacks,
    * and optionally a return result collector class type.
    * Signal callbacks can be added with operator+= to a signal and removed with operator-=, using
    * a callback connection ID return by operator+= as argument.
    * The callbacks of a signal are invoked with the Emit() method and arguments according to the signature.
    * The result returned by Emit() depends on the signal collector class. By default, the result of
    * the last callback is returned from Emit(). Collectors can be implemented to accumulate callback
    * results or to halt a running emissions in correspondance to callback results.
    * The signal implementation is safe against recursion, so callbacks may be removed and
    * added during a signal emission and recursive Emit() calls are also safe.
    * The overhead of an unused signal is intentionally kept very low, around the size of a single pointer.
    * Note that the Signal template types is non-copyable.
    */
   template <typename SignalSignature, class Collector = Lib::CollectorDefault<typename std::function<SignalSignature>::result_type> >
   struct Signal /*final*/ :
       Lib::ProtoSignal<SignalSignature, Collector>
   {
      typedef Lib::ProtoSignal<SignalSignature, Collector> ProtoSignal;
      typedef typename ProtoSignal::CbFunction CbFunction;
      /// Signal constructor, supports a default callback as argument.
      Signal(const CbFunction &method = CbFunction())
         : ProtoSignal (method)
      {
         // Intentionally left blank
      }
   };

   /// This function creates a std::function by binding @a object to the member function pointer @a method.
   template<class Instance, class Class, class R, class... Args> std::function<R (Args...)>
   slot (Instance &object, R (Class::*method) (Args...)) {
      return [&object, method] (Args... args) {
         return (object .* method) (args...);
      };
   }

   /// This function creates a std::function by binding @a object to the member function pointer @a method.
   template<class Class, class R, class... Args> std::function<R (Args...)>
   slot (Class *object, R (Class::*method) (Args...)) {
      return [object, method] (Args... args) {
         return (object ->* method) (args...);
      };
   }

   /// Keep signal emissions going while all handlers return !0 (true).
   template<typename Result>
   struct CollectorUntil0 {
      typedef Result CollectorResult;
      explicit CollectorUntil0(void)
         : mResult()
      {
         // Intentionally left blank
      }

      const CollectorResult& result(void) {
         return mResult;
      }

      inline bool operator() (Result r) {
         mResult = r;
         return mResult ? true : false;
      }
   private:
      CollectorResult mResult;
   };

   /// Keep signal emissions going while all handlers return 0 (false).
   template<typename Result>
   struct CollectorWhile0 {
      typedef Result CollectorResult;

      explicit CollectorWhile0(void)
         : mResult()
      {
         // Intentionally left blank
      }

      const CollectorResult& result(void) {
         return mResult;
      }

      inline bool operator() (Result r) {
         mResult = r;
         return mResult ? false : true;
      }
   private:
      CollectorResult mResult;
   };

   /// CollectorVector returns the result of the all signal handlers from a signal emission in a std::vector.
   template<typename Result>
   struct CollectorVector {
      typedef std::vector<Result> CollectorResult;

      const CollectorResult& result(void) {
         return mResult;
      }

      inline bool operator() (Result r) {
         mResult.push_back (r);
         return true;
      }
   private:
      CollectorResult mResult;
   };

} // Simple

#endif // SIMPLE_SIGNALS_CPP

#ifndef DISABLE_TESTS

#include <string>
#include <stdarg.h>

static std::string string_printf(const char *format, ...) __attribute__ ((__format__ (__printf__, 1, 2)));
static std::string string_printf(const char *format, ...) {
   std::string result;
   char *str = NULL;
   va_list args;
   va_start(args, format);
   if (vasprintf(&str, format, args) >= 0) {
      result = str;
   }
   va_end(args);
   if (str) {
      free (str);
   }
   return result;
}

static int64_t timestamp_benchmark(void) {
   struct timespec tp = { 0, 0 };
   if (__builtin_expect(clock_gettime (CLOCK_MONOTONIC, &tp) < 0, 0)) {
      perror("failed in clock_gettime");
      exit(-1);
   }
   int64_t stamp = (tp.tv_sec * 1000000000LL) + tp.tv_nsec;
   return stamp;
}

struct TestCounter {
   static uint64_t get(void);
   static void set(uint64_t);
   static void add2(void*, uint64_t);
};

namespace { // Anon
   void (*test_counter_add2)(void*, uint64_t) = TestCounter::add2; // external symbol to prevent easy inlining
   static uint64_t test_counter_var = 0;
} // Anon

class BasicSignalTests {
   static std::string accu;

   struct Foo {
      char foo_bool (float f, int i, std::string s) {
         accu += string_printf("Foo: %.2f\n", f + i + s.size());
         return true;
      }
   };

   static char float_callback(float f, int, std::string) {
      accu += string_printf("float: %.2f\n", f);
      return 0;
   }
public:
  static void run(void) {
     accu = "";
     Simple::Signal<char (float, int, std::string)> sig1;
     size_t id1 = sig1 += float_callback;
     size_t id2 = sig1 += [] (float, int i, std::string) {
        accu += string_printf("int: %d\n", i);
        return 0;
     };
     size_t id3 = sig1 += [] (float, int, const std::string &s) {
        accu += string_printf("string: %s\n", s.c_str());
        return 0;
     };
     sig1.Emit(.3, 4, "huhu");
     bool success;
     success = sig1 -= id1;
     assert(success == true);
     success = sig1 -= id1;
     assert(success == false);
     success = sig1 -= id2;
     assert(success == true);
     success = sig1 -= id3;
     assert(success == true);
     success = sig1 -= id3;
     assert(success == false);
     success = sig1 -= id2;
     assert(success == false);
     Foo foo;
     sig1 += Simple::slot(foo, &Foo::foo_bool);
     sig1 += Simple::slot(&foo, &Foo::foo_bool);
     sig1.Emit(.5, 1, "12");

     Simple::Signal<void (std::string, int)> sig2;
     sig2 += [] (std::string msg, int) {
        accu += string_printf("msg: %s", msg.c_str());
     };
     sig2 += [] (std::string, int d) {
        accu += string_printf(" *%d*\n", d);
     };
     sig2.Emit("in sig2", 17);

     accu += "DONE";

     const char *expected =
        "float: 0.30\n"
        "int: 4\n"
        "string: huhu\n"
        "Foo: 3.50\n"
        "Foo: 3.50\n"
        "msg: in sig2 *17*\n"
        "DONE";
     assert (accu == expected);
  }
};
std::string BasicSignalTests::accu;


class TestCollectorVector {
   static int handler1(void) {
      return 1;
   }

   static int handler42(void) {
      return 42;
   }

   static int handler777(void) {
      return 777;
   }
public:
   static void run(void) {
     Simple::Signal<int (), Simple::CollectorVector<int>> sig_vector;
     sig_vector += handler777;
     sig_vector += handler42;
     sig_vector += handler1;
     sig_vector += handler42;
     sig_vector += handler777;
     std::vector<int> results = sig_vector.Emit();
     const std::vector<int> reference = { 777, 42, 1, 42, 777, };
     assert(results == reference);
   }
};

class TestCollectorUntil0 {
   bool check1;
   bool check2;

   TestCollectorUntil0(void)
      : check1(0),
      check2(0)
   {
      // Intentionally left blank
   }

   bool handler_true(void) {
      check1 = true;
      return true;
   }

   bool handler_false(void) {
      check2 = true;
      return false;
   }

   bool handler_abort(void) {
      abort();
   }
public:
   static void run(void) {
      TestCollectorUntil0 self;
      Simple::Signal<bool (), Simple::CollectorUntil0<bool>> sig_until0;
      sig_until0 += Simple::slot (self, &TestCollectorUntil0::handler_true);
      sig_until0 += Simple::slot (self, &TestCollectorUntil0::handler_false);
      sig_until0 += Simple::slot (self, &TestCollectorUntil0::handler_abort);
      assert(!self.check1 && !self.check2);
      const bool result = sig_until0.Emit();
      assert(!result && self.check1 && self.check2);
   }
};

class TestCollectorWhile0 {
  bool check1, check2;
  TestCollectorWhile0() : check1 (0), check2 (0) {}
  bool handler_0     ()  { check1 = true; return false; }
  bool handler_1     ()  { check2 = true; return true; }
  bool handler_abort ()  { abort(); }
  public:
  static void
  run ()
  {
     TestCollectorWhile0 self;
     Simple::Signal<bool (), Simple::CollectorWhile0<bool>> sig_while0;
     sig_while0 += Simple::slot (self, &TestCollectorWhile0::handler_0);
     sig_while0 += Simple::slot (self, &TestCollectorWhile0::handler_1);
     sig_while0 += Simple::slot (self, &TestCollectorWhile0::handler_abort);
     assert (!self.check1 && !self.check2);
     const bool result = sig_while0.Emit();
     assert(result == true && self.check1 && self.check2);
  }
};

static void bench_simple_signal() {
   Simple::Signal<void (void*, uint64_t)> sig_increment;
   sig_increment += test_counter_add2;
   const uint64_t start_counter = TestCounter::get();
   const int64_t benchstart = timestamp_benchmark();
   uint64_t i;
   for (i = 0; i < 999999; i++) {
      sig_increment.Emit(NULL, 1);
   }
   const int64_t benchdone = timestamp_benchmark();
   const uint64_t end_counter = TestCounter::get();
   assert(end_counter - start_counter == i);
   printf("OK\n  Benchmark: Simple::Signal: %fns per emission (size=%zu): ",
           size_t (benchdone - benchstart) * 1.0 / size_t (i),
           sizeof (sig_increment));
}

static void bench_callback_loop(void) {
   void (*counter_increment) (void*, uint64_t) = test_counter_add2;
   const uint64_t start_counter = TestCounter::get();
   const int64_t benchstart = timestamp_benchmark();
   uint64_t i;
   for (i = 0; i < 999999; i++) {
      counter_increment(NULL, 1);
   }
   const int64_t benchdone = timestamp_benchmark();
   const uint64_t end_counter = TestCounter::get();
   assert(end_counter - start_counter == i);
   printf("OK\n  Benchmark: callback loop: %fns per round: ", size_t (benchdone - benchstart) * 1.0 / size_t (i));
}

uint64_t TestCounter::get(void) {
   return test_counter_var;
}

void TestCounter::set(uint64_t v) {
   test_counter_var = v;
}

void TestCounter::add2(void*, uint64_t v) {
   test_counter_var += v;
}

int main (int, const char *[]) {
  printf ("Signal/Basic Tests: ");
  BasicSignalTests::run();
  printf ("OK\n");

  printf ("Signal/CollectorVector: ");
  TestCollectorVector::run();
  printf ("OK\n");

  printf ("Signal/CollectorUntil0: ");
  TestCollectorUntil0::run();
  printf ("OK\n");

  printf ("Signal/CollectorWhile0: ");
  TestCollectorWhile0::run();
  printf ("OK\n");

  printf ("Signal/Benchmark: Simple::Signal: ");
  bench_simple_signal();
  printf ("OK\n");

  printf ("Signal/Benchmark: callback loop: ");
  bench_callback_loop();
  printf ("OK\n");

  return 0;
}

#endif // DISABLE_TESTS

// g++ -Wall -O2 -std=gnu++0x -pthread simplesignal.cc -lrt && ./a.out
