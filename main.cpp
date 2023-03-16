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
#include "./etc/pair.hpp"
#include "./vector/vector.hpp"
#include "./stack/stack.hpp"
#include "./etc/iterator.hpp"
#include "./etc/iterator_traits.hpp"
#include "./etc/algorithm.hpp"
#include "./etc/type_traits.hpp"
#include <memory>

int main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	
	std::vector<int> std_v;
	ft::vector<int> ft_v;

	for (int i = 1; i < 6; ++i)
	{
		std_v.push_back(i);
		ft_v.push_back(i);
		std::cout << "std vector : " << std_v[i - 1] << ",	ft_vector : " << ft_v[i - 1] << std::endl; 
		std::cout << "std vector : " << std_v.size() << ",	ft_vector : " << ft_v.size() << std::endl; 
		std::cout << "std vector : " << std_v.capacity() << ",	ft_vector : " << ft_v.capacity() << std::endl; 
	}
	// std::vector<int> v2;

	// v2.reserve(5);
	// // printf("%p\n", v1.begin());
	// std::vector<int>::iterator start(v2.begin());
	// // auto iter =  v1.insert(v1.begin(), 1, 5);
	// printf("%p %p\n", v1.begin(), v1.end());
	// auto iter = std::uninitialized_copy(v1.begin(), v1.end(), start);
	// v1.pop_back();
	// printf("%p %p\n", v1.begin(), v1.end());
	// v1.push_back(1);
	// printf("%p %p\n", v1.begin(), v1.end());
	// iter = std::uninitialized_copy(v1.begin(), v1.begin() + 1, start);
	// std::cout << v1.size() << std::endl;
	// std::cout << v1.capacity() << std::endl;
	// iter =  v1.insert(v1.begin() + 1, 3, 5);
	// std::vector<int>::iterator start;
	// auto iter = std::uninitialized_copy(v1.begin(), v1.begin() + 1, start);
	// std::cout << *(iter - 2) << " " << *(iter - 1) << " " << *(iter) << " " << *(iter + 1) << " " << *(iter + 2) << std::endl;
	// for (int i = 1; i < 6; i++) v2.push_back(i);
	// std::cout << v2.size() << std::endl;
	// std::cout << v2.capacity() << std::endl;

	// auto iter =  v2.insert(v2.begin() + 2, 3);
	// auto iter2 = v2.begin();
	// int i;
	// for (i = 0; iter2 != iter; ++i, ++iter2)
	// 	;
	// std::cout << i << std::endl;
	// std::vector<int> v3(v2.begin(), v2.end());

	// std::cout << std::distance(v2.begin(), v2.end()) << std::endl;

	// std::vector<int>::iterator iter = v1.begin();

	// std::cout << v3.size() << std::endl;
	// std::cout << v3.capacity() << std::endl;

	// std::allocator<int> a;

	// std::vector<int>::iterator iter;

	// v1.reserve(5);
	// iter = std::uninitialized_fill_n(v1.begin(), v3.size(), 1);
	
	// std::cout << v1.capacity() << std::endl;
	// std::cout << *iter << " " << *(v1.end() + 4) << std::endl;
	// if (iter == ++v1.end())
	// 	std::cout << "equal\n";

	

	// size_t n = -1;
	// auto begin = a.allocate(n);
		// auto end = std::uninitialized_fill_n(begin, n, 1);
	// try
	// {
	// 	v1.reserve(-1);
	// }
	// catch(const std::exception& e)
	// {
	// 	// a.deallocate(begin, n);
	// 	std::cerr << e.what() << '\n';
	// }
	
	// *iter = 2;

	// std::cout << *iter << std::endl;

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
