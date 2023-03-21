#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "pair.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "basic_macro.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include <memory>
#include <stdexcept>

_FT_BEGIN

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

template <typename _Ty>
struct __rb_tree_node
{
	typedef bidirectional_iterator_tag	iterator_category;
	typedef __rb_tree_node<_Ty>			value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef __rb_tree_node<_Ty>*		pointer;
	typedef __rb_tree_node<_Ty>&		reference;
	typedef __rb_tree_color_type	__color_type;

	__color_type					__color;
	bool							__extra_black;
	pointer							__parent;
	pointer							__left;
	pointer							__right;

	_Ty		__value_field;

	__rb_tree_node()
	{
		__value_field = _Ty();
		__color = __rb_tree_red;
		__parent = 0;
		__left = 0;
		__right = 0;
	}
	__rb_tree_node(const _Ty& _val) : __value_field(_val), __color(__rb_tree_red), __parent(0), __left(0), __right(0) {}
	__rb_tree_node(const __rb_tree_node& __n)
	: __value_field(_Ty(__n.__value_field)), __color(__n.__color), __parent(__n.__parent), __left(__n.__left), __right(__n.__right) {}

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
	_Iter current;
	_Iter _nil;

	void __get_nil()
	{
		_Iter _Tmp = current;
		while (_Tmp != _Tmp->__parent->parent)
			_Tmp = _Tmp->parent;
		if (_Tmp == _Tmp->__parent->parent)
			_nil = _Tmp->parent;
	}

