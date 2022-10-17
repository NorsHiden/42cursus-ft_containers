#include <iostream>
#include <vector>
#include "containers/vector.hpp"

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

int main(void)
{
	std::vector<int> filler;

	filler.push_back(0);
	filler.push_back(1);
	filler.push_back(2);
	filler.push_back(3);
	filler.push_back(4);
	filler.push_back(5);
	filler.push_back(6);
	filler.push_back(7);
	{
		ft::vector<int, myAlloc1<int> > vec;
		vec.assign(filler.begin(), filler.end());
		std::cout << "ft_size: " << vec.size() << std::endl;
		std::cout << "ft_capacity: " << vec.capacity() << std::endl;
		std::cout << "ft_empty: " << vec.empty() << std::endl;
		std::cout << "ft_allocator: " << vec.get_allocator().tt << std::endl;
		std::cout << std::endl;
		vec.assign(filler.rbegin(), filler.rend());
		std::cout << "ft_size: " << vec.size() << std::endl;
		std::cout << "ft_capacity: " << vec.capacity() << std::endl;
		std::cout << "ft_empty: " << vec.empty() << std::endl;
		std::cout << "ft_allocator: " << vec.get_allocator().tt << std::endl;
	}
	std::cout << "--------------------------------------" << std::endl;
	{
		std::vector<int, myAlloc1<int> > vec;
		vec.assign(filler.begin(), filler.end());
		std::cout << "std: ";
		for (auto it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << ' ';
		std::cout << std::endl;
		std::cout << "original_size: " << vec.size() << std::endl;
		std::cout << "original_capacity: " << vec.capacity() << std::endl;
		std::cout << "original_empty: " << vec.empty() << std::endl;
		std::cout << "original_allocator: " << vec.get_allocator().tt << std::endl;

		vec.assign(filler.rbegin(), filler.rend());
		std::cout << "std: ";
		for (auto it = vec.begin(); it != vec.end(); it++)
			std::cout << *it << ' ';
		std::cout << std::endl;
		std::cout << "original_size: " << vec.size() << std::endl;
		std::cout << "original_capacity: " << vec.capacity() << std::endl;
		std::cout << "original_empty: " << vec.empty() << std::endl;
		std::cout << "original_allocator: " << vec.get_allocator().tt << std::endl;
	}


	return (0);
}