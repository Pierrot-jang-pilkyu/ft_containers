#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "basic_macro.hpp"
#include "iterator_traits.hpp"

_FT_BEGIN
template <typename _Category, typename _Ty, typename _Distance = std::ptrdiff_t, typename _Pointer = _Ty*, typename _Reference = _Ty&>
struct iterator
{
	typedef _Category	iterator_category;
	typedef _Ty			value_type;
	typedef _Distance	difference_type;
	typedef _Pointer	pointer_type;
	typedef _Reference	reference_type;
};

/*
**	|----------------------------------------------------------------------------------------------------------------------------------------------|
**	|-------------------------------------------------------------struct iterator------------------------------------------------------------------|
**	|----------------------------------------------------------------------------------------------------------------------------------------------|
**	|-------------------------------------------------------------reverse_iterator-----------------------------------------------------------------|
**	|----------------------------------------------------------------------------------------------------------------------------------------------|
*/

template <typename _Iter>
class reverse_iterator :
	public iterator <	typename iterator_traits<_Iter>::iterator_category,
						typename iterator_traits<_Iter>::value_type,
						typename iterator_traits<_Iter>::difference_type,
						typename iterator_traits<_Iter>::pointer,
						typename iterator_traits<_Iter>::reference >
{
protected:
	_Iter current;
public:
	// Member type
	typedef _Iter												iterator_type;
	typedef typename iterator_traits<_Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<_Iter>::value_type			value_type;
	typedef typename iterator_traits<_Iter>::difference_type	difference_type;
	typedef typename iterator_traits<_Iter>::pointer			pointer;
	typedef typename iterator_traits<_Iter>::reference			reference;

	// Member Function
	reverse_iterator() {}
	explicit reverse_iterator (const iterator_type& it) : current(it) {}
	reverse_iterator (const reverse_iterator<_Iter>& rev_it) : current(rev_it.current) {}
	template <typename _Iter2>
	reverse_iterator (const reverse_iterator<_Iter2>& rev_it) : current(rev_it.base()) {}
	reverse_iterator &operator=(const reverse_iterator<_Iter>& _Right)
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
		_Iter _Tmp = current;
		return (*(--_Tmp));
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	reverse_iterator &operator++()
	{
		--current;
		return (*this);
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator _Tmp = *this;
		--current;
		return (_Tmp);
	}

	// bidirectional_iterator requirements

	reverse_iterator &operator--()
	{
		++current;
		return (*this);
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator _Tmp = *this;
		++current;
		return (_Tmp);
	}

	// random_access_iterator requirements

	reverse_iterator operator+(difference_type _Off) const
	{
		return (reverse_iterator(current - _Off));
	}

	reverse_iterator operator-(difference_type _Off) const
	{
		return (reverse_iterator(current + _Off));
	}

	reverse_iterator operator+=(difference_type _Off)
	{
		current -= _Off;
		return (*this);
	}

	reverse_iterator operator-=(difference_type _Off)
	{
		current += _Off;
		return (*this);
	}

	reference operator[](difference_type _Off) const
	{
		return (current[static_cast<difference_type>(_Off - 1)]);
	}

};


template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& _Left, const reverse_iterator<Iterator>& _Right)
{
	return (_Left.base() == _Right.base());
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& _Left, const reverse_iterator<Iterator>& _Right)
{
	return (_Left.base() != _Right.base());
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& _Left, const reverse_iterator<Iterator>& _Right)
{
	return (_Left.base() < _Right.base());
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& _Left, const reverse_iterator<Iterator>& _Right)
{
	return (_Left.base() <= _Right.base());
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& _Left, const reverse_iterator<Iterator>& _Right)
{
	return (_Left.base() > _Right.base());
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& _Left, const reverse_iterator<Iterator>& _Right)
{
	return (_Left.base() >= _Right.base());
}

template<class _Iter>
reverse_iterator<_Iter> operator+(typename reverse_iterator<_Iter>::difference_type _Off, const reverse_iterator<_Iter>& _Right)
{
	return (_Right + _Off);
}

template< class _Iter1, class _Iter2 >
typename reverse_iterator<_Iter1>::difference_type operator-(const reverse_iterator<_Iter1>& _Left, const reverse_iterator<_Iter2>& _Right)
{
	return (_Right.base() - _Left.base());
}

