/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:32:03 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/22 18:36:18 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <stack.hpp>

#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define CLEAR "\033[0;37m"

void	printStacks(ft::stack<int> &ft_st, std::stack<int> &std_st)
{
	std::cout << YELLOW << "ft_st size = " << ft_st.size() << CLEAR << std::endl;
	std::cout << GREEN << "std_st size = " << std_st.size() << CLEAR << std::endl;
	std::cout << YELLOW << "ft_st empty = " << ft_st.empty() << CLEAR << std::endl;
	std::cout << GREEN << "std_st empty = " << std_st.empty() << CLEAR << std::endl;
	std::cout << YELLOW << "ft_st top = " << ft_st.top() << CLEAR << std::endl;
	std::cout << GREEN << "std_st content = "<< std_st.top() << CLEAR << std::endl;
	std::cout << "----------------------------" << std::endl;
}

int main(void)
{
	ft::stack<int> ft_st;
	std::stack<int> std_st;

	ft_st.push(10);
	std_st.push(10);
	printStacks(ft_st, std_st);

	ft_st.push(12);
	ft_st.push(33);
	ft_st.push(77);
	std_st.push(12);
	std_st.push(33);
	std_st.push(77);
	printStacks(ft_st, std_st);

	ft_st.pop();
	std_st.pop();
	printStacks(ft_st, std_st);
}