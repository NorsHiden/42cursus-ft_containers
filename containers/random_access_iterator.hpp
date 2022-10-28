/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:52:11 by nelidris          #+#    #+#             */
/*   Updated: 2022/10/28 10:18:18 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RANDOMACCESSITERATORS_H_
# define _RANDOMACCESSITERATORS_H_

# include <iostream>
# include "iterator_traits.hpp"

namespace ft
{
	template<class T>
	class RandomAccessIterator
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
			RandomAccessIterator(): _p(0)																	{}
			RandomAccessIterator(const reference p): _p(&p)													{}
			RandomAccessIterator(const pointer p): _p(p)													{}
			template<class U>
			RandomAccessIterator(const RandomAccessIterator<U>& other): _p(other.base())					{}
			~RandomAccessIterator()																			{}
			
			/* Copy assignment operator */
			RandomAccessIterator& operator=(const RandomAccessIterator& other)
			{
				if (this == &other)
					return (*this);
				_p = other._p;
				return (*this);
			}

			/* Comparison operators */
			template<class U>
			bool	operator==(const RandomAccessIterator<U>& other) const	{ return (_p == other.base()); }
			template<class U>
			bool	operator!=(const RandomAccessIterator<U>& other) const	{ return (_p != other.base()); }
			template<class U>
			bool	operator<(const RandomAccessIterator<U>& other) const	{ return (_p < other.base()); }
			template<class U>
			bool	operator>(const RandomAccessIterator<U>& other) const	{ return (_p > other.base()); }
			template<class U>
			bool	operator<=(const RandomAccessIterator<U>& other) const	{ return (_p <= other.base()); }
			template<class U>
			bool	operator>=(const RandomAccessIterator<U>& other) const	{ return (_p >= other.base()); }

			/* Dereference operators */
			reference		operator*()			{ return (*_p); }
			const_reference	operator*() const	{ return (*_p); }
			
			pointer			operator->()		{return (_p);}
			const_pointer	operator->() const	{return (_p);}

			/* Arithmetic operators */
			RandomAccessIterator&	operator++() 							{ _p++; return (*this); }
			RandomAccessIterator	operator++(int) 						{ RandomAccessIterator it(_p); _p++; return (it); }
			RandomAccessIterator&	operator--() 							{ _p--; return (*this); }
			RandomAccessIterator	operator--(int) 						{ RandomAccessIterator it(_p); _p--; return (it); }
			
			RandomAccessIterator	operator+(const size_t& n) const		{ return (_p + n); }
			RandomAccessIterator	operator-(const size_t& n) const		{ return (_p - n); }
			RandomAccessIterator&	operator+=(const size_t& n)				{ _p += n; return (*this); }
			RandomAccessIterator&	operator-=(const size_t& n)				{ _p -= n; return (*this); }
			
			long		operator-(const RandomAccessIterator& other) const	{ return (_p - other._p); }
			
			/* Offset dereference operator */
			reference operator[](const size_t& idx)				{ return (*(_p + idx)); }
			const_reference operator[](const size_t& idx) const	{ return (*(_p + idx)); }

			/* Member function */
			pointer	base() const { return (_p); }
			// pointer const base() const { return (_p); }
	};
	
	template<class T>
	ft::RandomAccessIterator<T>	operator+(const size_t& n, const ft::RandomAccessIterator<T>& it) { return (it + n); }
};

#endif /* _RANDOMACCESSITERATORS_H_ */