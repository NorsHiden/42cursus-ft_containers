#include <iostream>
#include <vector>
#include "containers/vector.hpp"

struct str
{
	std::string _ss;

	str() { std::cout << "str default constructor boyyyy" << std::endl; }
	str(const  std::string ss): _ss(ss) { std::cout << "str init constructor boyyy" << std::endl; }
	str(const str& other): _ss(other._ss) { std::cout << "str copy constructor boyyy" << std::endl; }
	str& operator=(const str& other) { _ss = other._ss; std::cout << "str copy assignment boyyy" << std::endl; return (*this); }
	~str() { std::cout << "str destructor" << std::endl; }
};

template<typename T>
struct myAlloc1: std::allocator<T>
{
	// template< class U > struct rebind {
    // 	typedef myAlloc1<U> other;
	// };
	std::allocator<T> or_alloc;
	std::string tt;
	myAlloc1(): std::allocator<T>() { std::cout << "default constructor of myAlloc1 has been called" << std::endl;}
	T* allocate(size_t size)
	{
		std::cout << "myAlloc1 size: " << size << " needed" << std::endl;
		return (or_alloc.allocate(size));
	}
	void deallocate( T* p, std::size_t n )
	{
		std::cout << "myAlloc1 address: " << p << ", size:" << n << " deallocated" << std::endl;
		or_alloc.deallocate(p, n);
	}
	myAlloc1(const myAlloc1& other): std::allocator<T>(other), tt(other.tt)
	{
		std::cout << "copy constructor of myAlloc1 has been called" << std::endl;
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

	std::vector<str> filler2;

	filler2.push_back(str("I don't just"));
	std::cout << "»»»»»»»" << std::endl;
	filler2.push_back(str("want to tell you"));
	std::cout << "»»»»»»»" << std::endl;
	filler2.push_back(str("that you got this, but "));
	std::cout << "»»»»»»»" << std::endl;
	filler2.push_back(str("you will do it for sure"));
	std::cout << "»»»»»»»" << std::endl;

	// std::cout << "std: ";
	// for (std::vector<str>::iterator it = filler.begin(); it != filler.end(); it++)
	// 	std::cout << (*it)._ss << ' ';
	// std::cout << std::endl;
	// filler.push_back(3);
	// filler.push_back(4);
	// filler.push_back(5);
	// filler.push_back(6);
	// filler.push_back(7);
	{
		ft::vector<str, myAlloc1<str> > vec1;
		vec1.assign(filler.begin(), filler.end());
		ft::vector<str, myAlloc1<str> > vec;
		vec.reserve(100);
		vec.assign(filler2.begin(), filler2.end());
		vec = vec1;
		// vec.clear();
		std::cout << "ft: ";
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i]._ss << ' ';
		std::cout << std::endl;
		std::cout << "ft_size: " << vec.size() << std::endl;
		std::cout << "ft_capacity: " << vec.capacity() << std::endl;
		std::cout << "ft_empty: " << vec.empty() << std::endl;
		std::cout << "ft_allocator: " << vec.get_allocator().tt << std::endl;
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
	std::cout << "--------------------------------------" << std::endl;
	{
		std::vector<str, myAlloc1<str> > vec1;
		vec1.assign(filler.begin(), filler.end());
		std::vector<str, myAlloc1<str> > vec;
		vec.reserve(100);
		vec.assign(filler2.begin(), filler2.end());
		vec = vec1;
		// vec.clear();

		std::cout << "std: ";
		for (auto it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << ' ';
		std::cout << std::endl;
		std::cout << "original_size: " << vec.size() << std::endl;
		std::cout << "original_capacity: " << vec.capacity() << std::endl;
		std::cout << "original_empty: " << vec.empty() << std::endl;
		std::cout << "original_allocator: " << vec.get_allocator().tt << std::endl;

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
	std::cout << "--------------------------------------" << std::endl;
	return (0);
}