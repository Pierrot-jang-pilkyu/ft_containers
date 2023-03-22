// #include <vector>
// #include <stack>
// #include <cstddef>
// #include <xutility>
#include <iterator>
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
// 	A(const A& _a) : a(_a.a), ptr(_a.ptr) {}
// 	A(A* _a) : a(_a->a), ptr(_a->ptr) {}
// 	A(const A* _a) : a(_a->a), ptr(_a->ptr) {}

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

// #define SHOW(...) \
//     std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

int test()
{
	ft::rb_tree<int, std::less<int> > 			myTree;
	ft::rb_tree<int, std::less<int> >::iterator	iter;
	// myTree.insert(10);

	// std::cout << myTree.begin()->__value_field << std::endl;
	// std::cout << myTree.size() << std::endl;

	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Commands:" << std::endl;
	std::cout << "   '+Key': Insert element" << std::endl;
	std::cout << "      'Q': Quit the test program" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "※ In tree draw, '├──key' is left child, '└──key' is right child ※\n" << std::endl;

	std::string userStr;
	

	while (true) 
	{
		std::cout << myTree.show_tree() << std::endl;		// 매 loop마다 트리를 출력하도록 설정한다.

		std::cout << "Command: ";
		std::cin >> userStr;

		char userOption = userStr[0];		// 사용자 입력값의 첫 글자는 연산 option을 의미한다.
		userStr.erase(0, 1);				// atoi 함수를 사용하기 위해 첫 글자를 삭제한다.
		int userVar = std::atoi(userStr.c_str());	// 사용자 입력 문자열을 정수로 바꾼다.
		// [오류]: 유효하지 않은 연산자일경우 오류이므로 다시 입력하게끔 유도한다.
		if (userOption != '+' && userOption != '-' && userOption != 'Q' && userOption != 'q') 
		{
			std::cout << "[ERROR] Wrong command! Input command again please" << std::endl;
			continue;
		}
		// 사용자가 입력한 옵션에 따라 대응하는 함수를 호출한다.
		switch (userOption) 
		{
		case '+':
			myTree.insert(userVar);
			break;
		case '-':
			iter = myTree.find(userVar);
			myTree.erase(iter);
			break;
		case 'Q': case 'q':
			std::cout << "Quit program!" << std::endl;
			return 0;
		}
	}

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
	system("leaks ft_containers");
	return (0);
}
