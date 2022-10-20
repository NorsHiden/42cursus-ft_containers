#include <iostream>
#include <vector>
// #include "containers/vector.hpp"

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
	std::vector<str> v1;
	std::vector<str> v2;


	v1.push_back(str("a"));
	v1.push_back(str("b"));
	v1.push_back(str("c"));
	v1.push_back(str("d"));
	str hh("ok");

	std::vector<str>::iterator it = v1.end();
	std::cout << *it << std::endl;
	// // v1.push_back("e");
	// v2.push_back(str("a"));
	// v2.push_back(str("b"));
	// v2.push_back(str("c"));
	// v2.push_back(str("d"));

	// std::vector<str>::iterator;
	// std::cout << (v1 <= v2) << std::endl;
	return (0);
}