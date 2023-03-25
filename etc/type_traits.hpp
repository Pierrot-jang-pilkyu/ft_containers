#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP
#include "basic_macro.hpp"

_FT_BEGIN

template <typename _Ty, _Ty _v>
struct integral_constant
{
	typedef _Ty		value_type;
	static const _Ty value = _v;

	operator value_type() const
	{
		return ( value );
	}
};

#define _INTEGRAL_CONSTANT(_b)	integral_constant<bool, (_b)>

typedef _INTEGRAL_CONSTANT(true) true_type;
typedef _INTEGRAL_CONSTANT(false) false_type;


template <class _Ty> struct __libcpp_is_integral                     : public false_type {};
template <>          struct __libcpp_is_integral<bool>               : public true_type {};
template <>          struct __libcpp_is_integral<char>               : public true_type {};
template <>          struct __libcpp_is_integral<signed char>        : public true_type {};
template <>          struct __libcpp_is_integral<unsigned char>      : public true_type {};
template <>          struct __libcpp_is_integral<wchar_t>            : public true_type {};

template <>          struct __libcpp_is_integral<char16_t>           : public true_type {};
template <>          struct __libcpp_is_integral<char32_t>           : public true_type {};

template <>          struct __libcpp_is_integral<short>              : public true_type {};
template <>          struct __libcpp_is_integral<unsigned short>     : public true_type {};
template <>          struct __libcpp_is_integral<int>                : public true_type {};
template <>          struct __libcpp_is_integral<unsigned int>       : public true_type {};
template <>          struct __libcpp_is_integral<long>               : public true_type {};
template <>          struct __libcpp_is_integral<unsigned long>      : public true_type {};
template <>          struct __libcpp_is_integral<long long>          : public true_type {};
template <>          struct __libcpp_is_integral<unsigned long long> : public true_type {};

template<typename _Ty>
struct is_integral : public __libcpp_is_integral<typename std::remove_cv<_Ty>::type > {};

template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
	typedef T type;
};

template <typename _Arg, typename _Result>
struct __unary_function
{
    typedef _Arg    argument_type;
    typedef _Result result_type;
};

template <typename _Ty>
struct __key_of_value : public __unary_function<_Ty, _Ty>
{
	_Ty operator()(_Ty __a)
	{
		return ( __a );
	}

	_Ty operator()(const _Ty __a) const
	{
		return ( __a );
	}
};

template <typename _Arg, typename _Result>
struct __key_of_value_pair : public __unary_function<_Arg, _Result>
{
	_Result operator()(_Arg __a)
	{
		return ( (_Result)(__a.first) );
	}

	_Result operator()(const _Arg __a) const
	{
		return ( (_Result)(__a.first) );
	}
};
_FT_END
#endif
