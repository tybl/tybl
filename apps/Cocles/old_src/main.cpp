// License: The Unlicense (https://unlicense.org)
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "date/date.h"
#include "math/fixed_point.hpp"
#include "math/integer.hpp"
#include "ledger/identifier.hpp"

#include <algorithm>
#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <list>
#include <map>

static int run_unit_tests(int argc, const char* argv[]) {
   doctest::Context context; // initialize

   // defaults
   context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
   context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
   context.setOption("sort", "name");                // sort the test cases by their name

   context.applyCommandLine(argc, argv);

   // overrides
   context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

   int result = context.run();                       // run

   if (context.shouldExit()) {          // important !! query flags (and --exit) rely on the user doing this
      exit(result);                                  // propagate the result of the tests
   }
   return result;
}

template <typename TYPE>
struct table_column_t {

   struct value_type {
      std::size_t index;
      TYPE value;
   };

   std::size_t size() const {
      return m_data.size();
   }

   void push_back(value_type&& value) {
      std::sort(m_data.begin(), m_data.end(), index_cmp);
      auto iter = std::lower_bound(m_data.begin(), m_data.end(), value, index_cmp);
      if ((m_data.end() == iter) || (iter->index != value.index)) {
         m_data.insert(iter, value);
      }
   }

   const TYPE& value_at(std::size_t index) {
      std::sort(m_data.begin(), m_data.end(), index_cmp);
      auto iter = std::lower_bound(m_data.begin(), m_data.end(), index, lb_index_cmp);
      if ((m_data.end() == iter) || (index != iter->index)) {
         std::cerr << __LINE__ << std::endl;
         throw 0;
      }
      return iter->value;
   }

   std::size_t index_for(const TYPE& value) {
      std::sort(m_data.begin(), m_data.end(), value_cmp);
      auto iter = std::lower_bound(m_data.begin(), m_data.end(), value, lb_value_cmp);
      if ((m_data.end() == iter) || (value != iter->value)) {
         std::cerr << __LINE__ << std::endl;
         throw 0;
      }
      return iter->index;
   }

   void remove(std::size_t index) {
      std::sort(m_data.begin(), m_data.end(), index_cmp);
      auto iter = std::lower_bound(m_data.begin(), m_data.end(), index, lb_index_cmp);
      if ((m_data.end() != iter) && (index == iter->index)) {
         std::iter_swap(iter, std::prev(m_data.end()));
         m_data.erase(std::prev(m_data.end()));
      }
   }

private:

   static constexpr bool index_cmp(const value_type& a, const value_type& b) {
      return a.index < b.index;
   }

   static constexpr bool value_cmp(const value_type& a, const value_type& b) {
      return a.value < b.value;
   }

   static constexpr bool lb_index_cmp(const value_type& obj, const std::size_t& index) {
      return obj.index < index;
   }

   static constexpr bool lb_value_cmp(const value_type& obj, const TYPE& value) {
      return obj.value < value;
   }

private:
   std::vector<value_type> m_data;
};

TEST_CASE("table_column_t") {
   table_column_t<std::string> blah;
   blah.push_back({234, "Hello"});
   CHECK(blah.size() == 1);
   CHECK(blah.value_at(234) == std::string("Hello"));
   CHECK(blah.index_for("Hello") == 234);
   blah.push_back({235, "World"});
   CHECK(blah.size() == 2);
   CHECK(blah.value_at(234) == std::string("Hello"));
   CHECK(blah.index_for("Hello") == 234);
   CHECK(blah.value_at(235) == std::string("World"));
   CHECK(blah.index_for("World") == 235);
   blah.push_back({235, "Foo"});
   CHECK(blah.size() == 2);
   blah.remove(235);
   CHECK(blah.size() == 1);
   CHECK(blah.value_at(234) == std::string("Hello"));
   CHECK(blah.index_for("Hello") == 234);
}

template <typename TYPE>
struct table_t {

