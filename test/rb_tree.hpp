#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "iterator.hpp"
#include "algorithm.hpp"
#include "basic_macro.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include <memory>

_FT_BEGIN

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base
{
	typedef __rb_tree_color_type	__color_type;
	typedef __rb_tree_node_base*	__base_pointer;

	__color_type					__color;
	__base_pointer					__parent;
	__base_pointer					__left;
	__base_pointer					__right;
};

template <typename _Ty>
struct __rb_tree_node : public __rb_tree_node_base
{
	typedef bidirectional_iterator_tag	iterator_category;
	typedef __rb_tree_node<_Ty>			value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef __rb_tree_node<_Ty>*		pointer;
	typedef __rb_tree_node<_Ty>&		reference;

	_Ty		__value_field;

	__rb_tree_node() : __value_field(_Ty()) {}
	__rb_tree_node(const _Ty& _val) : __value_field(_val) {}

	reference operator*() const
	{
		return (__value_field);
	}

	__rb_tree_node &operator=(const __rb_tree_node& _Right)
	{
		this->__color = _Right.__color;
		this->__parent = _Right.__parent;
		this->__left = _Right.__left;
		this->__right = _Right.__right;
		this->__value_field = _Right.__value_field;
		return (*this);
	}
};

template <typename _Ty, typename _Compare, typename _Alloc = std::allocator<_Ty> > class rb_tree;

template <typename _Iter, typename _Container>
class __rb_tree_iterator :
	public ft::iterator <	typename ft::iterator_traits<_Iter>::iterator_category,
						typename ft::iterator_traits<_Iter>::value_type,
						typename ft::iterator_traits<_Iter>::difference_type,
						typename ft::iterator_traits<_Iter>::pointer,
						typename ft::iterator_traits<_Iter>::reference >
{
protected:
	using ft::rb_tree::__increment;
	using ft::rb_tree::__decrement;
	using ft::rb_tree::_nil;

	_Iter current;

public:
	// Member type
	typedef _Iter													iterator_type;
	typedef typename ft::iterator_traits<_Iter>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<_Iter>::value_type			value_type;
	typedef typename ft::iterator_traits<_Iter>::difference_type	difference_type;
	typedef typename ft::iterator_traits<_Iter>::pointer			pointer;
	typedef typename ft::iterator_traits<_Iter>::reference			reference;

	// Member Function
	__rb_tree_iterator() : current(_Iter()) {}
	explicit __rb_tree_iterator (const iterator_type& _It) : current(_It) {}
	// Allow iterator to const_iterator conversion
	template <typename _Iter2>
	__rb_tree_iterator (const __rb_tree_iterator<_Iter2, _Container>& _It) : current(_It.base()) {}
	__rb_tree_iterator &operator=(const __rb_tree_iterator<_Iter, _Container>& _Right)
	{
		this->current = _Right.current;
		return (*this);
	}

	iterator_type base() const
	{
		return (current);
	}

	// forward_iterator requirements

	reference operator*() const
	{
		return (*current);
	}

	pointer operator->() const
	{
		return (&(operator*()));
	}

	__rb_tree_iterator &operator++()
	{
		__increment(current, ft::rb_tree::_nil);
		return (*this);
	}

	__rb_tree_iterator operator++(int)
	{
		return ( __rb_tree_iterator(current++) );
	}

	// bidirectional_iterator requirements

	__rb_tree_iterator &operator--()
	{
		__decrement(current, ft::rb_tree::_nil);
		return (*this);
	}

	__rb_tree_iterator operator--(int)
	{
		return ( __rb_tree_iterator(current--) );
	}
};

template<typename _IterL, typename _IterR, typename _Container>
inline bool operator==(const __rb_tree_iterator<_IterL, _Container>& _Left, const __rb_tree_iterator<_IterR, _Container>& _Right)
{
	return ( _Left.base() == _Right.base() );
}

template<typename _IterL, typename _IterR, typename _Container>
inline bool operator!=(const __rb_tree_iterator<_IterL, _Container>& _Left, const __rb_tree_iterator<_IterR, _Container>& _Right)
{
	return ( _Left.base() != _Right.base() );
}

template <typename _Ty, typename _Compare, typename _Alloc >
class rb_tree
{
private:
	typedef rb_tree<_Ty, _Alloc>				rb_tree_type;

public:
	// Member type
	typedef __rb_tree_node<_Ty>								value_type;
	typedef _Compare										compare_type;
	typedef _Alloc											allocator_type;
	typedef value_type*										pointer;
	typedef const value_type*								const_pointer;
	typedef value_type&										reference;
	typedef const value_type&								const_reference;
	typedef typename __rb_tree_node_base::__base_pointer	base_pointer;
	typedef std::ptrdiff_t									difference_type;
	typedef std::size_t										size_type;
	typedef __rb_tree_color_type							color_type;

	// Membertype - iterator
	typedef __rb_tree_iterator<pointer, rb_tree_type>		iterator;
	typedef __rb_tree_iterator<const pointer, rb_tree_type>	const_iterator;
	typedef reverse_iterator<const_iterator>				const_reverse_iterator;
	typedef reverse_iterator<iterator>						reverse_iterator;

protected:
	allocator_type	_data_allocate;
	compare_type	_compare;
	size_type		_count;
	pointer			_nil;