		void __increment()
	{
		__get_nil();
		_Iter __node = current;
		if (__node->__right != _nil)
		{
			__node = __node->__right;
			while (__node->__left != _nil)
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
		current = __node;
	}

	void __decrement()
	{
		__get_nil();
		_Iter __node = current;
		if (__node == _nil)
		{
			_Iter __root = _nil->__parent;
			while ( __root->__right != _nil )
				__root = __root->__right;
		}
		else if (__node->__left != _nil)
		{
			__node = __node->__left;
			while (__node->__right != _nil)
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
		current = __node;
	}

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
		__increment();
		return (*this);
	}

	__rb_tree_iterator operator++(int)
	{
		return ( __rb_tree_iterator(current++) );
	}

	// bidirectional_iterator requirements

	__rb_tree_iterator &operator--()
	{
		__decrement();
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
	typedef _Ty												key_type;
	typedef __rb_tree_node<_Ty>								value_type;
	typedef _Compare										compare_type;
	typedef _Alloc											allocator_type;
	typedef value_type*										pointer;
	typedef const value_type*								const_pointer;
	typedef value_type&										reference;
	typedef const value_type&								const_reference;
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
	pointer				_nil;

	pointer __minimum_node(pointer& __root)
	{
		while ( __left(__root) != _nil )
			__root = __left(__root);
		return ( __root );
	}

	pointer __maximum_node(pointer& __root)
	{
		while ( __right(__root) != _nil )
			__root = __right(__root);
		return ( __root );
	}

	pointer& __root() const { return ( (pointer&)_nil->__parent ); }

	pointer& __parent(pointer __node) { return ( (pointer&)__node->__parent ); }
	pointer& __gparent(pointer __node)
	{
		pointer _Tmp = __parent(__node);
		if (__parent(_Tmp) != 0)
			return ( (pointer&)(_Tmp->__parent) );
		else
			return (_nil);
	}
	pointer& __ggparent(pointer __node)
	{
		pointer _Tmp = __gparent(__node);
		if (__parent(_Tmp) != 0)
			return ( (pointer&)(_Tmp->parent) );
		else
			return (_nil);
	}
	pointer& __uncle(pointer __node)
	{
		if (__node->__parent != _nil)
		{
			if (__parent(__node) == __gparent(__node)->__left)
				return (pointer&)(__gparent(__node)->__right);
			else if (__parent(__node) == __gparent(__node)->__right)
				return (pointer&)(__gparent(__node)->__left);
		}
		return (_nil);
	}
	pointer& __left(pointer __node) { return ( (pointer&)__node->__left ); }
	pointer& __right(pointer __node) { return ( (pointer&)__node->__right ); }
	color_type& __color(pointer __node) { return ( (color_type&)__node->__color ); }
	reference __value(pointer __node) { return ( __node->__value_field ); }

	void __left_rotate(pointer __node);
	void __right_rotate(pointer __node);

	void __revalance(pointer __node);

	ft::pair<iterator, bool> __insert_node(const _Ty& _val);
	ft::pair<iterator, bool> __insert_node(pointer __root, const _Ty& _val);

	iterator __get_change_node(pointer _cur)
	{
		if (_cur->__right != _nil)	// predecessor - 선임자
			return (iterator(__maximum_node(_cur->__right)));
		else if (_cur->__left != _nil) // successor - 후임자
			return (iterator(__minimum_node(_cur->__left)));
		else
			return (iterator(_nil));
	}

	void __erase_revalance(pointer __node);
	void __erase_case1(pointer __node);
	void __erase_case2(pointer __node);
	void __erase_case3(pointer __node);
	void __erase_case4(pointer __node);

public:
	void preorder(pointer root, std::string* stringBuilder, std::string padding, const std::string& pointer, const bool hasRightChild) const;

	std::string show_tree() const;




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
	pointer __get_node()
	{
		return ( _data_allocator.allocate(1) );
	}

	void	__put_node(pointer __p)
	{
		if (__p)
			_data_allocator.deallocate(__p, 1);
	}

	void __construct(_Ty* __p, const _Ty& _val)
	{
		if (__p)
			new ((void*)__p) _Ty(_val);
	}

	void __destroy(pointer _pos)
	{
		if (_pos)
			(&_pos->__value_field)->~_Ty();
	}

	pointer __create_node(const _Ty& __val)
	{
		pointer _Tmp = __get_node();
		_Tmp->__color = __rb_tree_red;
		(pointer&)_Tmp->__left = _nil;
		(pointer&)__right(_Tmp) = _nil;
		try
		{
			__construct(&_Tmp->__value_field, __val);
		}
		catch(...)
		{
			__put_node(_Tmp);
			throw ;
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
		__destroy(__node);
		__node->__left = 0;
		__node->__right = 0;
		__put_node(__node);
	}

	void __initialize()
	{
		_nil = __get_node();
		__color(_nil) = __rb_tree_black;
		(pointer&)_nil->__parent = 0;
		(pointer&)_nil->__left = _nil;
		(pointer&)_nil->__right = _nil;
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
	{
		__initialize();
		_data_allocator = allocator_type();
		_count = 0;
		_compare = compare_type();
	}

	rb_tree(const compare_type& _comp)
	{
		__initialize();
		_data_allocator = allocator_type();
		_count = 0;
		_compare = _comp;
	}

	rb_tree(const compare_type& _comp, const allocator_type& __a)
	{
		__initialize();
		_data_allocator = __a;
		_count = 0;
		_compare = _comp;
	}

	rb_tree(const rb_tree_type& __t)
	{
		if (__t.__root() == 0)
		{
			__initialize();
			_data_allocator = allocator_type();
			_count = 0;
			_compare = compare_type();
		}
		else
		{
			_data_allocator = __t.get_allocater();
			__color(_nil) = __rb_tree_black;
			__root() = __copy(__t.__root(), _nil);
			_nil->__left = _nil;
			_nil->__right = _nil;
			_count = __t._count;
		}
	}

	~rb_tree()
	{
		clear();
	}

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

	pair<iterator, bool> insert(const _Ty& __val)
	{
		return ( __insert_node(__val) );
	}

	iterator insert(iterator __position, const _Ty& __val)
	{ return ( __insert_node(__position.base(), __val).first ); }

	template <class _InputIterator>
	void insert(_InputIterator __first, _InputIterator __last)
	{
		for (; __first != __last; ++__first)
			insert(*__first);
	}

	// void erase(iterator __position);
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

	iterator find(const key_type &__x);
	const_iterator find(const key_type &__x) const;
	size_type count(const key_type &__x) const;
	iterator lower_bound(const key_type &__x);
	const_iterator lower_bound(const key_type &__x) const;
	iterator upper_bound(const key_type &__x);
	const_iterator upper_bound(const key_type &__x) const;
	pair<iterator, iterator> equal_range(const key_type &__x);
	pair<const_iterator, const_iterator> equal_range(const key_type &__x) const;
};


/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|--------------------------------------------------Relational_Operator----------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

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

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|-----------------------------------------------------Operations----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator
rb_tree<_Ty2, _Compare, _Alloc2>::find(const key_type &_val)
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_Tmp->__value_field, _val))
		{
			_res_p = _Tmp;
			_Tmp = __left(_Tmp);
		}
		else
			_Tmp = __right(_Tmp);
	}