   using container_type = std::map<ledger::identifier_t<TYPE>, TYPE>;
   using mapped_type    = typename container_type::mapped_type;
   using key_type       = typename container_type::key_type;
   using size_type      = typename container_type::size_type;
   using value_type     = typename container_type::value_type;
   using reference      = typename container_type::reference;
   using const_reference = typename container_type::const_reference;
   using iterator       = typename container_type::iterator;
   using const_iterator = typename container_type::const_iterator;

   table_t()
      : m_max_id() {}

   key_type insert(TYPE entry) {
      key_type ret_val(++m_max_id);
      m_entries.insert(std::make_pair(ret_val, entry));
      return ret_val;
   }

   void remove(key_type key) noexcept {
      const auto count = m_entries.erase(key);
      assert(1 == count);
   }

   size_type size() const noexcept {
      return m_entries.size();
   }

   mapped_type& at(const key_type& key) {
      return m_entries.at(key);
   }

   const mapped_type& at(const key_type& key) const {
      return m_entries.at(key);
   }

   size_type count(const key_type& key) const {
      return m_entries.count(key);
   }

   iterator begin() noexcept {
      return m_entries.begin();
   }

   const_iterator cbegin() const noexcept {
      return m_entries.cbegin();
   }

   iterator end() noexcept {
      return m_entries.end();
   }

   const_iterator cend() const noexcept {
      return m_entries.cend();
   }

private:
   container_type m_entries;
   uint64_t m_max_id;
}; // struct table_t

enum class account_type_t: uint8_t {
   INCOME_EXPENSE,
   BUDGET_CATEGORY,
   BUDGETED_ACCOUNT,
   UNBUDGETED_ACCOUNT
}; // enum class account_type_t

struct account_t {

   account_t(std::string name, account_type_t type)
      : m_name(name)
      , m_type(type) {}

   const std::string& name() const noexcept {
      return m_name;
   }

   account_type_t type() const noexcept {
      return m_type;
   }

private:
   std::string m_name;
   account_type_t m_type;
}; // struct account_t

struct transaction_t {

   transaction_t(const date::year_month_day& date, const std::string& memo = "")
      : m_date(date)
      , m_memo(memo) {}

   const date::year_month_day& date() const noexcept {
      return m_date;
   }

   const std::string& memo() const noexcept {
      return m_memo;
   }

private:
   date::year_month_day m_date;
   std::string m_memo;
}; // struct transaction_t

struct adjustment_t {
   using transaction_id_t = ledger::identifier_t<transaction_t>;
   using account_id_t = ledger::identifier_t<account_t>;

   adjustment_t(transaction_id_t transaction_id, account_id_t account_id, math::fixed_point_t<std::centi> amount)
      : m_transaction_id(transaction_id)
      , m_account_id(account_id)
      , m_amount(amount) {}

   math::fixed_point_t<std::centi> amount() const {
      return m_amount;
   }

private:
   transaction_id_t m_transaction_id;
   account_id_t m_account_id;
   math::fixed_point_t<std::centi> m_amount;
}; // struct adjustment_t

struct add_adjustment_event_t {
   add_adjustment_event_t()
      : account_id(0) {}

   ledger::identifier_t<account_t> account_id;
   std::string memo;
   math::fixed_point_t<std::centi> amount;
};

namespace internal {

struct transaction_t {
   uint64_t m_id;                //  8 bytes
   std::string m_memo;           // 32 bytes
   date::sys_days m_date;        //  4 bytes
                                 // ========
                                 // 44 bytes
                                 // 48 bytes (aligned)
   // 20 bytes off of cache line (16 once padded)
};

static_assert(48 == sizeof(transaction_t), "internal::transaction_t changed size");

struct account_t {
   std::string m_memo;            // 32 bytes
   std::string m_name;            // 32 bytes
   uint64_t m_id;                 //  8 bytes
   account_type_t m_account_type; //  1 byte
                                  // ========
                                  // 73 bytes
                                  // 80 bytes (aligned)
   // 55 bytes off of cache line (48 once padded)
};

static_assert(80 == sizeof(account_t), "internal::account_t changed size");

struct adjustment_t {
   uint64_t m_id;                            //  8 bytes
   uint64_t m_account_id;                    //  8 bytes
   uint64_t m_transaction_id;                //  8 bytes
   math::fixed_point_t<std::centi> m_amount; //  8 bytes
   uint64_t m_flags; // cleared, reconciled  //  8 bytes
                                             // ========
                                             // 40 bytes
                                             // 40 bytes (aligned)
   // 24 bytes off of cache line
};

static_assert(40 == sizeof(adjustment_t), "internal::adjustment_t changed size");

struct account_table_t {

