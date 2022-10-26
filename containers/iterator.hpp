/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:52:11 by nelidris          #+#    #+#             */
/*   Updated: 2022/10/26 09:04:15 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ITERATORS_H_
# define _ITERATORS_H_

# include <iostream>
# include "iterator_traits.hpp"

namespace ft
{
	template<class T>
	class Iterator
	{
		public:
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;
			typedef	const pointer									const_pointer;
			typedef const reference									const_reference;
			
		private:
			pointer _p;
			
		public:
			/* Constructors && Destructor */
			Iterator(): _p(0)								{}
			Iterator(const reference p): _p(&p)				{}
			Iterator(const pointer p): _p(p)				{}
			Iterator(const Iterator& other): _p(other._p)	{}
			~Iterator()										{}
			
			/* Copy assignment operator */
			Iterator& operator=(const Iterator& other)
			{
				if (this == &other)
					return (*this);
				_p = other._p;
				return (*this);
			}

			/* Comparison operators */
			bool	operator==(const Iterator& other) const	{ return (_p == other._p); }
			bool	operator!=(const Iterator& other) const	{ return (_p != other._p); }
			bool	operator<(const Iterator& other) const	{ return (_p < other._p); }
			bool	operator>(const Iterator& other) const	{ return (_p > other._p); }
			bool	operator<=(const Iterator& other) const	{ return (_p <= other._p); }
			bool	operator>=(const Iterator& other) const	{ return (_p >= other._p); }

			/* Dereference operators */
			reference		operator*()			{ return (*_p); }
			const_reference	operator*() const	{ return (*_p); }
			
			pointer			operator->()		{return (_p);}
			const_pointer	operator->() const	{return (_p);}

			/* Arithmetic operators */
			Iterator&	operator++()							{ _p++; return (*this); }
			Iterator	operator++(int)							{ Iterator it; _p++; return (it); }
			Iterator&	operator--()							{ _p--; return (*this); }
			Iterator	operator--(int)							{ Iterator it; _p--; return (it); }
			Iterator	operator+(const size_t& n) const		{ return (_p + n); }
			Iterator	operator-(const size_t& n) const		{ return (_p - n); }
			Iterator&	operator+=(const size_t& n)				{ _p += n; return (*this); }
			Iterator&	operator-=(const size_t& n)				{ _p -= n; return (*this); }
			long		operator-(const Iterator& other) const	{ return (_p - other._p); }
			
			/* Offset dereference operator */
			reference operator[](const size_t& idx)				{ return (*(_p + idx)); }
			const_reference operator[](const size_t& idx) const	{ return (*(_p + idx)); }

			/* Member function */
			pointer	base() const { return (_p); }
	};
};

#endif /* _ITERATORS_H_ */