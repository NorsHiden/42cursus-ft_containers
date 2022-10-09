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

template<typename T>
struct myAlloc1: std::allocator<T>
{

	template< class U > struct rebind {
    	typedef myAlloc1<U> other;
	};

	myAlloc1(): std::allocator<T>() { std::cout << "default constructor of myAlloc1 has been called" << std::endl;}
	T* allocate(size_t size)
	{
		std::cout << "myAlloc1 size: " << size << " needed" << std::endl;
		return (new T[size]);
	}
};

template<typename T>
struct myAlloc2: std::allocator<T>
{

	template< class U > struct rebind {
    	typedef myAlloc2<U> other;
	};

	myAlloc2(): std::allocator<T>() { std::cout << "default constructor of myAlloc2 has been called" << std::endl;}
	T* allocate(size_t size)
	{
		std::cout << "myAlloc2 size: " << size << " needed" << std::endl;
		return (new T[size]);
	}
};

int main(void)
{

	// myAlloc1<int> *alloc = new myAlloc1<int>();
	std::vector<int, myAlloc1<int> > vec;

	vec.reserve(10);
	vec.reserve(9);
	vec.reserve(10);
	vec.reserve(10);
	vec.reserve(10);
	vec.reserve(10);
	vec.reserve(11);
	vec.reserve(10);
	// // // vec.clear();)
	// // // vec.pop_back();
	// vec.push_back(1);
	// // vec.reserve(10);
	// // vec.reserve(5);
	// vec.push_back(3);
	// vec.push_back(2);
	// vec.push_back(1);
	// vec.push_back(0);
	// vec.push_back(-1);
	// vec.push_back(-2);
	// vec.push_back(-3);
	// vec.push_back(-4);
	// vec.push_back(-5);
	// vec.push_back(-6);
	// // vec.pop_back();

	// for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	// 	std::cout << *it << std::endl;
	return (0);
}