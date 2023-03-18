// #include <vector>
// #include <stack>
// #include <cstddef>
// #include <xutility>
// #include <iterator>
// #include <type_traits>
#include <iostream>
// #include <stack>
#include <vector>
#include <stdexcept>
// #include <algorithm>
// #include <type_traits>
#include <algorithm>
#include <functional>
#include "./etc/pair.hpp"
#include "./etc/rb_tree.hpp"
#include "./vector/vector.hpp"
#include "./stack/stack.hpp"
#include "./etc/iterator.hpp"
#include "./etc/iterator_traits.hpp"
#include "./etc/algorithm.hpp"
#include "./etc/type_traits.hpp"
#include <memory>
#include <string>
#include <map>

#include <iomanip>

// template <typename _Ty>
// class A
// {
// public:
// 	typedef A* _a_ptr;
// 	typedef A& _a_rfc;
// 	_Ty 	a;
// 	_a_ptr ptr;

// 	A() : a(10), ptr(0) {}
// 	// A(const A& _a) : a(_a.a), ptr(_a.ptr) {}
// 	// A(A* _a) : a(_a->a), ptr(_a->ptr) {}
// 	// A(const A* _a) : a(_a->a), ptr(_a->ptr) {}

// 	_a_rfc operator*() const
// 	{  return ( a ); }
// };

// // template <typename _Ty>
// // class B : public A
// // {
// // 	_Ty b;
// // };

// template <typename _Iter>
// class C :
// 	public ft::iterator <	typename ft::iterator_traits<_Iter>::iterator_category,
// 							typename ft::iterator_traits<_Iter>::value_type,
// 							typename ft::iterator_traits<_Iter>::difference_type,
// 							typename ft::iterator_traits<_Iter>::pointer,
// 							typename ft::iterator_traits<_Iter>::reference >
// {
// public:
// 	typedef typename ft::iterator_traits<_Iter>::pointer	 pointer;
// 	typedef typename ft::iterator_traits<_Iter>::reference	reference;

// 	_Iter current;

// 	C() : current(_Iter()) {}
// 	explicit C(const _Iter& it) : current(it) {}
// 	C(const C<_Iter>& _iter) : current(_iter.current) {}
// 	template <typename _Iter2>
// 	C(const C<_Iter2>& _iter) : current(_iter.base()) {}

// 	_Iter base() const { return current; }

// 	reference operator*() const
// 	{
// 		return *(current);
// 	}

// 	pointer operator->() const { return (&(operator*())); }
// };

// template <typename _Ty, typename _Alloc = std::allocator<_Ty> >
// class D
// {
// public:
// 	typedef _Ty				value_type;
// 	typedef value_type*		pointer;
// 	typedef value_type&		reference;
// 	typedef C<pointer> 		iterator;
// 	_Alloc a;
// 	_Ty* value;

// 	D()
// 	{
// 		// value = new _Ty();
// 		value = a.allocate(1);
// 		ft::uninitialized_fill(value, 0);
// 	}

// 	D(size_t __n, const _Ty& _val = value_type())
// 	{
// 		// value = new _Ty();
// 		value = a.allocate(__n);
// 		ft::uninitialized_fill_n(value, __n, _val);
// 	}

// 	iterator begin() { return iterator(value); }
// };

// template <class T> struct less : binary_function <T,T,bool> {
//   bool operator() (const T& x, const T& y) const {return x<y;}
// };

int test()
{
	ft::rb_tree<int, std::less<int> > rb;

	rb.insert(10);

	std::cout << rb.begin()->__value_field << std::endl;
	// A<int> a;
	// // a.a = 20;
	// D<A<int> > d(1, a);
	// D<A<int> >::iterator iter = d.begin();

	// std::cout << (*iter).a << std::endl;
	// std::cout << iter->a << std::endl;

	// std::map<std::string, std::string> m;
	// m.insert(std::pair<std::string, std::string>("11", "10"));
	// m.insert(std::pair<std::string, std::string>("12", "10"));
	// typename std::map<std::string, std::string>::iterator iter1 = m.end();
	// typename std::map<std::string, std::string>::iterator iter2 = m.begin();

	// printf("begin : %p, begin + 1 : %p\n", &(iter2), &((++iter2)));
	// printf("begin : %p, begin + 1 : %p\n", &(++iter2), &((--iter2)));
	// iter2 = m.begin();
	// printf("begin : %p, begin - 1 : %p\n", &(iter2), &((--iter2)));
	// iter2 = m.begin();
	// printf("begin first : %p, begin - 1 first : %p\n", &((iter2)->first), &((--iter2)->first));
	// iter2 = m.begin();
	// std::cout << (*iter2).first << " " << (*--iter2).first << " ";


	// for (int i = 1; i < 10; ++i)
	// 	m.insert(std::pair<int, int>(i, i * 100));
	
	// typename std::map<int, int>::iterator iter2 = m.end();

	// std::cout << iter1->first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n";
	// std::cout << (*++iter1).first << "\n\n";
	// std::cout << (*iter2).first << " " << std::endl;\
	// std::cout << (*--iter2).first << " " << std::endl;
	// std::cout << (*--iter2).first << " " << std::endl;
	// std::cout << (*--iter2).first << " " << std::endl;
	// iter2 = m.end();
	// std::cout << (*++iter2).first << " " << std::endl;
	// std::cout << (*++iter2).first << " " << std::endl;

	return (0);
}

int main()
{
	test();
	// system("leaks a.out");
	// system("leaks ft_containers");
	return (0);
}