	iterator _res_it = iterator(_res_p);
	return ( (_res_it == end() || _compare(_val, _res_it.base()->__value_field ) ) ? end() : _res_it );
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::const_iterator
rb_tree<_Ty2, _Compare, _Alloc2>::find(const key_type &_val) const
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_Tmp->__value_field, _val))
		{
			_res_p = _Tmp;
			_Tmp = __left(_Tmp);
		}
		else
			_Tmp = __right(_Tmp);
	}

	const_iterator _res_it = const_iterator(_res_p);
	return ( (_res_it == end() || _compare(_val, _res_it.base()->__value_field ) ) ? end() : _res_it );
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::size_type
rb_tree<_Ty2, _Compare, _Alloc2>::count(const key_type &_val) const
{
	ft::pair<iterator, iterator> _Tmp = equal_range(_val);
	size_type _res = ft::distance(_Tmp.first, _Tmp.second);
	return (_res);
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator
rb_tree<_Ty2, _Compare, _Alloc2>::lower_bound(const key_type &_val)
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_Tmp->__value_field, _val))
		{
			_res_p = _Tmp;
			_Tmp = __left(_Tmp);
		}
		else
			_Tmp = __right(_Tmp);
	}
	return (iterator(_Tmp));
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::const_iterator
rb_tree<_Ty2, _Compare, _Alloc2>::lower_bound(const key_type &_val) const
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_Tmp->__value_field, _val))
		{
			_res_p = _Tmp;
			_Tmp = __left(_Tmp);
		}
		else
			_Tmp = __right(_Tmp);
	}
	return (const_iterator(_Tmp));
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator
rb_tree<_Ty2, _Compare, _Alloc2>::upper_bound(const key_type &_val)
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (_compare(_val, _Tmp->__value_field))
		{
			_res_p = _Tmp;
			_Tmp = __left(_Tmp);
		}
		else
			_Tmp = __right(_Tmp);
	}
	return (iterator(_Tmp));
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _Compare, _Alloc2>::const_iterator
rb_tree<_Ty2, _Compare, _Alloc2>::upper_bound(const key_type &__x) const
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (_compare(_val, _Tmp->__value_field))
		{
			_res_p = _Tmp;
			_Tmp = __left(_Tmp);
		}
		else
			_Tmp = __right(_Tmp);
	}
	return (const_iterator(_Tmp));
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator>
rb_tree<_Ty2, _Compare, _Alloc2>::equal_range(const key_type &_val)
{
	return pair<iterator, iterator>(lower_bound(_val), upper_bound(_val));
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::const_iterator, typename rb_tree<_Ty2, _Compare, _Alloc2>::const_iterator>
rb_tree<_Ty2, _Compare, _Alloc2>::equal_range(const key_type &_val) const
{
	return pair<const_iterator, const_iterator>(lower_bound(_val), upper_bound(_val));
}


/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|---------------------------------------------------RB_Tree_Methods-------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/


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
	catch(...)
	{
		__erase(_top);
		throw ;
	}
	return (_top);
}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|---------------------------------------------------RB_Tree_Methods-------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/


template <typename _Ty2, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _Compare, _Alloc2>::__erase(pointer __p)
{
	while (__p != _nil)
	{
		__erase(__right(__p));
		pointer _Tmp = __left(__p);
		__destroy_node(__p);
		__p = _Tmp;
	}
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
ft::pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, bool>
rb_tree<_Ty2, _Compare, _Alloc2>::__insert_node(const _Ty2& _data)
{
	pointer parent = _nil;
	pointer tail = (pointer&)(_nil->__parent);

	while (tail != 0 && tail != _nil)
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
		tail->__parent = _nil;
	}
	else if (_compare(_data, parent->__value_field))
	{
		parent->__left = tail;
		tail->__parent = parent;
	}
	else
	{
		parent->__right = tail;
		tail->__parent = parent;
	}
	++this->_count;
	__revalance(tail);
	return ( typename ft::pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, bool>(iterator(tail), true) );
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
ft::pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, bool>
rb_tree<_Ty2, _Compare, _Alloc2>::__insert_node(pointer __root, const _Ty2& _data)
{
	pointer parent;
	pointer tail;
	if (__root == _nil)
	{
		parent = _nil;
		tail = (pointer&)(_nil->__parent);
	}
	else
	{
		parent = __root->__parent;
		tail = __root;
	}

	while (tail != 0 && tail != _nil)
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
		tail->__parent = _nil;
	}
	else if (_compare(_data, parent->__value_field))
	{
		parent->__left = tail;
		tail->__parent = parent;
	}
	else
	{
		parent->__right = tail;
		tail->__parent = parent;
	}
	++this->_count;
	__revalance(tail);
	return ( typename ft::pair<typename rb_tree<_Ty2, _Compare, _Alloc2>::iterator, bool>(iterator(tail), true) );
}


