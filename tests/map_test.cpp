/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:44:00 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/22 18:26:05 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <map.hpp>

#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define CLEAR "\033[0;37m"

void	printMaps(ft::map<int, int> &ft_m, std::map<int, int> &std_m)
{
	std::cout << YELLOW << "ft_m size = " << ft_m.size() << CLEAR << std::endl;
	std::cout << GREEN << "std_m size = " << std_m.size() << CLEAR << std::endl;
	std::cout << YELLOW << "ft_m content = ";
	for (ft::map<int, int>::iterator it = ft_m.begin(); it != ft_m.end(); ++it)
		std::cout << (*it).first << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << GREEN << "std_m content = ";
	for (std::map<int, int>::iterator it = std_m.begin(); it != std_m.end(); ++it)
		std::cout << (*it).first << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << YELLOW << "ft_m reversed content = ";
	for (ft::map<int, int>::reverse_iterator it = ft_m.rbegin(); it != ft_m.rend(); ++it)
		std::cout << (*it).first << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << GREEN << "std_m reversed content = ";
	for (std::map<int, int>::reverse_iterator it = std_m.rbegin(); it != std_m.rend(); ++it)
		std::cout << (*it).first << ' ';
	std::cout << CLEAR << std::endl;
	std::cout << "----------------------------" << std::endl;
}

int main(void)
{
	ft::map<int, int> ft_m;
	std::map<int, int> std_m;

	ft_m.insert(ft::make_pair(15,15));
	ft_m.insert(ft::make_pair(132,132));
	ft_m.insert(ft::make_pair(22,22));
	ft_m.insert(ft::make_pair(74,74));
	ft_m.insert(ft::make_pair(21,21));
	ft_m.insert(ft::make_pair(99,99));
	ft_m.insert(ft::make_pair(99,99));
	ft_m.insert(ft::make_pair(99,99));
	ft_m.insert(ft::make_pair(99,99));

	std_m.insert(std::make_pair(15,15));
	std_m.insert(std::make_pair(132,132));
	std_m.insert(std::make_pair(22,22));
	std_m.insert(std::make_pair(74,74));
	std_m.insert(std::make_pair(21,21));
	std_m.insert(std::make_pair(99,99));
	std_m.insert(std::make_pair(99,99));
	std_m.insert(std::make_pair(99,99));
	std_m.insert(std::make_pair(99,99));
	printMaps(ft_m, std_m);

	ft::map<int, int>::iterator ft_it = ft_m.begin();
	std::map<int, int>::iterator std_it = std_m.begin();
	std::advance(ft_it, 3);
	std::advance(std_it, 3);
	ft_m.erase(ft_it, ft_m.end());
	std_m.erase(std_it, std_m.end());
	printMaps(ft_m, std_m);
	ft_m.clear();
	std_m.clear();
	printMaps(ft_m, std_m);
}