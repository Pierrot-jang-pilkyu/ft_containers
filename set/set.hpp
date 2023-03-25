#ifndef SET_HPP
#define SET_HPP

#include "../etc/pair.hpp"
#include "../etc/rb_tree.hpp"
#include "../etc/iterator.hpp"
#include "../etc/algorithm.hpp"
#include "../etc/type_traits.hpp"
#include "../etc/iterator_traits.hpp"
#include "../etc/basic_macro.hpp"

#include <memory>
#include <functional>

_FT_BEGIN

template <typename _Key, typename _Compare = std::less<_Key>, typename _Alloc = std::allocator<_Key> >
class set;

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator==(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right);

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator<(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right);

template <typename _Key, typename _Compare, typename _Alloc>
class set
{
public:
	typedef _Key					key_type;
	typedef _Key					value_type;
	typedef _Compare				key_compare;
	typedef _Compare				value_compare;

private:
	typedef ft::rb_tree<value_type, __key_of_value<value_type>, _Compare, _Alloc>	rb_tree_type;

	rb_tree_type _t;

public:
	typedef typename rb_tree_type::pointer						pointer;
	typedef typename rb_tree_type::const_pointer				const_pointer;
	typedef typename rb_tree_type::reference					reference;
	typedef typename rb_tree_type::const_reference				const_reference;
	typedef typename rb_tree_type::iterator						iterator;
	typedef typename rb_tree_type::const_iterator				const_iterator;
	typedef typename rb_tree_type::reverse_iterator				reverse_iterator;
	typedef typename rb_tree_type::const_reverse_iterator		const_reverse_iterator;
	typedef typename rb_tree_type::size_type					size_type;
	typedef typename rb_tree_type::difference_type				difference_type;
	typedef typename rb_tree_type::allocator_type				allocator_type;

/*
**	|------------------------------------------------------Member_function----------------------------------------------------|


**	|-------------------------------------------------------------------------------------------------------------------------|
**	|---------------------------------------------Othodox_Canonical_Form + Alpha----------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	set() : _t(_Compare(), allocator_type()) {}
	explicit set(const _Compare& __comp, const allocator_type& __a = allocator_type()) : _t(__comp, __a) {}

	template <typename _input_iterator>
	set(_input_iterator _first, _input_iterator _last)
	: _t(_Compare(), allocator_type())
	{
		_t.insert(_first, _last);
	}

	template <typename _input_iterator>
	set(_input_iterator _first, _input_iterator _last, const _Compare& __comp, const allocator_type& __a = allocator_type())
	: _t(__comp, __a)
	{
		_t.insert(_first, _last);
	}

	set(const set<_Key, _Compare, _Alloc>& __m) : _t(__m._t) {}

	set<_Key, _Compare, _Alloc>& operator=(const set<_Key, _Compare, _Alloc>& __m)
	{
		_t = __m._t;
		return (*this);
	}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Accessors----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	key_compare key_comp() const { return _t.key_comp(); }
	value_compare value_comp() const { return value_compare(_t.key_comp()); }
	allocator_type get_allocator() const { return _t.get_allocator(); }

	iterator begin() { return _t.begin(); }
	const_iterator begin() const { return _t.begin(); }
	iterator end() { return _t.end(); }
	const_iterator end() const { return _t.end(); }
	reverse_iterator rbegin() { return _t.rbegin(); }
	const_reverse_iterator rbegin() const { return _t.rbegin(); }
	reverse_iterator rend() { return _t.rend(); }
	const_reverse_iterator rend() const { return _t.rend(); }
	bool empty() const { return _t.empty(); }
	size_type size() const { return _t.size(); }
	size_type max_size() const { return _t.max_size(); }

	void swap(set<_Key, _Compare, _Alloc>& __m) { _t.swap(__m._t); }

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Modifiers----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	ft::pair<iterator, bool> insert(const value_type& _val) { return (_t.insert(_val)); }
	iterator insert(iterator _pos, const value_type& _val) { return (_t.insert(_pos, _val)); }
	template <typename _input_iterator>
	void insert(_input_iterator _first, _input_iterator _last) { _t.insert(_first, _last); }

	void erase(iterator _pos) { _t.erase(_pos); }
	size_type erase(const key_type& __k) { return (_t.erase(__k)); }
	void erase(iterator _first, iterator _last) { _t.erase(_first, _last); }

	void clear() { _t.clear(); }

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|--------------------------------------------------------Lookup-----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	iterator find(const key_type& _val) { return _t.find(_val); }
	size_type count(const key_type& _val) const
	{
		return _t.find(_val) == _t.end() ? 0 : 1; 
	}
	iterator lower_bound(const key_type& _val) {return _t.lower_bound(_val); }
	iterator upper_bound(const key_type& _val) {return _t.upper_bound(_val); }

	pair<iterator,iterator> equal_range(const key_type& _val)
	{
		return _t.equal_range(_val);
	}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|--------------------------------------------------Relational_Operator----------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	template <typename _Key1, typename _Comp1, typename _Alloc1>
	friend bool operator== (const set<_Key1, _Comp1, _Alloc1>&, const set<_Key1, _Comp1, _Alloc1>&);
	template <typename _Key1, typename _Comp1, typename _Alloc1>
	friend bool operator< (const set<_Key1, _Comp1, _Alloc1>&, const set<_Key1, _Comp1, _Alloc1>&);
};

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator==(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right)
{
  return ( _Left._t == _Right._t );
}

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator<(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right)
{
  return ( _Left._t < _Right._t );
}

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator!=(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right)
{
  return !( _Left == _Right );
}

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator>(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right)
{
  return ( _Right < _Left );
}

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator<=(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right)
{
  return !( _Right < _Left );
}

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator>=(const set<_Key, _Compare, _Alloc>& _Left, const set<_Key, _Compare, _Alloc>& _Right)
{
  return !( _Left < _Right );
}

template <typename _Key, typename _Compare, typename _Alloc>
inline void swap(const set<_Key, _Compare, _Alloc>& _m1, const set<_Key, _Compare, _Alloc>& _m2)
{
	_m1.swap(_m2);
}

_FT_END
#endif