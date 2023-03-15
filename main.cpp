// #include <vector>
// #include <stack>
// #include <cstddef>
// #include <xutility>
#include <iterator>
// #include <type_traits>
#include <iostream>
#include "./stack/stack.hpp"
#include <stack>
#include <vector>
#include <algorithm>
#include <type_traits>

void	print(int a)
{
	std::cout << "print int\n";
}

void	print(char *a)
{
	std::cout << "print char*\n";
}

template <typename T>
class A
{
private:
	T a;

public:
	A() : a(0) {}
	A(const T& value) : a(value) {}
	~A() {}
	A &operator=(const A& obj)
	{
		this->a = obj.a;
		return (*this);
	}

	T &getValue(void) { return (this->a); }

};

template <typename T>
void only_int(const T &a)
{
	if (std::is_integral<T>::value)
		std::cout << "This type is integer\n";
	else
		std::cout << "This type is not integer\n";
}

int main(int ac, char *av[])
{
	int n = 10;
	only_int(n);
	A<int> a;
	only_int(a);
	// print(NULL);
	// print(nullptr);

	// A<int> a;
	// A<int> b(5);
	// std::cout << a.getValue() << std::endl;
	// a = b;
	// std::cout << a.getValue() << std::endl;
	// std::vector<int> v1;
	// std::vector<int> v2;
	
	// for (int i = 1; i < 6; i++) v1.push_back(i);

	// typename std::vector<int>::reverse_iterator rIter(v1.begin());

	// typename std::vector<int>::iterator it;
	// std::cout << *rIter << std::endl;


	// int* ptr = new int[1];

	// std::cout << *(ptr - 1) << std::endl;
	// std::cout << *(ptr) << std::endl;
	// std::cout << *(ptr + 1) << std::endl;
	// std::cout << std::endl;

	// std::cout << v2.capacity() << std::endl;
	// for (int i = 1; i < 128; i++)
	// {
	// 	std::vector<int>().swap(v2);
	// 	v2.resize(i, 0);
	// 	if (*v2.end() != 0)
	// 	{
	// 		std::cout << "i : " << i << std::endl;
	// 		break ;
	// 	}
	// }
	// v2.reserve(129);
	// std::cout << v2.size() << std::endl;
	// std::cout << v2.capacity() << std::endl;
	// std::cout << v2[0] << std::endl;
	// std::cout << *v2.begin() << " " << *v2.end() << std::endl;
	// std::cout << (v2.end() - v2.begin()) << std::endl;
	// for (int i = 0; i < 100; i++) v1.push_back(i);
	// std::cout << v1.size() << std::endl;
	// std::cout << v1.capacity() << std::endl;
	// std::cout << *v1.begin() << " " << *v1.end() << std::endl;
	// for (int i = 0; i < 27; i++) v1.push_back(i);
	// for (int i = 0; i < 100; i++) v2.push_back(i);
	// std::cout << "	before	\n----------------\n	after	\n";
	// v1.insert(v1.begin(), v2.begin(), v2.end());
	// std::cout << v1.capacity() << std::endl;
	// std::cout << *v1.begin() << " " << *v1.end() << std::endl;

	return (0);
}
