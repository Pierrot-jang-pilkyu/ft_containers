#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "pair.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "basic_macro.hpp"
#include "iterator_traits.hpp"
#include <memory>
#include <stdexcept>

_FT_BEGIN

typedef int __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = 0;
const __rb_tree_color_type __rb_tree_black = 1;
const __rb_tree_color_type __rb_tree_red_n_black = 2;
const __rb_tree_color_type __rb_tree_doubly_black = 3;

template <typename _Ty>
struct __rb_tree_node
{
	typedef bidirectional_iterator_tag	iterator_category;
	typedef __rb_tree_node<_Ty>			value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef __rb_tree_node<_Ty>*		pointer;
	typedef __rb_tree_node<_Ty>&		reference;
	typedef __rb_tree_color_type		__color_type;

	__color_type					__color;
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

template <typename _Iter, typename _Ty>
class __rb_tree_iterator 
{
public:
	// Member type
	typedef _Iter													iterator_type;
	typedef typename __rb_tree_node<_Ty>::iterator_category			iterator_category;
	typedef typename __rb_tree_node<_Ty>::value_type				value_type;
	typedef typename __rb_tree_node<_Ty>::difference_type			difference_type;
	typedef value_type*												node_pointer;
	typedef value_type&												node_reference;
	typedef _Ty*													pointer;
	typedef _Ty&													reference;
	typedef typename std::remove_cv<_Iter>::type					non_const_iter_type;

protected:
	node_pointer current;
	node_pointer _nil;

	void __get_nil()
	{
		node_pointer _Tmp(current);
		if (_Tmp->__parent == 0 || _Tmp->__left == _Tmp)
		{
			_nil = _Tmp;
			return ;
		}
		while (_Tmp != _Tmp->__parent->__parent)
			_Tmp = _Tmp->__parent;
		if (_Tmp == _Tmp->__parent->__parent)
			_nil = _Tmp->__parent;
	}

	void __increment()
	{
		__get_nil();
		node_pointer __node(current);
		if (__node->__right != _nil)
		{
			__node = __node->__right;
			while (__node->__left != _nil)
				__node = __node->__left;
		}
		else
		{
			node_pointer _Tmp = __node->__parent;
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
		node_pointer __node(current);
		if (__node == _nil)
		{
			node_pointer __root(_nil->__parent);
			while ( __root->__right != _nil )
				__root = __root->__right;
			__node = __root;
		}
		else if (__node->__left != _nil)
		{
			__node = __node->__left;
			while (__node->__right != _nil)
				__node = __node->__right;
		}
		else
		{
			node_pointer _Tmp = __node->__parent;
			while (__node == _Tmp->__left)
			{
				__node = _Tmp;
				_Tmp = _Tmp->__parent;
			}
			__node = _Tmp;
		}
		current = __node;
	}

public:

	// Member Function
	__rb_tree_iterator() : current(_Iter()) {}
	explicit __rb_tree_iterator (const iterator_type& _It) : current(_It) {}
	// Allow iterator to const_iterator conversion
	template <typename _Iter2>
	__rb_tree_iterator (const __rb_tree_iterator<_Iter2, _Ty>& _It) : current(_It.base()) {}
	__rb_tree_iterator &operator=(const __rb_tree_iterator<_Iter, _Ty>& _Right)
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
		return (current->__value_field);
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
		__rb_tree_iterator _Tmp = *this;
		__increment();
		return ( _Tmp );
	}

	// bidirectional_iterator requirements

	__rb_tree_iterator &operator--()
	{
		__decrement();
		return (*this);
	}

