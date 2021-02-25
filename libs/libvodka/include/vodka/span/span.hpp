// Library: The Unlicense (https://unlicense.org)
#pragma once
#ifndef TYBL_VODKA_SPAN_SPAN_HPP
#define TYBL_VODKA_SPAN_SPAN_HPP

#include "vodka/array/array.hpp"
#include "vodka/type_traits/false_type.hpp"
#include "vodka/type_traits/remove_cv.hpp"
#include "vodka/type_traits/true_type.hpp"
#include "vodka/type_traits/void_t.hpp"

#include <array>        // for array
#include <cstddef>      // for byte
#include <iterator>     // for iterators
#include <limits>       // std::numeric_limits
#include <type_traits>  // for remove_cv, etc

namespace tybl::vodka {

// dynamic_extent

inline constexpr size_t dynamic_extent = std::numeric_limits<size_t>::max();

// span

template <typename Type, size_t Extent = dynamic_extent>
class span;

// is_span

template <typename Type>
struct impl_is_span
  : public false_type { };

template <typename Type, size_t Extent>
struct impl_is_span<span<Type, Extent>>
  : public true_type { };

template <typename Type>
struct is_span
  : public impl_is_span<remove_cv_t<Type>> { };

// is_std_array

template <typename _Tp>
struct __is_std_array_impl : public false_type {};

template <typename _Tp, size_t _Sz>
struct __is_std_array_impl<array<_Tp, _Sz>> : public true_type {};

template <typename _Tp>
struct __is_std_array : public __is_std_array_impl<remove_cv_t<_Tp>> {};



template <class _Tp, class _ElementType, class = void>
struct __is_span_compatible_container : public false_type {};

template <class _Tp, class _ElementType>
struct __is_span_compatible_container<_Tp, _ElementType,
        void_t<
        // is not a specialization of span
            typename enable_if<!is_span<_Tp>::value, nullptr_t>::type,
        // is not a specialization of array
            typename enable_if<!__is_std_array<_Tp>::value, nullptr_t>::type,
        // is_array_v<Container> is false,
            typename enable_if<!is_array_v<_Tp>, nullptr_t>::type,
        // data(cont) and size(cont) are well formed
            decltype(data(declval<_Tp>())),
            decltype(size(declval<_Tp>())),
        // remove_pointer_t<decltype(data(cont))>(*)[] is convertible to ElementType(*)[]
            typename enable_if<
                std::is_convertible_v<remove_pointer_t<decltype(data(declval<_Tp &>()))>(*)[],
                                 _ElementType(*)[]>,
                nullptr_t>::type
        >>
    : public true_type {};


template <typename _Tp, size_t _Extent>
class span {
public:
//  constants and types
    using element_type     = _Tp;
    using value_type       = remove_cv_t<_Tp>;
    using size_type        = size_t;
    using difference_type  = ptrdiff_t;
    using pointer          = _Tp *;
    using const_pointer    = const _Tp *;
    using reference        = _Tp &;
    using const_reference  = const _Tp &;
    using iterator         =  __wrap_iter<pointer>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    static constexpr size_type extent = _Extent;

// [span.cons], span constructors, copy, assignment, and destructor
    template <size_t _Sz = _Extent, enable_if_t<_Sz == 0, nullptr_t> = nullptr>
    inline constexpr span() noexcept : __data{nullptr} {}

    constexpr span           (const span&) noexcept = default;
    constexpr span& operator=(const span&) noexcept = default;

    inline constexpr explicit span(pointer __ptr, size_type __count) : __data{__ptr}
        { (void)__count; _LIBCPP_ASSERT(_Extent == __count, "size mismatch in span's constructor (ptr, len)"); }
    inline constexpr explicit span(pointer __f, pointer __l) : __data{__f}
        { (void)__l;     _LIBCPP_ASSERT(_Extent == distance(__f, __l), "size mismatch in span's constructor (ptr, ptr)"); }

    inline constexpr span(element_type (&__arr)[_Extent])          noexcept : __data{__arr} {}

    template <class _OtherElementType,
              enable_if_t<std::is_convertible_v<_OtherElementType(*)[], element_type (*)[]>, nullptr_t> = nullptr>
    inline
    constexpr span(array<_OtherElementType, _Extent>& __arr) noexcept : __data{__arr.data()} {}

    template <class _OtherElementType,
              enable_if_t<std::is_convertible_v<const _OtherElementType(*)[], element_type (*)[]>, nullptr_t> = nullptr>
    inline
    constexpr span(const array<_OtherElementType, _Extent>& __arr) noexcept : __data{__arr.data()} {}

