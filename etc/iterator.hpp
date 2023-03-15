#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "basic_macro.hpp"

_FT_BEGIN
template <typename _Category, typename _Ty, typename _Distance = ptrdiff_t, typename _Pointer = _Ty*, typename _Reference = _Ty&>
struct iterator
{
	typedef _Category	iterator_category;
	typedef _Ty			value_type;
	typedef _Distance	difference_type;
	typedef _Pointer	pointer_type;
	typedef _Reference	reference_type;
};

template <typename _Iter>
class reverse_iterator
{
protected:
	_Iter current{};
public:
	// Member type
	typedef typename _Iter										iterator_type;
	typedef typename iterator_traits<_Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<_Iter>::value_type			value_type;
	typedef typename iterator_traits<_Iter>::difference_type	difference_type;
	typedef typename iterator_traits<_Iter>::pointer			pointer;
	typedef typename iterator_traits<_Iter>::const_pointer		const_pointer;
	typedef typename iterator_traits<_Iter>::reference			reference;
	typedef typename iterator_traits<_Iter>::const_reference	const_reference;

	// Member Function
	reverse_iterator() {}
	explicit reverse_iterator (const iterator_type& it) : current(it) {}
	reverse_iterator (const reverse_iterator<_Iter>& rev_it) : current(rev_it.current) {}
	reverse_iterator &operator=(const reverse_iterator<_Iter>& _Right)
	{
		this->current = _Right.current;
		return (*this);
	}

	iterator_type base() const
	{
		return (current);
	}

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
_FT_END

#endif