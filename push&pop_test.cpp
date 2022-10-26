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
	std::vector<str> filler;

	filler.push_back(str("I just"));
	std::cout << "»»»»»»»" << std::endl;
	filler.push_back(str("wanna tell you"));
	std::cout << "»»»»»»»" << std::endl;
	filler.push_back(str("that you got this, alright ?"));
	std::cout << "»»»»»»»" << std::endl;

	// std::vector<str> filler2;

	// filler2.push_back(str("I don't just"));
	// std::cout << "»»»»»»»" << std::endl;
	// filler2.push_back(str("want to tell you"));
	// std::cout << "»»»»»»»" << std::endl;
	// filler2.push_back(str("that you got this, but "));
	// std::cout << "»»»»»»»" << std::endl;
	// filler2.push_back(str("you will do it for sure"));
	// std::cout << "»»»»»»»" << std::endl;

	// std::cout << "std: ";
	// for (std::vector<str>::iterator it = filler.begin(); it != filler.end(); it++)
	// 	std::cout << (*it)._ss << ' ';
	// std::cout << std::endl;
	std::cout << YELLOW << "--------------------------------------" << RESET << std::endl;
	{
		ft::vector<str, myAlloc1<str> > vec(filler.begin(), filler.end());
		ft::vector<str, myAlloc1<str> > vec2;
		str hello("hello");
		str boyyyy("boyyyy,");
		str good("good");
		str bye("byeee");
		str hehe("hehe");
		
		vec2.push_back(hello);
		vec2.push_back(boyyyy);
		vec2.push_back(good);
		vec2.push_back(bye);

		std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
		vec.swap(vec2);
		// vec.resize(2, hehe);
		std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";

		std::cout << "ft_vec: ";
		for (ft::vector<str, myAlloc1<str> >::iterator it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << ' ';
		std::cout << std::endl;
		std::cout << "ft_vec_size: " << vec.size() << std::endl;
		std::cout << "ft_vec_capacity: " << vec.capacity() << std::endl;
		std::cout << "ft_vec_empty: " << vec.empty() << std::endl;
		std::cout << "ft_vec_allocator: " << vec.get_allocator().tt << std::endl;
		std::cout << "ft_vec2: ";
		for (ft::vector<str, myAlloc1<str> >::iterator it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << ' ';
		std::cout << std::endl;
		std::cout << "ft_vec2_size: " << vec2.size() << std::endl;
		std::cout << "ft_vec2_capacity: " << vec2.capacity() << std::endl;
		std::cout << "ft_vec2_empty: " << vec2.empty() << std::endl;
		std::cout << "ft_vec2_allocator: " << vec2.get_allocator().tt << std::endl;
		// std::cout << std::endl;
		// vec.assign(filler.rbegin(), filler.rend());
		// std::cout << "ft: ";
		// for (size_t i = 0; i < vec.size(); i++)
		// 	std::cout << vec[i]._ss << ' ';
		// std::cout << std::endl;
		// std::cout << "ft_size: " << vec.size() << std::endl;
		// std::cout << "ft_capacity: " << vec.capacity() << std::endl;
		// std::cout << "ft_empty: " << vec.empty() << std::endl;
		// std::cout << "ft_allocator: " << vec.get_allocator().tt << std::endl;
	}
	std::cout << YELLOW << "--------------------------------------" << RESET << std::endl;
	{
		std::vector<str, myAlloc1<str> > vec(filler.begin(), filler.end());
		std::vector<str, myAlloc1<str> > vec2;
		str hello("hello");
		str boyyyy("boyyyy,");
		str good("good");
		str bye("byeee");
		str hehe("hehe");
		
		vec2.push_back(hello);
		vec2.push_back(boyyyy);
		vec2.push_back(good);
		vec2.push_back(bye);


		std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";
		vec.swap(vec2);
		// vec.resize(2, hehe);
		std::cout << "∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞∞\n";

		std::cout << "std_vec: ";
		for (std::vector<str, myAlloc1<str> >::iterator it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << ' ';
		std::cout << std::endl;
		std::cout << "std_vec_size: " << vec.size() << std::endl;
		std::cout << "std_vec_capacity: " << vec.capacity() << std::endl;
		std::cout << "std_vec_empty: " << vec.empty() << std::endl;
		std::cout << "std_vec_allocator: " << vec.get_allocator().tt << std::endl;
		std::cout << "std_vec2: ";
		for (std::vector<str, myAlloc1<str> >::iterator it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << ' ';
		std::cout << std::endl;
		std::cout << "std_vec2_size: " << vec2.size() << std::endl;
		std::cout << "std_vec2_capacity: " << vec2.capacity() << std::endl;
		std::cout << "std_vec2_empty: " << vec2.empty() << std::endl;
		std::cout << "std_vec2_allocator: " << vec2.get_allocator().tt << std::endl;

		// vec.assign(filler.rbegin(), filler.rend());
		// std::cout << "std: ";
		// for (auto it = vec.begin(); it != vec.end(); it++)
		// 	std::cout << *it << ' ';
		// std::cout << std::endl;
		// std::cout << "original_size: " << vec.size() << std::endl;
		// std::cout << "original_capacity: " << vec.capacity() << std::endl;
		// std::cout << "original_empty: " << vec.empty() << std::endl;
		// std::cout << "original_allocator: " << vec.get_allocator().tt << std::endl;
	}
	std::cout << YELLOW << "--------------------------------------" << RESET << std::endl;
	return (0);
}