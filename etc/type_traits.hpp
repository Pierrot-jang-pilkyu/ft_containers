#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP
#include "basic_macro.hpp"

_FT_BEGIN
template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
	typedef T type;
};






_FT_END
#endif
