#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include "basic_macro.hpp"
#include <cstring>

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
	value_type tmp;
	std::memmove(static_cast<void *>(&tmp), static_cast<void *>(&a), sizeof(value_type));
	std::memmove(static_cast<void *>(&a), static_cast<void *>(&b), sizeof(value_type));
	std::memmove(static_cast<void *>(&b), static_cast<void *>(&tmp), sizeof(value_type));
}
_FT_END
#endif