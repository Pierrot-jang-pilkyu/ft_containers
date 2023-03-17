#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "../etc/iterator.hpp"
#include "../etc/algorithm.hpp"
#include "../etc/type_traits.hpp"
#include <memory>
#include <stdexcept>

_FT_BEGIN
template <typename _Ty, typename _Alloc = std::allocator<_Ty> >
class vector
{
private:
	typedef vector<_Ty, _Alloc>					vector_type;

public:
	// Member type
	typedef _Ty												value_type;
	typedef _Alloc											allocator_type;
	typedef value_type*										pointer;
	typedef const value_type*								const_pointer;
	typedef value_type&										reference;
	typedef const value_type&								const_reference;
	typedef std::ptrdiff_t									difference_type;
	typedef std::size_t										size_type;

	// Membertype - iterator
	typedef __normal_iterator<pointer, vector_type>			iterator;
	typedef __normal_iterator<const_pointer, vector_type>	const_iterator;
	typedef reverse_iterator<const_iterator>				const_reverse_iterator;
	typedef reverse_iterator<iterator>						reverse_iterator;

protected:
	allocator_type	_data_allocator;
	pointer			_start;
	pointer			_finish;
	pointer			_end_of_storage;

	// custom function
	pointer _allocate(size_type __n)
	{
		return ( _data_allocator.allocate(__n) );
	}

	template <class _input_iterator, class _forward_iterator>
	_forward_iterator uninitialized_copy(_input_iterator _first, _input_iterator _last, _forward_iterator _result)
	{
		for (; _first != _last; ++_result, ++_first)
			new (static_cast<void *>(&*_result))
				typename iterator_traits<_forward_iterator>::value_type(*_first);
		return ( _result );
	}

	template <class _forward_iterator, class _Ty2>
	_forward_iterator uninitialized_fill(_forward_iterator _first, _forward_iterator _last, const _Ty2 &_val)
	{
		for (; _first != _last; ++_first)
			new (static_cast<void *>(&*_first))
				typename iterator_traits<_forward_iterator>::value_type(_val);
		return ( _last );
	}

	template <class _forward_iterator, class _size, class _Ty2>
	_forward_iterator uninitialized_fill_n(_forward_iterator _first, _size __n, const _Ty2 &_val)
	{
		for (; __n--; ++_first)
			new (static_cast<void *>(&*_first))
				typename iterator_traits<_forward_iterator>::value_type(_val);
		return ( _first );
	}

	template <class _forward_iterator, class T>
	void fill(_forward_iterator first, _forward_iterator last, const T &val)
	{
		while (first != last)
		{
			*first = val;
			++first;
		}
	}

	template <class _outpur_iterator, class Size, class T>
	_outpur_iterator fill_n(_outpur_iterator first, Size n, const T &val)
	{
		while (n > 0)
		{
			*first = val;
			++first;
			--n;
		}
		return first; // since C++11
	}

	template <class _input_iterator, class _outpur_iterator>
	_outpur_iterator copy(_input_iterator first, _input_iterator last, _outpur_iterator result)
	{
		while (first != last)
		{
			*result = *first;
			++result;
			++first;
		}
		return result;
	}

	template <class _bidirectional_iterator1, class _bidirectional_iterator2>
	_bidirectional_iterator2 copy_backward(_bidirectional_iterator1 first, _bidirectional_iterator1 last, _bidirectional_iterator2 result)
	{
		while (last != first)
			*(--result) = *(--last);
		return result;
	}

	void _construct(pointer __p, const _Ty& _val)
	{
		if (__p)
			_data_allocator.construct(__p, _val);
	}

	void _deallocate(pointer __p, size_type __n)
	{
		if (__p)
			_data_allocator.deallocate(__p, __n);
	}

	void _destroy(pointer _first, pointer _last)
	{
		for (; _first != _last; ++_first)
		{
			_data_allocator.destroy(_first);
		}
	}

