#ifndef STACK_HPP
#define STACK_HPP
#include "../etc/basic_macro.hpp"

// test
#include <vector>

_FT_BEGIN
template <typename _Ty, typename _Container = std::vector<_Ty>>
class stack
{
protected:
	_Container	c{};

public:
	typedef _Container						container_type;
	typedef typename _Container::value_type	value_type;
	typedef typename _Container::size_type	size_type;

	// Member Fucntions

	// Othodox Canonical Form 
	explicit stack(const _Container& _Cont = _Container()) : c(_Cont) {}
	stack(const stack& _Other) : c(_Other) {}
	stack& operator=(const stack& _Other) { *this = _Other; }
	~stack() {};

	// Element Access
	value_type& top() { return c.back(); }
	const value_type& top() const { return c.back(); }

	// Capacity
	bool empty() { return c.empty(); }
	size_type size() { return c.size(); }

	// Modifiers
	void push(const value_type& _Val) { return c.push_back(_Val); }
	void pop() { c.pop_back(); }

};

_FT_END

#endif
