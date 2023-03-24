#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include "basic_macro.hpp"
#include "type_traits.hpp"
#include <algorithm>
#include <cstring>
#include <memory>

_FT_BEGIN
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1!=last1)
	{
		if (!(*first1 == *first2))
			return false;
    	++first1; ++first2;
	}
  return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
	while (first1!=last1)
	{
		if (!pred(*first1,*first2))
			return false;
    	++first1; ++first2;
	}
  return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
	while (first1 != last1)
	{
		if (first2 == last2 || comp(first2, first1))
			return false;
		else if (comp(first1, first2))
			return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}

template <typename value_type>
void swap(value_type& a, value_type& b)
{
	value_type tmp(a);
	a = b;
	b = tmp;
}

template <class _input_iterator, class _forward_iterator>
_forward_iterator uninitialized_copy(_input_iterator _first, _input_iterator _last, _forward_iterator _result)
{
	typedef typename ft::iterator_traits<_forward_iterator>::value_type value_type;
	_forward_iterator __s = _result;
	try
	{
		for (; _first != _last; ++_result, ++_first)
			new (static_cast<void *>(&*_result)) value_type(*_first);
	}
	catch(...)
	{
		for (; __s != _result; ++__s)
			__s->~value_type();
		throw ;
	}
	return (_result);
}

template <class _forward_iterator, class _Ty2>
_forward_iterator uninitialized_fill(_forward_iterator _first, _forward_iterator _last, const _Ty2 &_val)
{
	typedef typename ft::iterator_traits<_forward_iterator>::value_type value_type;
	_forward_iterator __s = _first;
	try
	{
		for (; _first != _last; ++_first)
			new (static_cast<void *>(&*_first)) value_type(_val);
	}
	catch(...)
	{
		for (; __s != _first; ++__s)
			__s->~value_type();
			throw ;
	}
	return (_last);
}

template <class _forward_iterator, class _size, class _Ty2>
_forward_iterator uninitialized_fill_n(_forward_iterator _first, _size __n, const _Ty2 &_val)
{
	typedef typename ft::iterator_traits<_forward_iterator>::value_type value_type;
	_forward_iterator __s = _first;
	try
	{
		for (; __n--; ++_first)
			new (static_cast<void *>(&*_first)) value_type(_val);
	}
	catch(...)
	{
		for (; __s != _first; ++__s)
			__s->~value_type();
			throw ;
	}
	return (_first);
}

template <class _forward_iterator, class T>
void fill(_forward_iterator _first, _forward_iterator _last, const T &_val)
{
	while (_first != _last)
	{
		*_first = _val;
		++_first;
	}
}

template <class _outpur_iterator, class Size, class T>
_outpur_iterator fill_n(_outpur_iterator _first, Size n, const T &_val)
{
	while (n > 0)
	{
		*_first = _val;
		++_first;
		--n;
	}
	return _first;
}

template <class _input_iterator, class _output_iterator>
_output_iterator copy(_input_iterator _first, _input_iterator _last, _output_iterator result)
{
	while (_first != _last)
	{
		*result = *_first;
		++result;
		++_first;
	}
	return result;
}

template <class _bidirectional_iterator1, class _bidirectional_iterator2>
_bidirectional_iterator2 copy_backward(_bidirectional_iterator1 _first, _bidirectional_iterator1 _last, _bidirectional_iterator2 result)
{
	while (_last != _first)
		*(--result) = *(--_last);
	return result;
}

_FT_END
#endif