	void _destroy(pointer _pos)
	{
		_data_allocator.destroy(_pos);
	}

	vector(size_type __n, const allocator_type& __a)
	{
		(void)__a;
		_start = _allocate(__n);
		_finish = _start;
		_end_of_storage = _start + __n;
	}

	void _range_check(size_type __n) const
	{
		if (__n < 0 || __n >= size())
			throw std::out_of_range("vector");
	}

	template <typename _forward_iterator>
	pointer _allocate_and_copy(_forward_iterator _first, _forward_iterator _last, size_type __n);

	template <typename _input_iterator>
	void	__initailize(_input_iterator _first, _input_iterator _last, input_iterator_tag);

	template <typename _forward_iterator>
	void	__initailize(_forward_iterator _first, _forward_iterator _last, forward_iterator_tag);

	void	__assign(size_type __n, const _Ty& _val);

	template <typename _input_iterator>
	void	__assign(_input_iterator _first, _input_iterator _last, input_iterator_tag);

	template <typename _forward_iterator>
	void	__assign(_forward_iterator _first, _forward_iterator _last, forward_iterator_tag);

	void	__insert(iterator _pos, const _Ty& _val);

	void __insert(iterator _pos, size_type __n, const _Ty& _val);

	template <typename _integer>
	void __insert(iterator _pos, _integer __n, _integer _val, true_type)
	{ __insert(_pos, static_cast<size_type>(__n), static_cast<_Ty>(_val)); }

	template <typename _input_iterator>
	void __insert(iterator _pos, _input_iterator _first, _input_iterator _last, false_type)
	{ __insert(_pos, _first, _last, typename iterator_traits<_input_iterator>::iterator_category()); }

	template <typename _input_iterator>
	void __insert(iterator _pos, _input_iterator _first, _input_iterator _last, input_iterator_tag);

	template <typename _forward_iterator>
	void __insert(iterator _pos, _forward_iterator _first, _forward_iterator _last, forward_iterator_tag);

/*
**	|------------------------------------------------------Custom_function----------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Member_function----------------------------------------------------|
*/

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

	iterator begin() { return iterator( _start ); }
	const_iterator begin() const { return const_iterator( _start ); }
	iterator end() { return iterator( _finish ); }
	const_iterator end() const { return const_iterator( _finish ); }

	reverse_iterator rbegin() { return reverse_iterator( end() ); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator( end() ); }
	reverse_iterator rend() { return reverse_iterator( begin() ); }
	const_reverse_iterator rend() const { return const_reverse_iterator( begin() ); }

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Capacity-----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	size_type size() const
	{
		return size_type( end() - begin() );
	}

	size_type max_size() const
	{
		return size_type(-1) / sizeof(_Ty);
	}

	size_type capacity() const
	{
		return size_type( const_iterator( _end_of_storage ) - begin() );
	}

	bool empty() const { return ( begin() == end() ); }

	void reserve(size_type __n)
	{
		if (capacity() < __n)
		{
			const size_type old_size = size();
			pointer _Tmp = _allocate_and_copy(_start, _finish, __n);
			_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = _Tmp;
			_finish = _Tmp + old_size;
			_end_of_storage = _Tmp + __n;
		}
	}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|-------------------------------------------------Elements_Access---------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	reference operator[](size_type __n) { return *( begin() + __n ); }
	const_reference operator[](size_type __n) const { return *( begin() + __n ); }

	reference at(size_type __n)
	{
		_range_check(__n);
		return ( (*this)[__n] );
	}
	const_reference at(size_type __n) const
	{
		_range_check(__n);
		return ( (*this)[__n] );
	}

	pointer data() { return ( &( *begin() ) ); }
	const pointer data() const { return ( &( *begin() ) ); }

	reference front() { return ( *begin() ); }
	const_reference front() const { return ( *begin() ); }
	reference back() { return ( *( end() - 1 ) ); }
	const_reference back() const { return ( *( end() - 1 ) ); }

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|---------------------------------------------Othodox_Canonical_Form + Alpha----------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	vector()
	: _start(0), _finish(0), _end_of_storage(0) {}
	
