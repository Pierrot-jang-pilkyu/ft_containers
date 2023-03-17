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

#include <iomanip>

int test()
{
	
	// std::vector<int> std_v1(3);
	// std_v1.reserve(10);
	// std::vector<int> std_v2(std_v1);
	// ft::vector<int> ft_v1(3);
	// ft_v1.reserve(10);
	// ft::vector<int> ft_v2(ft_v1);

	std::vector<int> std_v(3);
	ft::vector<int> ft_v(3);
	
	// std::cout << std_v1.size() << " " << std_v1.capacity() << std::endl;
	// std::cout << std_v2.size() << " " << std_v2.capacity() << std::endl;
	// std::cout << ft_v1.size() << " " << ft_v1.capacity() << std::endl;
	// std::cout << ft_v2.size() << " " << ft_v2.capacity() << std::endl;

	std_v.clear();
	ft_v.clear();
	for (size_t i = 1; i < 4; i++)
	{
		std_v.insert(std_v.begin(), i * 3);
		ft_v.insert(ft_v.begin(), i * 3);
	}
	std::cout << std_v.size() << " " << std_v.capacity() << std::endl;
	std::cout << ft_v.size() << " " << ft_v.capacity() << std::endl;

	// std::cout << ft_v[2] << " " << *ft_v.end() << " " << ft_v.capacity() << std::endl;

	// std_v.insert(std_v.end(), 10);
	// ft_v.insert(ft_v.end(), 10);

	// std_v.insert(std_v.begin() + 2, 5);
	// ft_v.insert(ft_v.begin() + 2, 5);

	// std::cout << std_v.size() << " " << std_v.capacity() << std::endl;
	// std::cout << ft_v.size() << " " << ft_v.capacity() << std::endl;

	// std_v.insert(std_v.begin(), 2, 0);
	// ft_v.insert(ft_v.begin(), 2, 0);

	// std::cout << std_v.size() << " " << std_v.capacity() << std::endl;
	// std::cout << ft_v.size() << " " << ft_v.capacity() << std::endl;

	// std_v.insert(std_v.end(), 3, 20);
	// ft_v.insert(ft_v.end(), 3, 20);

	// std::cout << std_v.size() << " " << std_v.capacity() << std::endl;
	// std::cout << ft_v.size() << " " << ft_v.capacity() << std::endl;

	// std_v.insert(std_v.begin() + 5, 15, 20);
	// ft_v.insert(ft_v.begin() + 5, 15, 20);

	// std::cout << std_v.size() << " " << std_v.capacity() << std::endl;
	// std::cout << ft_v.size() << " " << ft_v.capacity() << std::endl;

	return (0);
}

int main()
{
	test();
	system("leaks a.out");
	// system("leaks ft_containers");
	return (0);
}
