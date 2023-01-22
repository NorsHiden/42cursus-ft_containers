/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:44:00 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/22 18:17:24 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <vector.hpp>

#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define CLEAR "\033[0;37m"

void	printVectors(ft::vector<int> &ft_v, std::vector<int> &std_v)
{
	std::cout << YELLOW << "ft_v size = " << ft_v.size() << CLEAR << std::endl;
	std::cout << GREEN << "std_v size = " << std_v.size() << CLEAR << std::endl;
	std::cout << YELLOW << "ft_v capacity = " << ft_v.capacity() << CLEAR << std::endl;
	std::cout << GREEN << "std_v capacity = " << std_v.capacity() << CLEAR << std::endl;
	std::cout << YELLOW << "ft_v content = ";
	for (ft::vector<int>::iterator it = ft_v.begin(); it != ft_v.end(); ++it)
		std::cout << *it << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << GREEN << "std_v content = ";
	for (std::vector<int>::iterator it = std_v.begin(); it != std_v.end(); ++it)
		std::cout << *it << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << YELLOW << "ft_v reversed content = ";
	for (ft::vector<int>::reverse_iterator it = ft_v.rbegin(); it != ft_v.rend(); ++it)
		std::cout << *it << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << GREEN << "std_v reversed content = ";
	for (std::vector<int>::reverse_iterator it = std_v.rbegin(); it != std_v.rend(); ++it)
		std::cout << *it << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << "----------------------------" << std::endl;
}

int main(void)
{
	ft::vector<int> ft_v;
	std::vector<int> std_v;

	ft_v.assign(10, 15);
	std_v.assign(10, 15);
	printVectors(ft_v, std_v);
	ft_v.push_back(99);
	ft_v.push_back(102);
	ft_v.push_back(300);
	std_v.push_back(99);
	std_v.push_back(102);
	std_v.push_back(300);
	printVectors(ft_v, std_v);
	ft_v.erase(ft_v.begin() + 2, ft_v.end() - 2);
	std_v.erase(std_v.begin() + 2, std_v.end() - 2);
	printVectors(ft_v, std_v);
	ft_v.reserve(1000);
	std_v.reserve(1000);
	printVectors(ft_v, std_v);
	ft_v.clear();
	std_v.clear();
	printVectors(ft_v, std_v);
}