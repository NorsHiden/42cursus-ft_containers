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
	// std::cout << YELLOW << "•••••••••••••••••••FT•••••••••••••••••••" << RESET << std::endl;
	// {
	// 	ft::vector<str, myAlloc1<str> > v1;

	// 	v1.reserve(5);

	// 	str hello("hello");
	// 	str boyyyy("boyyyy,");
	// 	str good("good");
	// 	str bye("byeee");
	// 	str hehe1("hehe1");
	// 	str hehe2("hehe2");
		
	// 	v1.push_back(hello);
	// 	v1.push_back(boyyyy);
	// 	v1.push_back(good);
	// 	v1.push_back(bye);
	// 	for (ft::vector<str, myAlloc1<str> >::iterator it = v1.begin(); it != v1.end(); it++)
	// 		std::cout << *it << ' ';
	// 	std::cout << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	std::cout << *v1.erase(v1.begin(), v1.end()) << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	for (ft::vector<str, myAlloc1<str> >::iterator it = v1.begin(); it != v1.end(); it++)
	// 		std::cout << *it << ' ';
	// 	std::cout << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	// std::cout << *v1.erase(v1.end(), hehe2) << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	// v1.insert(v1.end(), 1, 2);
	// 	// v1.insert(v1.end(), 33);
	// 	for (ft::vector<str, myAlloc1<str> >::iterator it = v1.begin(); it != v1.end(); it++)
	// 		std::cout << *it << ' ';
	// 	std::cout << std::endl;
	// }
	// std::cout << YELLOW << "•••••••••••••••••••STD•••••••••••••••••••" << RESET << std::endl;
	// {
	// 	std::vector<str, myAlloc1<str> > v1;

	// 	v1.reserve(5);

	// 	str hello("hello");
	// 	str boyyyy("boyyyy,");
	// 	str good("good");
	// 	str bye("byeee");
	// 	str hehe1("hehe1");
	// 	str hehe2("hehe2");
		
	// 	v1.push_back(hello);
	// 	v1.push_back(boyyyy);
	// 	v1.push_back(good);
	// 	v1.push_back(bye);
	// 	for (std::vector<str, myAlloc1<str> >::iterator it = v1.begin(); it != v1.end(); it++)
	// 		std::cout << *it << ' ';
	// 	std::cout << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	std::cout << *v1.erase(v1.begin(), v1.end()) << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	for (std::vector<str, myAlloc1<str> >::iterator it = v1.begin(); it != v1.end(); it++)
	// 		std::cout << *it << ' ';
	// 	std::cout << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	// std::cout << *v1.erase(v1.begin(), v1.end() - 1) << std::endl;
	// 	std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
	// 	// v1.insert(v1.end(), 1, 2);
	// 	// v1.insert(v1.end(), 33);
	// 	for (std::vector<str, myAlloc1<str> >::iterator it = v1.begin(); it != v1.end(); it++)
	// 		std::cout << *it << ' ';
	// 	std::cout << std::endl;
	// }

	std::vector<int> vec1;
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);

	std::vector<int> vec2;
	vec2.push_back(1);
	vec2.push_back(2);
	vec2.push_back(3);
	vec2.push_back(4);

	std::cout << (vec1 <= vec2) << std::endl;
	return (0);
}