	explicit vector(const allocator_type& __a)
	: _start(0), _finish(0), _end_of_storage(0) { (void)__a; }
	
	explicit vector (size_type __n, const value_type& _val = value_type(), const allocator_type& _alloc = allocator_type())
	{
		(void)_alloc;
		_start = _allocate(__n);
		_finish = uninitialized_fill_n(_start, __n, _val);
		_end_of_storage = _start + __n;
	}

	vector(const vector& __v)
	{
		_start = _allocate(__v.size());
		_finish = uninitialized_copy(__v.begin(), __v.begin() + __v.size(), _start);
		_end_of_storage = _start + __v.size();
	}

	// Cpp compiler is used to identify function's overloads using fourth parameter(enable_if and is_integral) - pjang's opinion.
	template <class _input_iterator>
	vector (_input_iterator _first, _input_iterator _last, const allocator_type& _alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<_input_iterator>::value >::type* = 0)
	{
		(void)_alloc;
		__initailize(_first, _last, typename iterator_traits<_input_iterator>::iterator_category());
	}

	~vector()
	{
		_destroy( _start, _finish );
		_deallocate(_start, _end_of_storage - _start);
	}

	vector& operator=(const vector& __v);

	void assign(size_type __n, const value_type& _val) { __assign(__n, _val); }

	template <class _input_iterator>
	void assign(_input_iterator _first, _input_iterator _last,
		typename ft::enable_if<!ft::is_integral<_input_iterator>::value >::type* = 0)
	{
		__assign(_first, _last, typename iterator_traits<_input_iterator>::iterator_category());
	}

/*
**	|-------------------------------------------------------------------------------------------------------------------------|
**	|------------------------------------------------------Modifiers----------------------------------------------------------|
**	|-------------------------------------------------------------------------------------------------------------------------|
*/

	void push_back(const value_type& _val)
	{
		if (_finish != _end_of_storage)
		{
			_construct(_finish, _val);
			++_finish;
		}
		else
		{
			__insert(end(), _val);
		}
	}

	void swap(vector& __v)
	{
		ft::swap(_start, __v._start);
		ft::swap(_finish, __v._finish);
		ft::swap(_end_of_storage, __v._end_of_storage);
	}

	iterator insert(iterator _pos, const _Ty& _val)
	{
		size_type __n = _pos - begin();
		if (_finish != _end_of_storage && _pos == end())
		{
			_construct(_pos.base(), _val);
			++_finish;
		}
		else
		{
			__insert(_pos, _val);
		}
		return ( begin() + __n );
	}

	void insert(iterator _pos, size_type __n, const _Ty& _val)
	{
		__insert(_pos, __n, _val);
	}

	template <typename _input_iterator>
	void insert(iterator _pos, _input_iterator _first, _input_iterator _last)
	{
		__insert(_pos, _first, _last, ft::is_integral<_input_iterator>() );
	}

	void pop_back()
	{
		if (size() == 0)
			return ;
		--_finish;
		_destroy(_finish);
	}

	iterator erase(iterator _pos)
	{
		if (_pos + 1 != end())
		{
			copy(_pos + 1, end(), _pos);
		}
		--_finish;
		_destroy(_finish);
		return (_pos);
	}

	iterator erase(iterator _first, iterator _last)
	{
		iterator __i(copy(_last, end(), _first));
		_destroy(__i.base(), end().base());
		_finish = _finish - ft::distance(_first, _last);
		return (_first);
	}

	void resize(size_type _new_size, const _Ty& _val = _Ty())
	{
		if (_new_size < size())
			erase(begin() + _new_size, end());
		else
			insert(end(), _new_size - size(), _val);
	}

	void clear() { erase(begin(), end()); }
};