   std::size_t size() const {
      assert(m_data.size() == m_id_index.size());
      assert(m_data.size() == m_name_index.size());
      return m_data.size();
   }

#if 0
   insert(const account_t& account) {

   }
#endif

private:
   std::list<account_t> m_data;
   std::map<uint64_t, uint64_t> m_id_index;
   std::map<std::string, uint64_t> m_name_index;
};

struct transaction_table_t {
private:
   std::list<transaction_t> m_data;
   std::map<uint64_t, uint64_t> m_id_index;
   std::multimap<date::sys_days, uint64_t> m_date_index;
};

struct adjustment_table_t {
private:
   std::list<adjustment_t> m_data;
   std::map<uint64_t, uint64_t> m_id_index;
   std::multimap<uint64_t, uint64_t> m_account_id_index;
};

} // namespace internal

struct add_transaction_event_t {

   add_transaction_event_t() = default;

   add_transaction_event_t(const std::string& input) {
      deserialize(input);
   }

   void deserialize(const std::string& input) {
      std::size_t start = 0;
      std::size_t end = input.find('\t', start);
      assert(2 == std::stoi(input.substr(start, end - start)));
      start = end + 1;
      end = input.find('\t', start);
      time = std::chrono::system_clock::time_point(std::chrono::microseconds(std::stoull(input.substr(start, end - start))));

      start = end + 1;
      end = input.find('\t', start);
      date = date::sys_days(date::days(std::stoi(input.substr(start, end - start))));

      start = end + 1;
      end = input.find('\t', start);
      memo = input.substr(start, end - start);

      while (end < input.length()) {
         add_adjustment_event_t adjustment;
         start = end + 1;
         end = input.find('\t', start);
         adjustment.account_id = ledger::identifier_t<account_t>(std::stoull(input.substr(start, end - start)));
         start = end + 1;
         end = input.find('\t', start);
         adjustment.memo = input.substr(start, end - start);
         start = end + 1;
         end = input.find('\t', start);
         adjustment.amount.significand() = std::stoll(input.substr(start, end - start));
         adjustments.push_back(adjustment);
      }
   }

   std::string serialize() const {
      std::string result;
      result += std::to_string(2) + '\t';
      result += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count()) + '\t';
      result += std::to_string(date.time_since_epoch().count()) + '\t';
      result += memo;
      for (auto adj : adjustments) {
         result += '\t' + std::to_string(static_cast<uint64_t>(adj.account_id));
         result += '\t' + adj.memo;
         result += '\t' + std::to_string(adj.amount.significand());
      }
      return result;
   }

   std::chrono::system_clock::time_point time;
   date::sys_days date;
   std::string memo;
   std::vector<add_adjustment_event_t> adjustments;
};

TEST_CASE("add_transaction_event dogfood") {
   using namespace std::literals;
   //                       1          2          3         4            5
   //            0 12345678901234567 890123 456789012345678901 23 4 5678901
   auto input = "2\t1479263536123456\t17121\tStarting Balances\t1\t\t501318"s;
   add_transaction_event_t transaction(input);
   CHECK(transaction.serialize() == input);
}

struct add_account_event_t {

   add_account_event_t() = default;

   add_account_event_t(const std::string& input) {
      deserialize(input);
   }