    template <class _Container>
    inline
        constexpr explicit span(      _Container& __c,
            enable_if_t<__is_span_compatible_container<_Container, _Tp>::value, nullptr_t> = nullptr)
        : __data{_VSTD::data(__c)} {
            _LIBCPP_ASSERT(_Extent == _VSTD::size(__c), "size mismatch in span's constructor (range)");
        }

    template <class _Container>
    inline
        constexpr explicit span(const _Container& __c,
            enable_if_t<__is_span_compatible_container<const _Container, _Tp>::value, nullptr_t> = nullptr)
        : __data{_VSTD::data(__c)} {
            _LIBCPP_ASSERT(_Extent == _VSTD::size(__c), "size mismatch in span's constructor (range)");
        }

    template <class _OtherElementType>
    inline
        constexpr span(const span<_OtherElementType, _Extent>& __other,
                       enable_if_t<
                          std::is_convertible_v<_OtherElementType(*)[], element_type (*)[]>,
                          nullptr_t> = nullptr)
        : __data{__other.data()} {}

    template <class _OtherElementType>
    inline
        constexpr explicit span(const span<_OtherElementType, dynamic_extent>& __other,
                       enable_if_t<
                          std::is_convertible_v<_OtherElementType(*)[], element_type (*)[]>,
                          nullptr_t> = nullptr) noexcept
        : __data{__other.data()} { _LIBCPP_ASSERT(_Extent == __other.size(), "size mismatch in span's constructor (other span)"); }


//  ~span() noexcept = default;

    template <size_t _Count>
    inline
    constexpr span<element_type, _Count> first() const noexcept
    {
        static_assert(_Count <= _Extent, "Count out of range in span::first()");
        return span<element_type, _Count>{data(), _Count};
    }

    template <size_t _Count>
    inline
    constexpr span<element_type, _Count> last() const noexcept
    {
        static_assert(_Count <= _Extent, "Count out of range in span::last()");
        return span<element_type, _Count>{data() + size() - _Count, _Count};
    }

    inline
    constexpr span<element_type, dynamic_extent> first(size_type __count) const noexcept
    {
        _LIBCPP_ASSERT(__count <= size(), "Count out of range in span::first(count)");
        return {data(), __count};
    }

    inline
    constexpr span<element_type, dynamic_extent> last(size_type __count) const noexcept
    {
        _LIBCPP_ASSERT(__count <= size(), "Count out of range in span::last(count)");
        return {data() + size() - __count, __count};
    }

    template <size_t _Offset, size_t _Count = dynamic_extent>
    inline
    constexpr auto subspan() const noexcept
        -> span<element_type, _Count != dynamic_extent ? _Count : _Extent - _Offset>
    {
        static_assert(_Offset <= _Extent, "Offset out of range in span::subspan()");
        static_assert(_Count == dynamic_extent || _Count <= _Extent - _Offset, "Offset + count out of range in span::subspan()");

        using _ReturnType = span<element_type, _Count != dynamic_extent ? _Count : _Extent - _Offset>;
        return _ReturnType{data() + _Offset, _Count == dynamic_extent ? size() - _Offset : _Count};
    }


    inline
    constexpr span<element_type, dynamic_extent>
       subspan(size_type __offset, size_type __count = dynamic_extent) const noexcept
    {
        _LIBCPP_ASSERT(__offset <= size(), "Offset out of range in span::subspan(offset, count)");
        _LIBCPP_ASSERT(__count  <= size() || __count == dynamic_extent, "Count out of range in span::subspan(offset, count)");
        if (__count == dynamic_extent)
            return {data() + __offset, size() - __offset};
        _LIBCPP_ASSERT(__count <= size() - __offset, "Offset + count out of range in span::subspan(offset, count)");
        return {data() + __offset, __count};
    }

    inline constexpr size_type size()       const noexcept { return _Extent; }
    inline constexpr size_type size_bytes() const noexcept { return _Extent * sizeof(element_type); }
    inline constexpr bool empty()           const noexcept { return _Extent == 0; }

    inline constexpr reference operator[](size_type __idx) const noexcept
    {
        _LIBCPP_ASSERT(__idx < size(), "span<T,N>[] index out of bounds");
        return __data[__idx];
    }

    inline constexpr reference front() const noexcept
    {
        _LIBCPP_ASSERT(!empty(), "span<T, N>::front() on empty span");
        return __data[0];
    }

