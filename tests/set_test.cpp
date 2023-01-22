/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:44:00 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/22 18:29:31 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include <set.hpp>

#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define CLEAR "\033[0;37m"

void	printSets(ft::set<int> &ft_s, std::set<int> &std_s)
{
	std::cout << YELLOW << "ft_s size = " << ft_s.size() << CLEAR << std::endl;
	std::cout << GREEN << "std_s size = " << std_s.size() << CLEAR << std::endl;
	std::cout << YELLOW << "ft_s content = ";
	for (ft::set<int>::iterator it = ft_s.begin(); it != ft_s.end(); ++it)
		std::cout << (*it) << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << GREEN << "std_s content = ";
	for (std::set<int>::iterator it = std_s.begin(); it != std_s.end(); ++it)
		std::cout << (*it) << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << YELLOW << "ft_s reversed content = ";
	for (ft::set<int>::reverse_iterator it = ft_s.rbegin(); it != ft_s.rend(); ++it)
		std::cout << (*it) << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << GREEN << "std_s reversed content = ";
	for (std::set<int>::reverse_iterator it = std_s.rbegin(); it != std_s.rend(); ++it)
		std::cout << (*it) << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << "----------------------------" << std::endl;
}

int main(void)
{
	ft::set<int> ft_s;
	std::set<int> std_s;

	ft_s.insert(15);
	ft_s.insert(132);
	ft_s.insert(22);
	ft_s.insert(74);
	ft_s.insert(21);
	ft_s.insert(99);
	ft_s.insert(99);
	ft_s.insert(99);
	ft_s.insert(99);

	std_s.insert(15);
	std_s.insert(132);
	std_s.insert(22);
	std_s.insert(74);
	std_s.insert(21);
	std_s.insert(99);
	std_s.insert(99);
	std_s.insert(99);
	std_s.insert(99);
	printSets(ft_s, std_s);

	ft::set<int>::iterator ft_it = ft_s.begin();
	std::set<int>::iterator std_it = std_s.begin();
	std::advance(ft_it, 3);
	std::advance(std_it, 3);
	ft_s.erase(ft_it, ft_s.end());
	std_s.erase(std_it, std_s.end());
	printSets(ft_s, std_s);
	ft_s.clear();
	std_s.clear();
	printSets(ft_s, std_s);
}