/*
**	|----------------------------------------------------------------------------------------------------------------------------------------------|
**	|-------------------------------------------------------------reverse_iterator-----------------------------------------------------------------|
**	|----------------------------------------------------------------------------------------------------------------------------------------------|
**	|-------------------------------------------------------------__normal_iterator----------------------------------------------------------------|
**	|----------------------------------------------------------------------------------------------------------------------------------------------|
*/

template <typename _Iter, typename _Container>
class __normal_iterator :
	public iterator <	typename iterator_traits<_Iter>::iterator_category,
						typename iterator_traits<_Iter>::value_type,
						typename iterator_traits<_Iter>::difference_type,
						typename iterator_traits<_Iter>::pointer,
						typename iterator_traits<_Iter>::reference >
{
protected:
	_Iter current;

public:
	// Member type
	typedef _Iter												iterator_type;
	typedef typename iterator_traits<_Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<_Iter>::value_type			value_type;
	typedef typename iterator_traits<_Iter>::difference_type	difference_type;
	typedef typename iterator_traits<_Iter>::pointer			pointer;
	typedef typename iterator_traits<_Iter>::reference			reference;

	// Member Function
	__normal_iterator() {}
	explicit __normal_iterator (const iterator_type& _It) : current(_It) {}
	// Allow iterator to const_iterator conversion
	template <typename _Iter2>
	__normal_iterator (const __normal_iterator<_Iter2, _Container>& _It) : current(_It.base()) {}
	__normal_iterator &operator=(const __normal_iterator<_Iter, _Container>& _Right)
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
		return (current);
	}

	__normal_iterator &operator++()
	{
		++current;
		return (*this);
	}

	__normal_iterator operator++(int)
	{
		return ( __normal_iterator(current++) );
	}

	// bidirectional_iterator requirements

	__normal_iterator &operator--()
	{
		--current;
		return (*this);
	}

	__normal_iterator operator--(int)
	{
		return ( __normal_iterator(current--) );
	}

	// random_access_iterator requirements

	__normal_iterator operator+(difference_type _Off) const
	{
		return (__normal_iterator(current + _Off));
	}

	__normal_iterator operator-(difference_type _Off) const
	{
		return (__normal_iterator(current - _Off));
	}

	difference_type operator-(const __normal_iterator& _it) const
	{
		return ( current - _it.current );
	}

	__normal_iterator operator+=(difference_type _Off)
	{
		current += _Off;
		return (*this);
	}

	__normal_iterator operator-=(difference_type _Off)
	{
		current -= _Off;
		return (*this);
	}

	reference operator[](difference_type _Off) const
	{
		return (current[static_cast<difference_type>(_Off)]);
	}
};

// forward_iterator requirements
template<typename _IterL, typename _IterR, typename _Container>
inline bool operator==(const __normal_iterator<_IterL, _Container>& _Left, const __normal_iterator<_IterR, _Container>& _Right)
{
	return (_Left.base() == _Right.base());
}

template<typename _IterL, typename _IterR, typename _Container>
inline bool operator!=(const __normal_iterator<_IterL, _Container>& _Left, const __normal_iterator<_IterR, _Container>& _Right)
{
	return !(_Left == _Right);
}

// random_access_iterator requirements
template<typename _IterL, typename _IterR, typename _Container>
inline bool operator<(const __normal_iterator<_IterL, _Container>& _Left, const __normal_iterator<_IterR, _Container>& _Right)
{
	return (_Left.base() < _Right.base());
}

template<typename _IterL, typename _IterR, typename _Container>
inline bool operator>(const __normal_iterator<_IterL, _Container>& _Left, const __normal_iterator<_IterR, _Container>& _Right)
{
	return (_Right < _Left);
}

template<typename _IterL, typename _IterR, typename _Container>
inline bool operator<=(const __normal_iterator<_IterL, _Container>& _Left, const __normal_iterator<_IterR, _Container>& _Right)
{
	return !(_Right < _Left);
}

template<typename _IterL, typename _IterR, typename _Container>
inline bool operator>=(const __normal_iterator<_IterL, _Container>& _Left, const __normal_iterator<_IterR, _Container>& _Right)
{
	return !(_Left < _Right);
}

template<typename _Iterator, typename _Container>
inline __normal_iterator<_Iterator, _Container> operator+(typename __normal_iterator<_Iterator, _Container>::difference_type _n, const __normal_iterator<_Iterator, _Container>& _It)
{
	return (__normal_iterator<_Iterator, _Container>(_It.base() + _n));
}
_FT_END

#endif