    inline constexpr reference back() const noexcept
    {
        _LIBCPP_ASSERT(!empty(), "span<T, N>::back() on empty span");
        return __data[size()-1];
    }

    inline constexpr pointer data()                         const noexcept { return __data; }

// [span.iter], span iterator support
    inline constexpr iterator                 begin() const noexcept { return iterator(data()); }
    inline constexpr iterator                   end() const noexcept { return iterator(data() + size()); }
    inline constexpr reverse_iterator        rbegin() const noexcept { return reverse_iterator(end()); }
    inline constexpr reverse_iterator          rend() const noexcept { return reverse_iterator(begin()); }

    inline span<const byte, _Extent * sizeof(element_type)> __as_bytes() const noexcept
    { return span<const byte, _Extent * sizeof(element_type)>{reinterpret_cast<const byte *>(data()), size_bytes()}; }

    inline span<byte, _Extent * sizeof(element_type)> __as_writable_bytes() const noexcept
    { return span<byte, _Extent * sizeof(element_type)>{reinterpret_cast<byte *>(data()), size_bytes()}; }

private:
    pointer    __data;
};


template <typename _Tp>
class _LIBCPP_TEMPLATE_VIS span<_Tp, dynamic_extent> {
private:

public:
//  constants and types
    using element_type           = _Tp;
    using value_type             = remove_cv_t<_Tp>;
    using size_type              = size_t;
    using difference_type        = ptrdiff_t;
    using pointer                = _Tp *;
    using const_pointer          = const _Tp *;
    using reference              = _Tp &;
    using const_reference        = const _Tp &;
    using iterator               =  __wrap_iter<pointer>;
    using reverse_iterator       = _VSTD::reverse_iterator<iterator>;

    static constexpr size_type extent = dynamic_extent;

// [span.cons], span constructors, copy, assignment, and destructor
    inline constexpr span() noexcept : __data{nullptr}, __size{0} {}

    constexpr span           (const span&) noexcept = default;
    constexpr span& operator=(const span&) noexcept = default;

    inline constexpr span(pointer __ptr, size_type __count) : __data{__ptr}, __size{__count} {}
    inline constexpr span(pointer __f, pointer __l) : __data{__f}, __size{static_cast<size_t>(distance(__f, __l))} {}

    template <size_t _Sz>
    inline
    constexpr span(element_type (&__arr)[_Sz])          noexcept : __data{__arr}, __size{_Sz} {}

    template <class _OtherElementType, size_t _Sz,
              enable_if_t<std::is_convertible_v<_OtherElementType(*)[], element_type (*)[]>, nullptr_t> = nullptr>
    inline
    constexpr span(array<_OtherElementType, _Sz>& __arr) noexcept : __data{__arr.data()}, __size{_Sz} {}

    template <class _OtherElementType, size_t _Sz,
              enable_if_t<std::is_convertible_v<const _OtherElementType(*)[], element_type (*)[]>, nullptr_t> = nullptr>
    inline
    constexpr span(const array<_OtherElementType, _Sz>& __arr) noexcept : __data{__arr.data()}, __size{_Sz} {}

    template <class _Container>
    inline
        constexpr span(      _Container& __c,
            enable_if_t<__is_span_compatible_container<_Container, _Tp>::value, nullptr_t> = nullptr)
        : __data{_VSTD::data(__c)}, __size{(size_type) _VSTD::size(__c)} {}

    template <class _Container>
    inline
        constexpr span(const _Container& __c,
            enable_if_t<__is_span_compatible_container<const _Container, _Tp>::value, nullptr_t> = nullptr)
        : __data{_VSTD::data(__c)}, __size{(size_type) _VSTD::size(__c)} {}


    template <class _OtherElementType, size_t _OtherExtent>
    inline
        constexpr span(const span<_OtherElementType, _OtherExtent>& __other,
                       enable_if_t<
                          std::is_convertible_v<_OtherElementType(*)[], element_type (*)[]>,
                          nullptr_t> = nullptr) noexcept
        : __data{__other.data()}, __size{__other.size()} {}

//    ~span() noexcept = default;

    template <size_t _Count>
    inline
    constexpr span<element_type, _Count> first() const noexcept
    {
        _LIBCPP_ASSERT(_Count <= size(), "Count out of range in span::first()");
        return span<element_type, _Count>{data(), _Count};
    }

    template <size_t _Count>
    inline
    constexpr span<element_type, _Count> last() const noexcept
    {
        _LIBCPP_ASSERT(_Count <= size(), "Count out of range in span::last()");
        return span<element_type, _Count>{data() + size() - _Count, _Count};
    }