	static pointer __minimum_node(pointer& __root)
	{
		while ( __root->__left != _nil )
			__root = __root->__left;
		return ( __root );
	}

	static pointer __maximum_node(pointer& __root)
	{
		while ( __root->__right != _nil )
			__root = __root->__right;
		return ( __root );
	}

public:

/*
**	|------------------------------------------------------Member_function----------------------------------------------------|


**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Get_Member_Attribute-----------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	allocator_type get_allocater() const
	{
		return ( _data_allocator );
	}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Iterators----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	iterator begin() { return ( iterator(__minimum_node((pointer&)_nil->__parent)) ); }
	const_iterator begin() const { return ( const_iterator(__minimum_node((pointer&)_nil->__parent)) ); }
	iterator end() { return ( iterator(_nil) ); }
	const_iterator end() const { return ( const_iterator(_nil) ); }

	reverse_iterator rbegin() { return reverse_iterator( end() ); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator( end() ); }
	reverse_iterator rend() { return reverse_iterator( begin() ); }
	const_reverse_iterator rend() const { return const_reverse_iterator( begin() ); }

protected:
	void __increment(pointer& __node, pointer __nil)
	{
		if (__node->__right != __nil)
		{
			__node = __node->__right;
			while (__node->__left != __nil)
				__node = __node->__left;
		}
		else
		{
			pointer _Tmp = __node->__parent;
			while (__node == _Tmp->__right)
			{
				__node = _Tmp;
				_Tmp = _Tmp->__parent;
			}
			__node = _Tmp;
		}
	}

	void __decrement(pointer &__node, pointer __nil)
	{
		if (__node == end().base())
		{
			__node = __maximum_node(_nil->__parent);
		}
		else if (__node->__left != __nil)
		{
			__node = __node->__left;
			while (__node->__right != __nil)
				__node = __node->__right;
		}
		else
		{
			pointer _Tmp = __node->__parent;
			while (__node == _Tmp->left)
			{
				__node = _Tmp;
				_Tmp = _Tmp->parent;
			}
			__node = _Tmp;
		}
	}

	pointer __get_node()
	{
		return ( _data_allocator.allocate(__n) );
	}

	void	__put_node(pointer __p)
	{
		if (__p)
			_data_allocator.deallocate(__p, 1);
	}

	void __construct(pointer __p, const _Ty& _val)
	{
		if (__p)
			_data_allocator.construct(__p, _val);
	}

	void __destroy(pointer _first, pointer _last)
	{
		for (; _first != _last; ++_first)
		{
			_data_allocator.destroy(_first);
		}
	}

	void __destroy(pointer _pos)
	{
		_data_allocator.destroy(_pos);
	}

	pointer __create_node(const value_type& __val)
	{
		pointer _Tmp = __get_node();
		try
		{
			_construct(&_Tmp->__value_field, _val);
		}
		catch(const std::exception& e)
		{
			__put_node(_Tmp);
			std::cerr << e.what() << '\n';
		}
		return (_Tmp);
	}

	pointer __clone_node(pointer __node)
	{
		pointer _Tmp = __create_node(__node->__value_field);
		_Tmp->__color = __node->__color;
		_Tmp->__left = _nil;
		_Tmp->__right = _nil;
		return (_Tmp);
	}

	void __destroy_node(pointer __node)
	{
		__destroy(&__node->__value_field);
		__node->__left = 0;
		__node->__right = 0;
		__put_node(__node);
	}

	pointer& __root() const { return ( (pointer&)_nil->__parent ); }

	static pointer& __get_parent(pointer __node) { return ( (pointer&)__node->__parent ); }
	static pointer& __get_left(pointer __node) { return ( (pointer&)__node->__left ); }
	static pointer& __get_right(pointer __node) { return ( (pointer&)__node->__right ); }
	static color_type& __get_color(pointer __node) { return ( (color_type&)__node->__color ); }
	static reference __get_value(pointer __node) { return ( __node->__value_field ); }

	static pointer& __get_parent(base_pointer __node) { return ( (pointer&)__node->__parent ); }
	static pointer& __get_left(base_pointer __node) { return ( (pointer&)__node->__left ); }
	static pointer& __get_right(base_pointer __node) { return ( (pointer&)__node->__right ); }
	static color_type& __get_color(base_pointer __node) { return ( (color_type&)__node->__color ); }
	static reference __get_value(base_pointer __node) { return ( __node->__value_field ); }

public:

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Capacity-----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	size_type size() const {  return (_count); }
	size_type max_size() const { return ( size_type(-1) / sizseof(value_type) ); }
	bool empty() { return ( _count == 0 ); }





/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Modifiers----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	void swap(rb_tree<_Ty, _Compare, _Alloc>& __t)
	{
		ft::swap(this->_nil, __t->_nil);
		ft::swap(this->_count, __t->_count);
		ft::swap(this->_compare, __t->_compare);
	}

};


_FT_END
#endif
