/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:52:11 by nelidris          #+#    #+#             */
/*   Updated: 2022/10/20 16:07:19 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ITERATORS_H_
# define _ITERATORS_H_

#include <iostream>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class T>
	struct iterator_traits
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template<class Category, class T, class Distance = std::ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template<class T>
	class LegacyRandomAccessIterator: ft::iterator<
		typename	iterator_traits<T>::iterator_category,
		typename	iterator_traits<T>::value_type,
		typename	iterator_traits<T>::difference_type,
		typename	iterator_traits<T>::iterator_category,
		typename	iterator_traits<T>::pointer,
		typename	iterator_traits<T>::reference>
	{
		private:
			pointer _p;

		public:
			typedef	const pointer	const_pointer;
			typedef const reference	const_reference;

			LegacyRandomAccessIterator(): _p(0) {}
			LegacyRandomAccessIterator(const reference p): _p(&p) {}
			LegacyRandomAccessIterator(const pointer p): _p(p) {}
			LegacyRandomAccessIterator(const LegacyRandomAccessIterator& other): _p(other._p) {}
			LegacyRandomAccessIterator& operator=(const LegacyRandomAccessIterator& other) { _p = other._p; return (*this); }
			~LegacyRandomAccessIterator() {}

			/* Comparison operators */
			bool	operator==(const LegacyRandomAccessIterator& other) const { return (_p == other._p); }
			bool	operator!=(const LegacyRandomAccessIterator& other) const { return (_p != other._p); }
			bool	operator<(const LegacyRandomAccessIterator& other) const { return (_p < other._p); }
			bool	operator>(const LegacyRandomAccessIterator& other) const { return (_p > other._p); }
			bool	operator<=(const LegacyRandomAccessIterator& other) const { return (_p <= other._p); }
			bool	operator>=(const LegacyRandomAccessIterator& other) const { return (_p >= other._p); }

			/* Dereference operators */
			reference operator*() { return (*_p); }
			const_reference operator*() const { return (*_p); }
			
			pointer operator->() {return (_p);}
			const_pointer operator->() const {return (_p);}

			/* Arithmetic operators */
			LegacyRandomAccessIterator& operator++() { _p++; return (*this); }
			LegacyRandomAccessIterator& operator++(int) { LegacyRandomAccessIterator it; _p++; return (it); }
			LegacyRandomAccessIterator& operator--() { _p--; return (*this); }
			LegacyRandomAccessIterator& operator--(int) { LegacyRandomAccessIterator it; _p--; return (it); }
			LegacyRandomAccessIterator operator+(const size_t& n) const { return (_p + n); }
			LegacyRandomAccessIterator operator-(const size_t& n) const { return (_p - n); }
			LegacyRandomAccessIterator operator-(const LegacyRandomAccessIterator& other) const { return (_p - other._p); }
			LegacyRandomAccessIterator& operator+=(const size_t& n) { _p += n; return (*this); }
			LegacyRandomAccessIterator& operator-=(const size_t& n) { _p -= n; return (*this); }
			
			/* Offset dereference operator */
			reference operator[](const size_t& idx) { return (*(_p + idx)); }
			const_reference operator[](const size_t& idx) const { return (*(_p + idx)); }

			
	};
};

#endif /* _ITERATORS_H_ */