// template <typename _Ty2, typename _Compare, typename _Alloc2>
// void rb_tree<_Ty2, _Compare, _Alloc2>::erase(iterator __position)
// {
// 	pointer __p = __position.base();
// 	pointer _Tmp;
// 	if (__left(__p) != _nil)
// 	{
// 		_Tmp = __maximum_node(__left(__p));
// 		__destroy(__p);
// 		__construct(&__p->__value_field, _Tmp->__value_field);
// 		__destroy_node(_Tmp);
// 	}
// 	else
// 	{

// 	}
// 	if (__p == __p->__parent->__left)
// 	{
// 			_Tmp = __p->__right;
// 			__p->__parent->__left = _Tmp;
// 			__parent(_Tmp) = __p->__parent;
// 			__destroy_node(__p);
// 	}
// 	else
// 	{
// 			_Tmp = __p->__right;
// 			__p->__parent->__right = _Tmp;
// 			__parent(_Tmp) = __p->__parent;
// 			__destroy_node(__p);
// 	}
// 	__revalance(_Tmp);
// }


template <typename _Ty2, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _Compare, _Alloc2>::preorder(pointer root, std::string *stringBuilder, std::string padding, const std::string &__pointer, const bool hasRightChild) const
{
	std::string* paddingBuilder;	// 이 loop에서 stringBuilder에 append할 문자열을 의미한다.
	if (root == _nil) return;
	else 
	{
		paddingBuilder = new std::string(padding);
		stringBuilder->append("\n").append(padding).append(__pointer);
		if (root->__color == __rb_tree_black) stringBuilder->append("B");
		else stringBuilder->append("R");
		stringBuilder->append(std::to_string(root->__value_field));

		if (hasRightChild) paddingBuilder->append("│  ");
		else paddingBuilder->append("   ");
	}

	// [재귀함수]
	preorder(root->__left, stringBuilder, *paddingBuilder, "├──", root->__right != nullptr);
	preorder(root->__right, stringBuilder, *paddingBuilder, "└──", false);

	delete paddingBuilder;		// 메모리 누수를 막자.
}

template <typename _Ty2, typename _Compare, typename _Alloc2>
std::string rb_tree<_Ty2, _Compare, _Alloc2>::show_tree() const
{
	pointer root = _nil->__parent;
	if (this->_count == 0) 
	{	// [오류]: 비어있는 BST에 대한 'show'함수 호출은 오류상황이다.
		std::cout << "[ERROR] Can't perform 'show' function on empty tree!" << std::endl;
		return "";
	}

	std::string* str = new std::string();	// BST 전체를 preorder로 출력할 문자열 포인터를 생성한다.
	if (root->__color == __rb_tree_black) str->append("B");
	else str->append("R");
	str->append(std::to_string(root->__value_field));		// 우선 문자열에 root 노드의 key를 넣어준다.

	// [본격적인 재귀 함수 시작 부분] 
	preorder(root->__left, str, "", "├──", root->__right != nullptr);
	preorder(root->__right, str, "", "└──", false);

	// 재귀함수가 끝나면 문자열에는 전체 BST의 출력문이 들어있게 된다.
	std::string returnStr = *str;	// 문자열 포인터를 삭제해주기 위해 지역변수에 복사한다.
	delete str;						// 문자열 포인터를 delete해서 메모리 누수를 막는다.
	return returnStr;				// 지역변수를 넘겨주고 프로그램 종료시 컴파일러가 삭제하게 맡긴다.
}

_FT_END
#endif