template <class _Ty, class _Alloc>
inline bool 
operator==(const vector<_Ty, _Alloc>& _Left, const vector<_Ty, _Alloc>& _Right)
{
  return ( _Left.size() == _Right.size() && ft::equal(_Left.begin(), _Left.end(), _Right.begin()) );
}

template <class _Ty, class _Alloc>
inline bool 
operator<(const vector<_Ty, _Alloc>& _Left, const vector<_Ty, _Alloc>& _Right)
{
  return ( ft::lexicographical_compare(_Left.begin(), _Left.end(), _Right.begin(), _Right.end()) );
}

template <class _Ty, class _Alloc>
inline void swap(vector<_Ty, _Alloc>& _Left, vector<_Ty, _Alloc>& _Right)
{
  _Left.swap(_Right);
}

template <class _Ty, class _Alloc>
inline bool
operator!=(const vector<_Ty, _Alloc>& _Left, const vector<_Ty, _Alloc>& _Right) {
  return !(_Left == _Right);
}

template <class _Ty, class _Alloc>
inline bool
operator>(const vector<_Ty, _Alloc>& _Left, const vector<_Ty, _Alloc>& _Right) {
  return ( _Right < _Left );
}

template <class _Ty, class _Alloc>
inline bool
operator<=(const vector<_Ty, _Alloc>& _Left, const vector<_Ty, _Alloc>& _Right) {
  return !(_Right < _Left);
}

template <class _Ty, class _Alloc>
inline bool
operator>=(const vector<_Ty, _Alloc>& _Left, const vector<_Ty, _Alloc>& _Right) {
  return !(_Left < _Right);
}

template <class _Ty, class _Alloc>
vector<_Ty,_Alloc>& 
vector<_Ty,_Alloc>::operator=(const vector<_Ty, _Alloc>& _val)
{
	if (&_val != this)
	{
		const size_type _vlen = _val.size();
		if (_vlen > capacity())
		{
			pointer _Tmp = _allocate_and_copy(_val.begin(), _val.end(), _vlen);
			_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = _Tmp;
			_end_of_storage = _start + _vlen;
		}
		else if (size() >= _vlen)
		{
			iterator __i(copy(_val.begin(), _val.end(), begin()));
			_destroy(__i.base(), end().base());
		}
		else // vlen > size()
		{
			copy(_val.begin(), _val.begin() + size(), _start);
			uninitialized_copy(_val.begin() + size(), _val.end(), _finish);
		}
		_finish = _start + _vlen;
 	}
	return (*this);
}

template <typename _Ty, typename _Alloc>
template <typename _forward_iterator>
typename vector<_Ty, _Alloc>::pointer
vector<_Ty, _Alloc>::_allocate_and_copy(_forward_iterator _first, _forward_iterator _last, size_type __n)
{
	pointer __r = _allocate(__n);
	if (0 <= __n && __n <= max_size())
	{
		try
		{
			uninitialized_copy(_first, _last, __r);
		}
		catch (const std::bad_alloc &__b)
		{
			_deallocate(__r, __n);
			std::cerr << __b.what() << '\n';
		}
	}
	else
	{
		try
		{
			uninitialized_copy(_first, _last, __r);
		}
		catch (const std::length_error &__l)
		{
			_deallocate(__r, __n);
			std::cerr << __l.what() << '\n';
		}
	}
	return (__r);
}

template <typename _Ty, typename _Alloc>
template <typename _input_iterator>
void vector<_Ty, _Alloc>::__initailize(_input_iterator _first, _input_iterator _last, input_iterator_tag)
{
	for (; _first != _last; ++_first)
		push_back(*_first);
}

template <typename _Ty, typename _Alloc>
template <typename _forward_iterator>
void vector<_Ty, _Alloc>::__initailize(_forward_iterator _first, _forward_iterator _last, forward_iterator_tag)
{
	size_type __n = ft::distance(_first, _last);

	_start = _allocate(__n);
	_finish = uninitialized_copy(_first, _last, _start);
	_end_of_storage = _start + __n;
}