    inline
    constexpr span<element_type, dynamic_extent> first(size_type __count) const noexcept
    {
        _LIBCPP_ASSERT(__count <= size(), "Count out of range in span::first(count)");
        return {data(), __count};
    }

    inline
    constexpr span<element_type, dynamic_extent> last (size_type __count) const noexcept
    {
        _LIBCPP_ASSERT(__count <= size(), "Count out of range in span::last(count)");
        return {data() + size() - __count, __count};
    }

    template <size_t _Offset, size_t _Count = dynamic_extent>
    inline
    constexpr span<element_type, _Count> subspan() const noexcept
    {
        _LIBCPP_ASSERT(_Offset <= size(), "Offset out of range in span::subspan()");
        _LIBCPP_ASSERT(_Count == dynamic_extent || _Count <= size() - _Offset, "Offset + count out of range in span::subspan()");
        return span<element_type, _Count>{data() + _Offset, _Count == dynamic_extent ? size() - _Offset : _Count};
    }

    constexpr span<element_type, dynamic_extent>
    inline
    subspan(size_type __offset, size_type __count = dynamic_extent) const noexcept
    {
        _LIBCPP_ASSERT(__offset <= size(), "Offset out of range in span::subspan(offset, count)");
        _LIBCPP_ASSERT(__count  <= size() || __count == dynamic_extent, "count out of range in span::subspan(offset, count)");
        if (__count == dynamic_extent)
            return {data() + __offset, size() - __offset};
        _LIBCPP_ASSERT(__count <= size() - __offset, "Offset + count out of range in span::subspan(offset, count)");
        return {data() + __offset, __count};
    }

    inline constexpr size_type size()       const noexcept { return __size; }
    inline constexpr size_type size_bytes() const noexcept { return __size * sizeof(element_type); }
    inline constexpr bool empty()           const noexcept { return __size == 0; }

    inline constexpr reference operator[](size_type __idx) const noexcept
    {
        _LIBCPP_ASSERT(__idx < size(), "span<T>[] index out of bounds");
        return __data[__idx];
    }

    inline constexpr reference front() const noexcept
    {
        _LIBCPP_ASSERT(!empty(), "span<T>[].front() on empty span");
        return __data[0];
    }

    inline constexpr reference back() const noexcept
    {
        _LIBCPP_ASSERT(!empty(), "span<T>[].back() on empty span");
        return __data[size()-1];
    }


    inline constexpr pointer data()                         const noexcept { return __data; }

// [span.iter], span iterator support
    inline constexpr iterator                 begin() const noexcept { return iterator(data()); }
    inline constexpr iterator                   end() const noexcept { return iterator(data() + size()); }
    inline constexpr reverse_iterator        rbegin() const noexcept { return reverse_iterator(end()); }
    inline constexpr reverse_iterator          rend() const noexcept { return reverse_iterator(begin()); }

    inline span<const byte, dynamic_extent> __as_bytes() const noexcept
    { return {reinterpret_cast<const byte *>(data()), size_bytes()}; }

    inline span<byte, dynamic_extent> __as_writable_bytes() const noexcept
    { return {reinterpret_cast<byte *>(data()), size_bytes()}; }

private:
    pointer   __data;
    size_type __size;
};

//  as_bytes & as_writable_bytes
template <class _Tp, size_t _Extent>
inline
auto as_bytes(span<_Tp, _Extent> __s) noexcept
-> decltype(__s.__as_bytes())
{ return    __s.__as_bytes(); }

template <class _Tp, size_t _Extent>
inline
auto as_writable_bytes(span<_Tp, _Extent> __s) noexcept
-> enable_if_t<!is_const_v<_Tp>, decltype(__s.__as_writable_bytes())>
{ return __s.__as_writable_bytes(); }

//  Deduction guides
template<class _Tp, size_t _Sz>
    span(_Tp (&)[_Sz]) -> span<_Tp, _Sz>;

template<class _Tp, size_t _Sz>
    span(array<_Tp, _Sz>&) -> span<_Tp, _Sz>;

template<class _Tp, size_t _Sz>
    span(const array<_Tp, _Sz>&) -> span<const _Tp, _Sz>;

template<class _Container>
    span(_Container&) -> span<typename _Container::value_type>;

template<class _Container>
    span(const _Container&) -> span<const typename _Container::value_type>;

} // namespace tybl::vodka

#endif // TYBL_VODKA_SPAN_SPAN_HPP
