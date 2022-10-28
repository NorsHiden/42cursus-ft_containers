#include <iostream>
#include <vector>
#include "containers/vector.hpp"

#define RED  "\033[0;31m"
#define GREEN  "\033[0;32m"
#define RESET "\033[0;37m"
#define YELLOW "\033[0;33m"

struct str
{
	std::string _ss;

	str() { std::cout << GREEN << "str default constructor {N/A}" << RESET << std::endl; }
	str(const  std::string ss): _ss(ss) { std::cout << GREEN << "str init constructor {" << _ss << "}" << RESET << std::endl; }
	str(const str& other): _ss(other._ss) { std::cout << GREEN << "str copy constructor {" << _ss << "}" << RESET << std::endl; }
	str& operator=(const str& other) { _ss = other._ss; std::cout << GREEN << "str copy assignment {" << _ss << "}" << RESET << std::endl; return (*this); }
	~str() { std::cout << GREEN << "str destructor {" << _ss << "}" << RESET << std::endl; }
};

template<typename T>
struct myAlloc1: std::allocator<T>
{
	// template< class U > struct rebind {
    // 	typedef myAlloc1<U> other;
	// };
	std::allocator<T> or_alloc;
	std::string tt;
	myAlloc1(): std::allocator<T>() { std::cout << RED << "default constructor of myAlloc1 has been called" << RESET << std::endl;}
	T* allocate(size_t size)
	{
		std::cout << RED << "myAlloc1 size: " << size << " needed" << RESET << std::endl;
		return (or_alloc.allocate(size));
	}
	void deallocate( T* p, std::size_t n )
	{
		std::cout << RED << "myAlloc1 address: " << p << ", size:" << n << " deallocated" << RESET << std::endl;
		or_alloc.deallocate(p, n);
	}
	myAlloc1(const myAlloc1& other): std::allocator<T>(other), tt(other.tt)
	{
		std::cout << RED << "copy constructor of myAlloc1 has been called" << RESET << std::endl;
	}
	myAlloc1& operator=(const myAlloc1& other)
	{
		tt = other.tt;
		std::cout << RED << "copy assignment of myAlloc1 has been called" << RESET << std::endl;
		return (*this);
	}
	
};

std::ostream& operator<<(std::ostream& out, str& s)
{
		out << s._ss;
		return (out);
}

int main(void)
{
	std::cout << YELLOW << "•••••••••••••••••••FT•••••••••••••••••••" << RESET << std::endl;
	{
		ft::vector<std::string> vecL;
		ft::vector<std::string> vecR;

		// vecL.push_back(0);
		// vecL.push_back(1);
		// vecL.push_back(2);
		// vecL.push_back(3);
		// vecL.push_back(4);
		vecL.push_back("hello");

		// vecR.push_back(0);
		// vecR.push_back(1);
		// vecR.push_back(2);
		// vecR.push_back(3);
		// vecR.push_back(4);
		std::cout << "----------------ITERATORS-----------------" << std::endl;
		// ft::vector<std::string>::reverse_iterator rit = vecL.rbegin();
		std::cout << ft::is_integral<ft::remove_cv<const int>::type >::value << std::endl;
		std::cout << "----------------STATS-----------------" << std::endl;
		std::cout << "\t\tvecL\t|\tvecR" << std::endl;
		std::cout << "size:\t\t" << vecL.size() << "\t|\t" << vecR.size() << std::endl;
		std::cout << "capacity:\t" << vecL.capacity() << "\t|\t" << vecR.capacity() << std::endl;
		std::cout << "----------------RESULT-----------------" << std::endl;

		// std::cout << "vecL == vecR:" << (vecL == vecR) << std::endl;
		// std::cout << "vecL != vecR:" << (vecL != vecR) << std::endl;
		// std::cout << "vecL <= vecR:" << (vecL <= vecR) << std::endl;
		// std::cout << "vecL >= vecR:" << (vecL >= vecR) << std::endl;
		// std::cout << "vecL < vecR:" << (vecL < vecR) << std::endl;
		// std::cout << "vecL > vecR:" << (vecL > vecR) << std::endl;
	}
	// std::cout << YELLOW << "•••••••••••••••••••STD•••••••••••••••••••" << RESET << std::endl;
	// {
	// 	std::vector<int> vecL;
	// 	std::vector<int> vecR;

	// 	vecL.push_back(0);
	// 	vecL.push_back(1);
	// 	vecL.push_back(2);
	// 	vecL.push_back(3);
	// 	vecL.push_back(4);

	// 	vecR.push_back(0);
	// 	vecR.push_back(1);
	// 	vecR.push_back(2);
	// 	vecR.push_back(3);
	// 	vecR.push_back(4);

	// 	std::cout << "----------------STATS-----------------" << std::endl;
	// 	std::cout << "\t\tvecL\t|\tvecR" << std::endl;
	// 	std::cout << "size:\t\t" << vecL.size() << "\t|\t" << vecR.size() << std::endl;
	// 	std::cout << "capacity:\t" << vecL.capacity() << "\t|\t" << vecR.capacity() << std::endl;
	// 	std::cout << "----------------RESULT-----------------" << std::endl;

	// 	std::cout << "vecL == vecR:" << (vecL == vecR) << std::endl;
	// 	std::cout << "vecL != vecR:" << (vecL != vecR) << std::endl;
	// 	std::cout << "vecL <= vecR:" << (vecL <= vecR) << std::endl;
	// 	std::cout << "vecL >= vecR:" << (vecL >= vecR) << std::endl;
	// 	std::cout << "vecL < vecR:" << (vecL < vecR) << std::endl;
	// 	std::cout << "vecL > vecR:" << (vecL > vecR) << std::endl;
	// }
	return (0);
}