template <typename _Ty, typename _Alloc>
void	vector<_Ty, _Alloc>::__assign(size_type __n, const _Ty& _val)
{
	if (__n > capacity())
	{
		vector<_Ty, _Alloc> _Tmp(__n, _val, get_allocater());
		_Tmp.swap(*this);
	}
	else if (__n > size())
	{
		fill(begin(), end(), _val);
		_finish = uninitialized_fill_n(_finish, __n - size(), _val);
	}
	else
	{
		erase(fill_n(begin(), __n, _val), end());
	}
}

template <typename _Ty, typename _Alloc>
template <typename _input_iterator>
void vector<_Ty, _Alloc>::__assign(_input_iterator _first, _input_iterator _last, input_iterator_tag)
{
	iterator _cur(begin());
	for (; _first != _last && _cur != end(); ++_first, ++_cur)
		*_cur == *_first;
	if (_first == _last)
		erase(_cur, end());
	else
		insert(end(), _first, _last);
}

template <typename _Ty, typename _Alloc>
template <typename _forward_iterator>
void vector<_Ty, _Alloc>::__assign(_forward_iterator _first, _forward_iterator _last, forward_iterator_tag)
{
	size_type __n = ft::distance(_first, _last);

	if (__n > capacity())
	{
		pointer _Tmp(_allocate_and_copy(_first, _last, __n));
		_destroy(_start, _finish);
		_deallocate(_start, _end_of_storage - _start);
		_start = _Tmp;
		_end_of_storage = _finish = _Tmp + __n;
	}
	else if (__n > size())
	{
		_forward_iterator _mid = _first;
		ft::advance(_mid, size());
		copy(_first, _mid, _start);
		_finish = uninitialized_copy(_mid, _last, _finish);
	}
	else
	{
		iterator _new_finish(copy(_first, _last, _start));
		_destroy(_new_finish.base(), end().base());
		_finish = _new_finish.base();
	}
}

template <typename _Ty, typename _Alloc>
void vector<_Ty, _Alloc>::__insert(iterator _pos, const _Ty &_val)
{
	if (_finish != _end_of_storage)
	{
		_construct(_finish, *(_finish - 1));
		++_finish;
		_Ty _val_copy = _val;
		copy_backward(_pos, iterator(_finish - 2), iterator(_finish - 1));
		*_pos = _val_copy;
	}
	else
	{
		const size_type _old_size = size();
		const size_type _new_capa = _old_size != 0 ? _old_size * 2 : 1;
		iterator _new_start(_allocate(_new_capa));
		iterator _new_finish(_new_start);	// initialize
		try
		{
			_new_finish = uninitialized_copy(iterator(_start), _pos, _new_start);
			_construct(_new_finish.base(), _val);
			++_new_finish;
			_new_finish = uninitialized_copy(_pos, iterator(_finish), _new_finish);

		}
		catch(const std::exception& e)
		{
			_destroy(_new_start.base(), _new_finish.base());
			_deallocate(_new_start.base(), _new_capa);
			std::cerr << e.what() << '\n';
		}
		// copy success
		_destroy(_start, _finish);
		_deallocate(_start, _end_of_storage - _start);
		_start = _new_start.base();
		_finish = _new_finish.base();
		_end_of_storage = _new_start.base() + _new_capa;
	}
}