	__rb_tree_iterator operator--(int)
	{
		__rb_tree_iterator _Tmp = *this;
		__decrement();
		return ( _Tmp );
	}
};

template<typename _IterL, typename _IterR, typename _Ty>
inline bool operator==(const __rb_tree_iterator<_IterL, _Ty>& _Left, const __rb_tree_iterator<_IterR, _Ty>& _Right)
{
	return ( _Left.base() == _Right.base() );
}

template<typename _IterL, typename _IterR, typename _Ty>
inline bool operator!=(const __rb_tree_iterator<_IterL, _Ty>& _Left, const __rb_tree_iterator<_IterR, _Ty>& _Right)
{
	return ( _Left.base() != _Right.base() );
}

template <typename _Ty, typename _KeyOfValue = ft::__key_of_value<_Ty>, typename _Compare = std::less<_Ty>, typename _Alloc = std::allocator<__rb_tree_node<_Ty> > >
class rb_tree
{
private:
	typedef rb_tree<_Ty, _KeyOfValue, _Compare, _Alloc>					rb_tree_type;

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
	typedef __rb_tree_iterator<pointer, _Ty>				iterator;
	typedef __rb_tree_iterator<const pointer, _Ty>			const_iterator;
	typedef reverse_iterator<const_iterator>				const_reverse_iterator;
	typedef reverse_iterator<iterator>						reverse_iterator;

protected:
	allocator_type		_data_allocator;
	_Compare			_compare;
	_KeyOfValue			_key_of_value;
	size_type			_count;
	pointer				_nil;

	pointer __minimum_node(pointer __root)
	{
		while ( __root->__left != _nil )
			__root = __root->__left;
		return ( __root );
	}

	pointer __maximum_node(pointer __root)
	{
		while ( __root->__right != _nil )
			__root = __root->__right;
		return ( __root );
	}

	pointer __minimum_node(pointer __root) const
	{
		while ( __root->__left != _nil )
			__root = __root->__left;
		return ( __root );
	}

	pointer __maximum_node(pointer __root) const
	{
		while ( __root->__right != _nil )
			__root = __root->__right;
		return ( __root );
	}

	pointer& __root() const
	{
		return ( (pointer&)_nil->__parent );
	}

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

	pointer __get_change_node(pointer _cur)
	{
		if (_cur->__left != _nil)	// predecessor - 선임자
			return (__maximum_node(_cur->__left));
		else if (_cur->__right != _nil) // successor - 후임자
			return (__minimum_node(_cur->__right));
		else
			return (_nil);
	}

	template <typename _input_iterator>
	difference_type
	__distance(_input_iterator _first, _input_iterator _last)
	{
		difference_type __r(0);

		for (; _first != _last; ++_first)
			++__r;
		return (__r);
	}

	void __erase_base(pointer __node);
	void __erase_revalance(pointer _doubly_black, int _case, bool _left_right);
	void __erase_get_case(pointer _doubly_black, int& _case, bool& _left_right);
	void __erase_case1(pointer _doubly_black, bool _left_right);
	void __erase_case2(pointer _doubly_black, bool _left_right);
	void __erase_case3(pointer _doubly_black, bool _left_right);
	void __erase_case4(pointer _doubly_black, bool _left_right);

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
**	|------------------------------------------------------Accessors----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	compare_type key_comp() const { return ( _compare ); }

	iterator begin()
	{
		if (_nil->__parent == 0)
			return ( iterator(_nil) );
		return ( iterator(__minimum_node(_nil->__parent)) );
	}
	const_iterator begin() const
	{
		if (_nil->__parent == 0)
			return ( const_iterator(_nil) );
		return ( const_iterator(__minimum_node(_nil->__parent)) );
	}
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
		_data_allocator.deallocate(__p, 1);
	}

	void __construct(_Ty* __p, const _Ty& _val)
	{
		if (__p)
			new ((void*)__p) _Ty(_val);
	}

	void __destroy(pointer _pos)
	{
		(&_pos->__value_field)->~_Ty();
	}

