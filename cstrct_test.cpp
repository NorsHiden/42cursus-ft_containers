/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:05:43 by marvin            #+#    #+#             */
/*   Updated: 2022/10/05 20:05:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	func()
{
	myAlloc1<int> *alloc = new myAlloc1<int>();
	alloc->tt = "my_alloc_myAlloc1";
	std::vector<int> filler;
	filler.push_back(1);
	filler.push_back(2);
	filler.push_back(3);
	filler.push_back(2);
	std::vector<int, myAlloc1<int> > filler_vec(filler.begin(), filler.end(), *alloc);
	delete alloc;
	{
		std::vector<int, myAlloc1<int> > vec;
		vec = filler_vec;

		std::cout << "or: ";
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << ' ';
		std::cout << std::endl;

		std::cout << "original_size: " << vec.size() << std::endl;
		std::cout << "original_capacity: " << vec.capacity() << std::endl;
		std::cout << "original_empty: " << vec.empty() << std::endl;
		std::cout << "original_allocator: " << vec.get_allocator().tt << std::endl;
	}
	std::cout << std::endl;
	{
		ft::vector<int, myAlloc1<int> > ft_filler_vec(filler.begin(), filler.end(), *alloc);
		ft::vector<int, myAlloc1<int> > ft_vec;

		ft_vec = ft_filler_vec;

		std::cout << "ft_size: " << ft_vec.size() << std::endl;
		std::cout << "ft_capacity: " << ft_vec.capacity() << std::endl;
		std::cout << "ft_empty: " << ft_vec.empty() << std::endl;
		std::cout << "ft_allocator: " << ft_vec.get_allocator().tt << std::endl;
	}
}

int main(void)
{
	func();
	// system("leaks tt");

	// for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	// 	std::cout << *it << std::endl;
	return (0);
}