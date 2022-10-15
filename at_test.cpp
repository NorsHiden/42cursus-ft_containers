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
	{
		ft::vector<int, myAlloc1<int> > vec/*(filler.begin(), filler.end())*/;


		// std::cout << "ft: " << *(vec.data() + 1) << std::endl;
		// std::cout << "ft max_size: " << vec.max_size() << std::endl;
		vec.reserve(5);
		vec.reserve(6);
		std::cout << "ft_capacity: " << vec.capacity() << std::endl;
		// vec[1] = 99;

		// std::cout << "ft: ";
		// for (size_t i = 0; i < vec.size(); i++)
		// 	std::cout << vec[i] << ' ';
		// std::cout << std::endl;
	}

	std::cout << "--------------------------------------" << std::endl;

	{
		std::vector<int, myAlloc1<int> > vec/*(filler.begin(), filler.end())*/;

		// std::cout << "std: " << *vec.data() << std::endl;
		vec.reserve(5);
		vec.reserve(6);
		std::cout << "std_capacity: " << vec.capacity() << std::endl;
		// vec[1] = 99;

		// std::cout << "std: ";
		// for (size_t i = 0; i < vec.size(); i++)
		// 	std::cout << vec[i] << ' ';
		// // for (auto it = vec.begin(); it != vec.end(); it++)
		// // 	std::cout << *it << ' ';
		// std::cout << std::endl;
	}


	return (0);
}