   void deserialize(const std::string& input) {
      std::size_t start = 0;
      std::size_t end = input.find('\t', start);
      assert(1 == std::stoi(input.substr(start, end - start)));
      start = end + 1;
      end = input.find('\t', start);
      time = std::chrono::system_clock::time_point(std::chrono::microseconds(std::stoull(input.substr(start, end - start))));

      start = end + 1;
      end = input.find('\t', start);
      name = input.substr(start, end - start);

      start = end + 1;
      end = input.find('\t', start);
      type = static_cast<account_type_t>(std::stoi(input.substr(start, end - start)));
   }

   std::string serialize() const {
      return std::to_string(1) + '\t' +
             std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count()) + '\t' +
             name + '\t' +
             std::to_string(static_cast<int>(type));
   }

   std::chrono::system_clock::time_point time;
   std::string name;
   account_type_t type;
};

TEST_CASE("add_account_event dogfood") {
   using namespace std::literals;
   auto account_input = "1\t1479263530123456\tChecking\t2"s;
   add_account_event_t a(account_input);
   CHECK(a.serialize() == account_input);
}

// This class defines an object that is responsible for keeping track of the current state of the system.
// The state can be queried.
// It also keeps track of state changes in the form of a log
// During initialization, the log is read in and the actions are applied to the state of the system.
// After initialization, messages that modify the state are appended to the log
struct ledger_t {

   ledger_t(std::iostream& /*io*/)
      //: m_event_io(io)
   {

   }

   void replay_event(const add_transaction_event_t& event) {
      ledger::identifier_t<transaction_t> tid = transaction_table.insert({event.date, event.memo});
      for (auto adj : event.adjustments) {
         // TODO(tybl): throw exception if adjustment already exists
         adjustment_table.insert({tid, adj.account_id, adj.amount});
      }
   }

   void replay_event(const add_account_event_t& event) {
      account_t account(event.name, event.type);
      // TODO(tybl): throw exception if account already exists
      account_table.insert(account);
   }

   table_t<transaction_t> transaction_table;
   table_t<account_t>         account_table;
   table_t<adjustment_t>   adjustment_table;
private:
   //std::iostream& m_event_io;
};

extern "C" int main(int argc, const char* argv[]) {
   using namespace std::literals;
   int unit_test_results = run_unit_tests(argc, argv);

   std::stringstream log("1\t1479263530123456\tChecking\t2\n2\t1479263536123456\t17121\tStarting Balances\t1\t\t501318");
   ledger_t ledger(log);

   add_account_event_t account("1\t1479263530123456\tChecking\t2");
   ledger.replay_event(account);

   auto transaction_input = "2\t1479263536123456\t17121\tStarting Balances\t1\t\t501318"s;
   add_transaction_event_t e;
   e.deserialize(transaction_input);

#if 0
   auto aid001 = ledger.account_table.insert({"Credit Card", account_type_t::BUDGETED_ACCOUNT});
   auto aid002 = ledger.account_table.insert({"Groceries", account_type_t::BUDGET_CATEGORY});
   auto aid003 = ledger.account_table.insert({"Wegmans", account_type_t::INCOME_EXPENSE});
   auto tid001 = ledger.transaction_table.insert({date::year{2016}/11/14});
   ledger.adjustment_table.insert({tid001, aid001, "-20.00"});
   ledger.adjustment_table.insert({tid001, aid002, "-20.00"});
   ledger.adjustment_table.insert({tid001, aid003, "20.00"});
#endif

   std::cout << ledger.account_table.size() << std::endl;
   std::cout << ledger.adjustment_table.size() << std::endl;
   std::cout << ledger.transaction_table.size() << std::endl;

   for (const auto& pr : ledger.account_table) {
      std::cout << pr.first << ": " << pr.second.name() << std::endl;
   }

   std::cout << sizeof(internal::transaction_t) << std::endl;
   std::cout << sizeof(std::string) << std::endl;

   std::cout << "sizeof(internal::account_t): " << sizeof(internal::account_t) << std::endl;
   return unit_test_results; // the result from doctest is propagated here as well
}
