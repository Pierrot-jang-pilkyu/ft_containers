#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "pair.hpp"
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

	__rb_tree_node() : __value_field(_Ty()), __color(__rb_tree_red), __parent(0), __left(0), __right(0) {}
	__rb_tree_node(const _Ty& _val) : __value_field(_val), __color(__rb_tree_red), __parent(0), __left(0), __right(0) {}

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

template <typename _Ty, typename _Compare, typename _Alloc = std::allocator<__rb_tree_node<_Ty> > > class rb_tree;

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
		__increment(current, _nil);
		return (*this);
	}

	__rb_tree_iterator operator++(int)
	{
		return ( __rb_tree_iterator(current++) );
	}

	// bidirectional_iterator requirements

	__rb_tree_iterator &operator--()
	{
		__decrement(current, _nil);
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

template <typename _Ty, typename _Compare, typename _Alloc>
class rb_tree
{
private:
	typedef rb_tree<_Ty, _Compare, _Alloc>					rb_tree_type;

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
	allocator_type		_data_allocator;
	compare_type		_compare;
	size_type			_count;
	static pointer		_nil;

	static pointer __minimum_node(pointer& __root)
	{
		while ( __left(__root) != _nil )
			__root = __left(__root);
		return ( __root );
	}

	static pointer __maximum_node(pointer& __root)
	{
		while ( __right(__root) != _nil )
			__root = __right(__root);
		return ( __root );
	}

	pointer& __root() const { return ( (pointer&)_nil->__parent ); }

	static pointer& __parent(pointer __node) { return ( (pointer&)__node->__parent ); }
	static pointer& __gparent(pointer __node)
	{
		pointer _Tmp = __parent(__node);
		if (__parent(_Tmp) != 0)
			return ( (pointer&)(_Tmp->parent) );
		else
			return (0);
	}
	static pointer& __ggparent(pointer __node)
	{
		pointer _Tmp = __gparent(__node);
		if (__parent(_Tmp) != 0)
			return ( (pointer&)(_Tmp->parent) );
		else
			return (0);
	}
	static pointer& __uncle(pointer __node)
	{
		if (__node->__parent != _nil)
		{
			if (__node == __node->__parent->__left)
				return (pointer&)(__node->__parent->__right);
			else if (__node == __node->__parent->__right)
				return (pointer&)(__node->__parent->__left);
		}
		else
			return (0);
	}
	static pointer& __left(pointer __node) { return ( (pointer&)__node->__left ); }
	static pointer& __right(pointer __node) { return ( (pointer&)__node->__right ); }
	static color_type& __color(pointer __node) { return ( (color_type&)__node->__color ); }
	static reference __value(pointer __node) { return ( __node->__value_field ); }

	static pointer& __parent(base_pointer __node) { return ( (pointer&)__node->__parent ); }
	static pointer& __gparent(base_pointer __node)
	{
		pointer _Tmp = __parent(__node);
		if (__parent(_Tmp) != 0)
			return ( (pointer&)(_Tmp->parent) );
		else
			return (0);
	}
	static pointer& __ggparent(base_pointer __node)
	{
		pointer _Tmp = __gparent(__node);
		if (__parent(_Tmp) != 0)
			return ( (pointer&)(_Tmp->parent) );
		else
			return (0);
	}
	static pointer& __uncle(base_pointer __node)
	{
		if (__parent(__node)!= _nil)
		{
			if (__node == (pointer&)__node->__parent->__left)
				return (pointer&)(__node->__parent->__right);
			else if (__node == __node->__parent->__right)
				return (pointer&)(__node->__parent->__left);
		}
		else
			return (0);
	}
	static pointer& __left(base_pointer __node) { return ( (pointer&)__node->__left ); }
	static pointer& __right(base_pointer __node) { return ( (pointer&)__node->__right ); }
	static color_type& __color(base_pointer __node) { return ( (color_type&)__node->__color ); }
	static reference __value(base_pointer __node) { return ( __value((pointer&)__node) ); }

	void __left_rotate(pointer __node);
	void __right_rotate(pointer __node);

	void __revalance(pointer __node);

	ft::pair<iterator, bool> __insert_node(pointer __root, const _Ty& _val);

	void __initialize()
	{
		__color(_nil) = __rb_tree_red;
		(pointer&)_nil->__parent = 0;
		(pointer&)_nil->__left = _nil;
		(pointer&)_nil->__right = _nil;
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

	compare_type __key_comp() const { return ( _compare ); }

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
				_Tmp = __parent(_Tmp);
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
		return ( _data_allocator.allocate(1) );
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
		_Tmp->__color = __rb_tree_red;
		(pointer&)_Tmp->__left = _nil;
		(pointer&)__right(_Tmp) = _nil;
		try
		{
			_construct(&_Tmp->__value_field, __val);
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
		(pointer&)_Tmp->__left = _nil;
		(pointer&)__right(_Tmp) = _nil;
		return (_Tmp);
	}

	void __destroy_node(pointer __node)
	{
		__destroy(&__node->__value_field);
		__node->__left = 0;
		__node->__right = 0;
		__put_node(__node);
	}


	pointer __copy(pointer _first, pointer _last);
	void	__erase(pointer __p);

public:

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Capacity-----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	size_type size() const {  return (_count); }
	size_type max_size() const { return ( size_type(-1) / sizseof(__rb_tree_node<_Ty>() ) ); }
	bool empty() { return ( _count == 0 ); }

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|---------------------------------------------Othodox_Canonical_Form + Alpha----------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	rb_tree()
	: _data_allocator(allocator_type()), _count(0), _compare()
	{ __initialize(); }

	rb_tree(const compare_type& _comp)
	: _data_allocator(allocator_type()), _count(0), _compare(_comp)
	{ __initialize(); }

	rb_tree(const compare_type& _comp, const allocator_type& __a)
	: _data_allocator(__a), _count(0), _compare(_comp)
	{ __initialize(); }

	rb_tree(const rb_tree_type& __t)
	: _data_allocator(__t.get_allocater()), _count(0), _compare(__t.__key_comp)
	{
		if (__t.__root() == 0)
			__initialize();
		else
		{
			__color(_nil) = __rb_tree_red;
			__root() = __copy(__t.__root(), _nil);
			(pointer&)_nil->__left = _nil;
			(pointer&)_nil->__right = _nil;
		}
		_count = __t._count;
	}

	~rb_tree() { clear(); }

	rb_tree_type& operator=(const rb_tree_type& __t);

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

	pair<iterator, bool> insert(const value_type &__val)
	{ return ( __insert_node(__root(), __val) ); }

	iterator insert(iterator __position, const value_type &__val)
	{ return ( __insert_node(__position.base(), __val).first ); }

	template <class _InputIterator>
	void insert(_InputIterator __first, _InputIterator __last)
	{
		for (; __first != __last; ++__first)
			insert(*__first);
	}

	void erase(iterator __position);
	// size_type erase(const key_type &__x);
	// void erase(iterator __first, iterator __last);

	void clear()
	{
		if (_count != 0)
		{
			__erase(__root());
			(pointer&)_nil->__left = _nil;
			__root() = 0;
			(pointer&)_nil->__right = _nil;
			_count = 0;
		}
	}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|--------------------------------------------------------Lookup-----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	// iterator find(const key_type &__x);
	// const_iterator find(const key_type &__x) const;
	// size_type count(const key_type &__x) const;
	// iterator lower_bound(const key_type &__x);
	// const_iterator lower_bound(const key_type &__x) const;
	// iterator upper_bound(const key_type &__x);
	// const_iterator upper_bound(const key_type &__x) const;
	// pair<iterator, iterator> equal_range(const key_type &__x);
	// pair<const_iterator, const_iterator> equal_range(const key_type &__x) const;
};

template <typename _Ty2, typename _Compare, typename _Alloc2>
inline bool 
operator==(const rb_tree<_Ty2, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _Compare, _Alloc2>& _Right)
{
  return ( ( _Left.size() == _Right.size() ) && ( equal(_Left.begin(), _Left.end(), _Right.begin()) ) );
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
inline bool 
operator<(const rb_tree<_Ty2, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _Compare, _Alloc2>& _Right)
{
  return ( lexicographical_compare(_Left.begin(), _Left.end(), _Right.begin(), _Right.end()) );
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
inline bool 
operator!=(const rb_tree<_Ty2, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _Compare, _Alloc2>& _Right)
{
  return !(_Left == _Right);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
inline bool 
operator>(const rb_tree<_Ty2, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _Compare, _Alloc2>& _Right)
{
  return (_Right < _Left);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
inline bool 
operator<=(const rb_tree<_Ty2, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _Compare, _Alloc2>& _Right)
{
  return !(_Right < _Left);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
inline bool 
operator>=(const rb_tree<_Ty2, _Compare, _Alloc2>& _Left,  const rb_tree<_Ty2, _Compare, _Alloc2>& _Right)
{
  return !(_Left < _Right);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
void swap(const rb_tree<_Ty2, _Compare, _Alloc2>& __t1, const rb_tree<_Ty2, _Compare, _Alloc2>& __t2)
{
	__t1.swap(__t2);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
rb_tree<_Ty2, _Compare, _Alloc2>& rb_tree<_Ty2, _Compare, _Alloc2>::operator=(const rb_tree<_Ty2, _Compare, _Alloc2>& __t)
{
	if (this != &__t)
	{
		clear();
		_count = 0;
		_compare = __t._compare;
		if (__t.__root() == 0)
		{
			__root() = 0;
			(pointer&)_nil->__left = _nil;
			(pointer&)_nil->__right = _nil;
		}
		else
		{
			__root() = __copy(__t.__root(), _nil);
			(pointer&)_nil->__left = _nil;
			(pointer&)_nil->__right = _nil;
			_count = __t._count;
		}
	}
	return (*this);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _Compare, _Alloc2>::__erase(pointer __p)
{
	while (__p != _nil)
	{
		__erase(__right(__p));
		pointer _Tmp = __left(__p);
		__destroy(__p);
		__p = _Tmp;
	}
}


template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::pointer
rb_tree<_Ty2, _Compare, _Alloc2>::__copy(pointer __x, pointer __p)
{
	if (__x == 0 || __p == 0)
		return ( __initialize() );
	pointer _top = __clone_node(__x);
	__parent(_top) = __p;

	try
	{
		if (__x->__right)
			__right(_top) = __copy(__right(__x), _top);
		__p = _top;
		__x = __left(__x);

		while (__x != _nil)
		{
			pointer _Tmp = __clone_node(__x);
			__left(__p) = _Tmp;
			__parent(_Tmp) = __p;
			if (__x->__right)
				__right(_Tmp) = __copy(__left(__x), _Tmp);
			__p = _Tmp;
			__x = __left(__x);
		}
	}
	catch(const std::exception& e)
	{
		__erase(_top);
		std::cerr << e.what() << '\n';
	}
	return (_top);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _Compare, _Alloc2>::__left_rotate(pointer __node)
{
	pointer _Tmp = __node->__right;

	__node->__right = _Tmp->__left;

	if (_Tmp->__left != _nil)
		_Tmp->__left->__parent = __node;

	__parent(_Tmp) = __node->__parent;

	if (__parent(__node)== _nil)
		_nil->__parent = _Tmp;	// root setting
	else if (__node->__parent->__left == __node)
		__node->__parent->__left = _Tmp;
	else
		__node->__parent->__right = _Tmp;

	_Tmp->__left = __node;
	__parent(__node)= _Tmp;
}


template <typename _Ty2, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _Compare, _Alloc2>::__right_rotate(pointer __node)
{
	pointer _Tmp = (pointer&)__node->__left;

	__node->__left = _Tmp->__right;

	if (__right(_Tmp) != _nil)
		(pointer&)_Tmp->__right->__parent = __node;

	__parent(_Tmp) = __node->__parent;

	if (__parent(__node)== _nil)
		_nil->__parent = _Tmp;	// root setting
	else if ((pointer&)__node->__parent->__left == __node)
		(pointer&)__node->__parent->__left = _Tmp;
	else
		(pointer&)__node->__parent->__right = _Tmp;

	__right(_Tmp) = __node;
	__parent(__node)= _Tmp;
}


template <typename _Ty2, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _Compare, _Alloc2>::__revalance(pointer __node)
{
	while (__node->__parent->__color == __rb_tree_red)
	{
		pointer _grand = __gparent(__node);
		pointer _uncle = __uncle(__node);
		if (__parent(__node)== _grand->__left)
		{
			// parent, uncle : red
			if (_uncle->__color == __rb_tree_red)
			{	// parent, uncle, grand : !color
				__node->__parent->__color = _uncle->__color = __rb_tree_black;
				_grand->__color = __rb_tree_red;
				__node = _grand;
			}
			else
			{	// uncle : black
				if (__node == (pointer&)__node->__parent->__right)
				{
					__node = (pointer&)__node->__parent;
					__left_rotate(__node);
				}
				// original __node and __node->__left by the left_rotate is double red : uncle(nil) is black.
				// original __node is parent_node of __node->__left and grand. because __node is middle value of three nodes.
				__right_rotate(_grand);
				// therefore, original __node is __node->parent.
				__node->__parent->__color = __rb_tree_black;
				_grand->__color = __node->__color = __rb_tree_red;
			}
		}
		else
		{	// __node->parent == _grand->__right
			// parent, uncle : red
			if (_uncle->__color == __rb_tree_red)
			{	// parent, uncle, grand : !color
				__node->__parent->__color = _uncle->__color = __rb_tree_black;
				_grand->__color = __rb_tree_red;
				__node = _grand;
			}
			else
			{	// uncle : black
				if (__node == (pointer&)__node->__parent->__left)
				{
					__node = (pointer&)__node->__parent;
					__right_rotate(__node);
				}
				// original __node and __node->__left by the left_rotate is double red : uncle(nil) is black.
				// original __node is parent_node of __node->__left and grand. because __node is middle value of three nodes.
				__left_rotate(_grand);
				// therefore, original __node is __node->parent.
				__node->__parent->__color = __rb_tree_black;
				_grand->__color = __node->__color = __rb_tree_red;
			}
		}
	}
	_nil->__parent->__color = __rb_tree_black;
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
ft::pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, bool>
rb_tree<_Ty2, _Compare, _Alloc2>::__insert_node(pointer __root, const _Ty2& _data)
{
	pointer parent = _nil;
	pointer tail = (pointer&)(_nil->__parent);

	while (tail != _nil)
	{
		// parent : nil -> root, tail : root -> left or right.
		parent = tail;
		_Ty2 var = tail->__value_field;
		if (_data == var) // iterator.base()->__value_field == _data
			return ( typename ft::pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, bool>(iterator(tail), false) );
		else if (_compare(_data, var))
			tail = tail->__left;
		else
			tail = tail->__right;
	}	// insert position is setting in parent.
	tail = __create_node(_data);
	if (parent == _nil)
	{
		parent->__parent = tail;
		tail->__color = __rb_tree_black;
	}
	else if (_compare(_data, parent->__value_field))
		parent->__left = tail;
	else
		parent->__right = tail;
	++this->_count;
	__revalance(tail);
	return ( typename ft::pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, bool>(iterator(tail), true) );
}


template <typename _Ty2, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _Compare, _Alloc2>::erase(iterator __position)
{
	pointer __p = __position.base();
	pointer _Tmp;
	if (__left(__p) != _nil)
	{
		_Tmp = __maximum_node(__left(__p));
		__destroy(&__p->__value_field);
		__construct(&__p->__value_field, _Tmp->__value_field);
		__destroy_node(_Tmp);
	}
	else
	{

	}
	if (__p == __p->__parent->__left)
	{
			_Tmp = __p->__right;
			__p->__parent->__left = _Tmp;
			__parent(_Tmp) = __p->__parent;
			__destroy_node(__p);
	}
	else
	{
			_Tmp = __p->__right;
			__p->__parent->__right = _Tmp;
			__parent(_Tmp) = __p->__parent;
			__destroy_node(__p);
	}
	__revalance(_Tmp);
}

_FT_END
#endif
