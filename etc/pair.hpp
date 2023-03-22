#ifndef PAIR_HPP
#define PAIR_HPP
#include "basic_macro.hpp"

_FT_BEGIN
template <typename _T1, typename _T2>
struct pair
{
	typedef _T1	first_type;
	typedef _T2	second_type;

	first_type	first;
	second_type	second;

	pair() : first(), second() {}
	pair(const _T1& _t1, const _T2& _t2) : first(_t1), second(_t2) {}
	template <typename _U1, typename _U2>
	pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}

	pair &operator=(const pair& _Other)
	{
		this->first = _Other.first;
		this->second = _Other.second;
		return (*this);
	}
};

template <typename _T1, typename _T2>
inline bool operator==(const pair<_T1, _T2>& _Left, const pair<_T1, _T2>& _Right)
{
	return ( (_Left.first == _Right.first) && (_Left.second == _Right.second) );
}

template <typename _T1, typename _T2>
inline bool operator!=(const pair<_T1, _T2>& _Left, const pair<_T1, _T2>& _Right)
{
	return ( !(_Left == _Right) );
}

template <typename _T1, typename _T2>
inline bool operator<(const pair<_T1, _T2>& _Left, const pair<_T1, _T2>& _Right)
{
	return ( (_Left.first < _Right.first) || ( !(_Left.first < _Right.first) && (_Left.second < _Right.second)) );
}

template <typename _T1, typename _T2>
inline bool operator>(const pair<_T1, _T2>& _Left, const pair<_T1, _T2>& _Right)
{
	return ( _Right < _Left );
}

template <typename _T1, typename _T2>
inline bool operator<=(const pair<_T1, _T2>& _Left, const pair<_T1, _T2>& _Right)
{
	return !( _Right < _Left );
}

template <typename _T1, typename _T2>
inline bool operator>=(const pair<_T1, _T2>& _Left, const pair<_T1, _T2>& _Right)
{
	return !( _Left < _Right );
}

template <typename _T1, typename _T2>
pair<_T1, _T2> make_pair(_T1 _t1, _T2 _t2)
{
	return ( pair<_T1, _T2>(_t1, _t2) );
}
_FT_END
#endif
