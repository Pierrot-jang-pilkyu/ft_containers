#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "basic_macro.hpp"
// #include "rb_tree.hpp"

_FT_BEGIN

// template <typename _Ty, typename _Compare, typename _Alloc = std::allocator<_Ty> > class rb_tree;

// template <typename _Ty> struct __rb_tree_node : public __rb_tree_node_base;

template<class _Iter>
struct iterator_traits;

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// https://cplusplus.com/reference/iterator/iterator_traits/?kw=iterator_traits 

template<class _Iter>
struct iterator_traits
{
	typedef typename _Iter::iterator_category	iterator_category;
	typedef typename _Iter::value_type			value_type;
	typedef typename _Iter::difference_type		difference_type;
	typedef typename _Iter::pointer				pointer;
	typedef typename _Iter::reference			reference;
};

template<class _Ty>
struct iterator_traits<_Ty*>
{
	typedef random_access_iterator_tag				iterator_category;
	typedef _Ty										value_type;
	typedef std::ptrdiff_t							difference_type;
	typedef value_type*								pointer;
	typedef value_type&								reference;
};

template<class _Ty>
struct iterator_traits<const _Ty*>
{
	typedef random_access_iterator_tag				iterator_category;
	typedef const _Ty								value_type;
	typedef std::ptrdiff_t							difference_type;
	typedef value_type*								pointer;
	typedef value_type&								reference;
};

_FT_END
#endif
