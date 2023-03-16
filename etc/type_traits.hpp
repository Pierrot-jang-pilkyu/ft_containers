#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP
#include "basic_macro.hpp"

_FT_BEGIN

struct true_type
{
	static const bool value = true;
};

struct false_type
{
	static const bool value = false;
};

template <class _Ty> struct is_integral                     : public false_type {};
template <>          struct is_integral<bool>               : public true_type {};
template <>          struct is_integral<char>               : public true_type {};
template <>          struct is_integral<signed char>        : public true_type {};
template <>          struct is_integral<unsigned char>      : public true_type {};
template <>          struct is_integral<wchar_t>            : public true_type {};

template <>          struct is_integral<char16_t>           : public true_type {};
template <>          struct is_integral<char32_t>           : public true_type {};

template <>          struct is_integral<short>              : public true_type {};
template <>          struct is_integral<unsigned short>     : public true_type {};
template <>          struct is_integral<int>                : public true_type {};
template <>          struct is_integral<unsigned int>       : public true_type {};
template <>          struct is_integral<long>               : public true_type {};
template <>          struct is_integral<unsigned long>      : public true_type {};
// template <>          struct is_integral<long long>          : public true_type {};
// template <>          struct is_integral<unsigned long long> : public true_type {};

template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
	typedef T type;
};

_FT_END
#endif