template <typename _Ty, typename _Alloc>
void vector<_Ty, _Alloc>::__insert(iterator _pos, size_type __n, const _Ty &_val)
{
	if (__n != 0)
	{
		// capacity >= size() + __n
		if (size_type(_end_of_storage - _finish) >= __n)
		{
			_Ty _v_copy = _val;
			const size_type num_pos_to_end = end() - _pos;
			iterator _old_finish(_finish);
			if (num_pos_to_end > __n)
			{
				uninitialized_copy(_finish - __n, _finish, _finish);
				_finish += __n;
				copy_backward(_pos, _old_finish - __n, _old_finish);
				fill(_pos, _pos + __n, _v_copy);
			}
			else
			{
				uninitialized_copy(_finish - __n, _finish, _finish);
				_finish += __n;
				fill(_pos, _pos + __n, _v_copy);
			}
		}
		else
		{
			// capacity < size() + n
			const size_type _old_capa = capacity();
			const size_type _new_capa = _old_capa * 2 > size() + __n ? _old_capa * 2 : size() + __n;
			iterator _new_start(_allocate(_new_capa));
			iterator _new_finish(_new_start);
			try
			{
				// std::vector - capacity == 0, _pos != being() or end() (ex) begin() + 1 : segfault
				_new_finish = uninitialized_copy(iterator(_start), _pos, _new_start);
				_new_finish = uninitialized_fill_n(_new_finish, __n, _val);
				_new_finish = uninitialized_copy(_pos, iterator(_finish), _new_finish);
			}
			catch(const std::exception& e)
			{
				_destroy(_new_start.base(), _new_finish.base());
				_deallocate(_new_start.base(), _new_capa);
				std::cerr << e.what() << '\n';
			}
			// copy success
			_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = _new_start.base();
			_finish = _new_finish.base();
			_end_of_storage = _new_start.base() + _new_capa;
		}
	}
}

template <typename _Ty, typename _Alloc>
template <typename _input_iterator>
void vector<_Ty, _Alloc>::__insert(iterator _pos, _input_iterator _first, _input_iterator _last, input_iterator_tag)
{
	iterator _Tmp(_first);
	for(; _Tmp != _last; ++_Tmp)
	{
		_pos = insert(_pos, *_Tmp);
		++_pos;
	}
}

template <typename _Ty, typename _Alloc>
template <typename _forward_iterator>
void vector<_Ty, _Alloc>::__insert(iterator _pos, _forward_iterator _first, _forward_iterator _last, forward_iterator_tag)
{
	if (_first != _last)
	{
		size_type __n = ft::distance(_first, _last);
		// capacity >= size() + __n
		if (size_type(_end_of_storage - _finish) >= __n)
		{
			const size_type num_pos_to_end = end() - _pos;
			iterator _old_finish(_finish);
			if (num_pos_to_end > __n)
			{
				uninitialized_copy(_finish - __n, _finish, _finish);
				_finish += __n;
				copy_backward(_pos, _old_finish - __n, _old_finish);
				copy(_first, _last, _pos);
			}
			else
			{
				_forward_iterator _mid = _first;
				ft::advance(_mid, num_pos_to_end);
				uninitialized_copy(_mid, _last, _finish);
				_finish += __n - num_pos_to_end;
				uninitialized_copy(_pos, _old_finish, _finish);
				_finish += num_pos_to_end;
				copy(_first, _mid, _pos);
			}
		}
		else
		{
			// capacity < size() + n
			const size_type _old_capa = capacity();
			const size_type _new_capa = _old_capa * 2 > size() + __n ? _old_capa * 2 : size() + __n;
			iterator _new_start(_allocate(_new_capa));
			iterator _new_finish(_new_start);
			try
			{
				// std::vector - capacity == 0, _pos != being() or end() (ex) begin() + 1 : segfault
				_new_finish = uninitialized_copy(iterator(_start), _pos, _new_start);
				_new_finish = uninitialized_copy(_first, _last, _new_finish);
				_new_finish = uninitialized_copy(_pos, iterator(_finish), _new_finish);
			}
			catch(const std::exception& e)
			{
				_destroy(_new_start.base(), _new_finish.base());
				_deallocate(_new_start.base(), _new_capa);
				std::cerr << e.what() << '\n';
			}
			// copy success
			_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = _new_start.base();
			_finish = _new_finish.base();
			_end_of_storage = _new_start.base() + _new_capa;
		}
	}
}

_FT_END
#endif