	pointer __create_node(const _Ty& __val)
	{
		pointer _Tmp = __get_node();
		_Tmp->__color = __rb_tree_red;
		(pointer&)_Tmp->__left = _nil;
		(pointer&)_Tmp->__right = _nil;
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
		(pointer&)_Tmp->__right = _nil;
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

	pointer __get_nil(pointer __node)
	{
		pointer _Tmp(__node);
		if (_Tmp->__parent == 0 || _Tmp->__left == _Tmp)
			return (__node);
		while (_Tmp != _Tmp->__parent->__parent)
			_Tmp = _Tmp->__parent;
		if (_Tmp == _Tmp->__parent->__parent)
			return (_Tmp->__parent);
		return ((pointer) 0);
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
	size_type max_size() const { return ( size_type(-1) ); }
	bool empty() const { return ( _count == 0 ); }

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
			__initialize();
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
		__put_node(_nil);
	}

	rb_tree_type& operator=(const rb_tree_type& __t);

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Modifiers----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	void swap(rb_tree<_Ty, _KeyOfValue, _Compare, _Alloc>& __t)
	{
		ft::swap(this->_nil, __t._nil);
		ft::swap(this->_count, __t._count);
		ft::swap(this->_compare, __t._compare);
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

	void erase(iterator __position);
	size_type erase(const key_type &_val);
	void erase(iterator __first, iterator __last);

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

	iterator find(const key_type& _val);
	const_iterator find(const key_type& _val) const;
	size_type count(const key_type& _val) const;
	iterator lower_bound(const key_type& _val);
	const_iterator lower_bound(const key_type& _val) const;
	iterator upper_bound(const key_type& _val);
	const_iterator upper_bound(const key_type& _val) const;
	pair<iterator, iterator> equal_range(const key_type& _val);
	pair<const_iterator, const_iterator> equal_range(const key_type& _val) const;
};


/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|--------------------------------------------------Relational_Operator----------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
inline bool 
operator==(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Right)
{
  return ( ( _Left.size() == _Right.size() ) && ( ft::equal(_Left.begin(), _Left.end(), _Right.begin()) ) );
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
inline bool 
operator<(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Right)
{
  return ( ft::lexicographical_compare(_Left.begin(), _Left.end(), _Right.begin(), _Right.end()) );
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
inline bool 
operator!=(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Right)
{
  return !(_Left == _Right);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
inline bool 
operator>(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Right)
{
  return (_Right < _Left);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
inline bool 
operator<=(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Left, const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Right)
{
  return !(_Right < _Left);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
inline bool 
operator>=(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Left,  const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& _Right)
{
  return !(_Left < _Right);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void swap(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& __t1, const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& __t2)
{
	__t1.swap(__t2);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::operator=(const rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>& __t)
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

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::find(const key_type &_val)
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_key_of_value(_Tmp->__value_field), _key_of_value(_val)))
		{
			_res_p = _Tmp;
			_Tmp = _Tmp->__left;
		}
		else
			_Tmp = _Tmp->__right;
	}

	iterator _res_it = iterator(_res_p);
	return ( (_res_it == end() || _compare(_key_of_value(_val), _key_of_value(_res_it.base()->__value_field) ) ) ? end() : _res_it );
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::const_iterator
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::find(const key_type &_val) const
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_key_of_value(_Tmp->__value_field), _key_of_value(_val)))
		{
			_res_p = _Tmp;
			_Tmp = _Tmp->__left;
		}
		else
			_Tmp = _Tmp->__right;
	}

	const_iterator _res_it = const_iterator(_res_p);
	return ( (_res_it == end() || _compare(_key_of_value(_val), _key_of_value(_res_it.base()->__value_field) ) ) ? end() : _res_it );
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::size_type
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::count(const key_type &_val) const
{
	ft::pair<iterator, iterator> _Tmp = equal_range(_val);
	size_type _res = __distance(_Tmp.first, _Tmp.second);
	return (_res);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::lower_bound(const key_type &_val)
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_key_of_value(_Tmp->__value_field), _key_of_value(_val)))
		{
			_res_p = _Tmp;
			_Tmp = _Tmp->__left;
		}
		else
		{
			_Tmp = _Tmp->__right;
		}
	}
	return (iterator(_res_p));
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::const_iterator
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::lower_bound(const key_type &_val) const
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (!_compare(_key_of_value(_Tmp->__value_field), _key_of_value(_val)))
		{
			_res_p = _Tmp;
			_Tmp = _Tmp->__left;
		}
		else
			_Tmp = _Tmp->__right;
	}
	return (const_iterator(_res_p));
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::upper_bound(const key_type &_val)
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (_compare(_key_of_value(_val), _key_of_value(_Tmp->__value_field)))
		{
			_res_p = _Tmp;
			_Tmp = _Tmp->__left;
		}
		else
			_Tmp = _Tmp->__right;
	}
	return (iterator(_res_p));
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::const_iterator
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::upper_bound(const key_type &_val) const
{
	pointer _res_p = _nil;
	pointer _Tmp = __root();

	while (_Tmp != 0 && _Tmp != _nil)
	{
		if (_compare(_key_of_value(_val), _key_of_value(_Tmp->__value_field)))
		{
			_res_p = _Tmp;
			_Tmp = _Tmp->__left;
		}
		else
			_Tmp = _Tmp->__right;
	}
	return (const_iterator(_res_p));
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator, typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator>
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::equal_range(const key_type &_val)
{
	return pair<iterator, iterator>(lower_bound(_val), upper_bound(_val));
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::const_iterator, typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::const_iterator>
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::equal_range(const key_type &_val) const
{
	return pair<const_iterator, const_iterator>(lower_bound(_val), upper_bound(_val));
}


/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|---------------------------------------------------RB_Tree_Methods-------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/


template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__left_rotate(pointer __node)
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


template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__right_rotate(pointer __node)
{
	pointer _Tmp = (pointer&)__node->__left;

	__node->__left = _Tmp->__right;

	if (_Tmp->__right != _nil)
		(pointer&)_Tmp->__right->__parent = __node;

	__parent(_Tmp) = __node->__parent;

	if (__parent(__node)== _nil)
		_nil->__parent = _Tmp;	// root setting
	else if ((pointer&)__node->__parent->__left == __node)
		(pointer&)__node->__parent->__left = _Tmp;
	else
		(pointer&)__node->__parent->__right = _Tmp;

	_Tmp->__right = __node;
	__parent(__node)= _Tmp;
}


template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__revalance(pointer __node)
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


template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::pointer
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__copy(pointer __x, pointer __p)
{
	if (__x == 0 || __p == 0)
		return ( pointer(__get_node()) );
	pointer _top = __clone_node(__x);
	pointer _x_nil = __get_nil(__x);
	__parent(_top) = __p;

	try
	{
		if (__x->__right != _x_nil)
			__right(_top) = __copy(__right(__x), _top);
		else
			__right(_top) = _nil;
		__p = _top;
		__x = __left(__x);

		while (__x != _x_nil)
		{
			pointer _Tmp = __clone_node(__x);
			__left(__p) = _Tmp;
			__parent(_Tmp) = __p;
			if (__x->__right != _x_nil)
				_Tmp->__right = __copy(__right(__x), _Tmp);
			else
				_Tmp->__right = _nil;
			__p = _Tmp;
			__x = __left(__x);
		}
		__left(__p) = _nil;
	}
	catch(...)
	{
		__erase(_top);
		throw ;
	}
	return (_top);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase_base(pointer __node)
{
	int		_case = 0;
	bool	_left_right;
	pointer	parent = __node->__parent;
	pointer change_node = NULL;

	if (__node->__left == _nil && __node->__right == _nil)
	{
		if (__node->__color == __rb_tree_red)
		{
			if (__node == parent->__left)
				parent->__left = _nil;
			else if (__node == parent->__right)
				parent->__right = _nil;
			__destroy_node(__node);
		}
		else if (__node->__color == __rb_tree_black)
		{
			if (parent == _nil)
			{
				parent->__parent = 0;
				__destroy_node(__node);
			}
			pointer _Tmp_nil = __get_node();
			_Tmp_nil->__color = __rb_tree_doubly_black;
			_Tmp_nil->__left = 0;
			_Tmp_nil->__right = 0;
			_Tmp_nil->__parent = parent;
			if (__node == parent->__left)
				parent->__left = _Tmp_nil;
			else if (__node == parent->__right)
				parent->__right = _Tmp_nil;
			__destroy_node(__node);
			__erase_get_case(_Tmp_nil, _case, _left_right);
			__erase_revalance(_Tmp_nil, _case, _left_right);
			if (_Tmp_nil == _Tmp_nil->__parent->__left)
				_Tmp_nil->__parent->__left = _nil;
			else if (_Tmp_nil == _Tmp_nil->__parent->__right)
				_Tmp_nil->__parent->__right = _nil;
			__put_node(_Tmp_nil);
		}
	}
	else if ((__node->__left != _nil && __node->__right == _nil) || (__node->__left == _nil && __node->__right != _nil))
	{
		if (__node->__left != _nil)
			change_node = __node->__left;
		else if (__node->__right != _nil)
			change_node = __node->__right;
		if (__node == parent->__left)
			parent->__left = change_node;
		else if (__node == parent->__right)
			parent->__right = change_node;
		else if (__node->__parent == _nil)
			_nil->__parent = change_node;
		change_node->__parent = parent;
		if (__node->__color == __rb_tree_black)
		{
			if (change_node->__color == __rb_tree_red)	// red_n_black
				change_node->__color = __rb_tree_black;
			else if (change_node->__color == __rb_tree_black)
			{
				change_node->__color = __rb_tree_doubly_black;
				__erase_get_case(change_node, _case, _left_right);
				__erase_revalance(change_node, _case, _left_right);
			}
		}
		__destroy_node(__node);
	}
	else // __node->__left != _nil && __node->__right != _nil
	{
		change_node = __get_change_node(__node); // change_node->__left == _nil || change_node->__right == _nil;
		ft::swap(__node->__value_field, change_node->__value_field);
		__erase_base(change_node);
	}
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase_revalance(pointer _doubly_black, int _case, bool _left_right)
{
	switch (_case)
	{
	case 1:
		__erase_case1(_doubly_black, _left_right);
		break;
	case 2:
		__erase_case2(_doubly_black, _left_right);
		break;
	case 3:
		__erase_case3(_doubly_black, _left_right);
		break;
	case 4:
		__erase_case4(_doubly_black, _left_right);
		break;
	default:
		break;
	}

}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase_get_case(pointer _doubly_black, int& _case, bool& _left_right)
{
	pointer parent = _doubly_black->__parent;
	pointer brother = 0;

	if (_doubly_black == parent->__left)
	{
		_left_right = LEFT;
		brother = parent->__right;
	}
	else if (_doubly_black == parent->__right)
	{
		_left_right = RIGHT;
		brother = parent->__left;
	}
	if (brother->__color == __rb_tree_red)
		_case = 1;
	else if (brother->__color == __rb_tree_black)
	{
		if (brother->__left->__color == __rb_tree_black && brother->__right->__color == __rb_tree_black)
			_case = 2;
		else if (brother->__left->__color == __rb_tree_red && brother->__right->__color == __rb_tree_black)
			_case = 3;
		else _case = 4;
	}
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase_case1(pointer _doubly_black, bool _left_right)
{
	int		_case = 0;
	pointer	parent = _doubly_black->__parent;
	pointer	brother = 0;
	if (_left_right == LEFT)
	{
		brother = parent->__right;
		ft::swap(parent->__color, brother->__color);
		__left_rotate(parent);
	}
	else if (_left_right == RIGHT)
	{
		brother = parent->__left;
		ft::swap(parent->__color, brother->__color);
		__right_rotate(parent);
	}
	__erase_get_case(_doubly_black, _case, _left_right);
	__erase_revalance(_doubly_black, _case, _left_right);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase_case2(pointer _doubly_black, bool _left_right)
{
	int		_case = 0;
	pointer	parent = _doubly_black->__parent;
	pointer	brother = 0;
	if (_left_right == LEFT)
		brother = parent->__right;
	else if (_left_right == RIGHT)
		brother = parent->__left;
	_doubly_black->__color = __rb_tree_black;
	brother->__color = __rb_tree_red;
	if (parent->__color == __rb_tree_red || parent->__parent == _nil)
	{
		parent->__color = __rb_tree_black;
		return ;
	}
	parent->__color = __rb_tree_doubly_black;
	__erase_get_case(parent, _case, _left_right);
	__erase_revalance(parent, _case, _left_right);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase_case3(pointer _doubly_black, bool _left_right)
{
	pointer parent = _doubly_black->__parent;
	pointer brother = 0;
	pointer nephew = 0;
	if (_left_right == LEFT)
	{
		brother = parent->__right;
		nephew = parent->__left;
		ft::swap(brother->__color, nephew->__color);
		__right_rotate(brother);
	}
	else if (_left_right == RIGHT)
	{
		brother = parent->__left;
		nephew = parent->__right;
		ft::swap(brother->__color, nephew->__color);
		__left_rotate(brother);
	}
	__erase_case4(_doubly_black, _left_right);
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase_case4(pointer _doubly_black, bool _left_right)
{
	pointer parent = _doubly_black->__parent;
	pointer brother = 0;
	if (_left_right == LEFT)
	{
		brother = parent->__right;
		brother->__color = parent->__color;
		brother->__right->__color = __rb_tree_black;
		parent->__color = __rb_tree_black;
		__left_rotate(parent);
	}
	else if (_left_right == RIGHT)
	{
		brother = parent->__left;
		brother->__color = parent->__color;
		brother->__left->__color = __rb_tree_black;
		parent->__color = __rb_tree_black;
		__right_rotate(parent);
	}
}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|-------------------------------------------------------Modifiers---------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/


template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__erase(pointer __p)
{
	while (__p != _nil)
	{
		__erase(__right(__p));
		pointer _Tmp = __left(__p);
		__destroy_node(__p);
		__p = _Tmp;
	}
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
ft::pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator, bool>
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__insert_node(const _Ty2& _data)
{
	pointer parent = _nil;
	pointer tail = (pointer&)(_nil->__parent);

	while (tail != 0 && tail != _nil)
	{
		// parent : nil -> root, tail : root -> left or right.
		parent = tail;
		_Ty2 var = tail->__value_field;
		if (_key_of_value(_data) == _key_of_value(var)) // iterator.base()->__value_field == _data
			return ( typename ft::pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator, bool>(iterator(tail), false) );
		else if (_compare(_key_of_value(_data), _key_of_value(var)))
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
	else if (_compare(_key_of_value(_data), _key_of_value(parent->__value_field)))
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
	return ( typename ft::pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator, bool>(iterator(tail), true) );
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
ft::pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator, bool>
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::__insert_node(pointer __root, const _Ty2& _data)
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
		if (_key_of_value(_data) == _key_of_value(var)) // iterator.base()->__value_field == _data
			return ( typename ft::pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator, bool>(iterator(tail), false) );
		else if (_compare(_key_of_value(_data), _key_of_value(var)))
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
	else if (_compare(_key_of_value(_data), _key_of_value(parent->__value_field)))
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
	return ( typename ft::pair<typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::iterator, bool>(iterator(tail), true) );
}


template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::erase(iterator __position)
{
	pointer __node = __position.base();
	__erase_base(__node);
	_count--;
}

template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
typename rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::size_type
rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::erase(const key_type &_val)
{
	ft::pair<iterator, iterator> __p = equal_range(_val);
	size_type __n = __distance(__p.first, __p.second);
	erase(__p.first, __p.second);
	return (__n);
}


template <typename _Ty2, typename _KeyOfValue, typename _Compare, typename _Alloc2>
void rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2>::erase(iterator __first, iterator __last)
{
	if (__first == begin() && __last == end())
		clear();
	else
	{
		rb_tree<_Ty2, _KeyOfValue, _Compare, _Alloc2> _Tmp;
		_Tmp.insert(begin(), end());
		iterator _Tmp_first = _Tmp.find(*__first);
		iterator _Tmp_last = __last.base() == _nil ? _Tmp.end() : _Tmp.find(*__last);
		iterator _del_one;
		while (_Tmp_first != _Tmp_last)
		{
			_del_one = find(*_Tmp_first);
			erase(_del_one);
			_Tmp_first++;
		}
	}
}

_FT_END
#endif
