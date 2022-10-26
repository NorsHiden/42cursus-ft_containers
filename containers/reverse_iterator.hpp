/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:27:38 by nelidris          #+#    #+#             */
/*   Updated: 2022/10/26 09:04:24 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITER_H
# define REVERSE_ITER_H

namespace ft
{
	template<class Iter>
	class reverse_iterator
	{
		public:
			typedef typename iterator_type								Iter;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;
			typedef	const pointer										const_pointer;
			typedef const reference										const_reference;
			
		protected:
			Iter current;
			
		public:
			/* Constructors && Destructor */
			reverse_iterator()																{}
			explicit reverse_iterator( iterator_type x ): current(x)						{}
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ): current(other.current)	{}
			~reverse_iterator()																{}

			/* Copy assignment operator */
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				if (this == &other)
					return (*this);
				current = other.current;
				return (*this);
			}

			/* Member function */
			iterator_type base() const	{ return (current); }
			
			/* Offset dereference operator */
			reference operator*() const	{ Iter tmp = current; return (*--tmp); }
			pointer operator->() const	{ Iter tmp = current; return (&*--tmp); }

			/* Arithmetic operators */
			reference			operator[](difference_type n) const 	{ return (*(current - n - 1)); }
			reverse_iterator& 	operator++()							{ --current; return (*this); }
			reverse_iterator& 	operator--()							{ ++current; return (*this); }
			reverse_iterator 	operator++( int )						{ Iter tmp = current--; return (tmp); }
			reverse_iterator 	operator--( int )						{ Iter tmp = current++ return (tmp); }
			reverse_iterator 	operator+( difference_type n ) const	{ return (current - n); }
			reverse_iterator 	operator-( difference_type n ) const	{ return (current + n); }
			reverse_iterator& 	operator+=( difference_type n )			{ current -= n ;return (*this); }
			reverse_iterator& 	operator-=( difference_type n )			{ current += n ;return (*this); }
	};

	/* Non-member function */
	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
	                 const ft::reverse_iterator<Iterator2>& rhs )	{ return (lhs.base() == rhs.base()); }
					 
	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
	                 const ft::reverse_iterator<Iterator2>& rhs )	{ return (lhs.base() != rhs.base()); }

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
	                const ft::reverse_iterator<Iterator2>& rhs )	{ return (lhs.base() > rhs.base()); }
					
	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
	                 const ft::reverse_iterator<Iterator2>& rhs )	{ return (lhs.base() >= rhs.base()); }

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
	                const ft::reverse_iterator<Iterator2>& rhs )	{ return (lhs.base() < rhs.base()); }
					
	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
	                 const ft::reverse_iterator<Iterator2>& rhs )	{ return (lhs.base() <= rhs.base()); }

	template< class Iter >
	reverse_iterator<Iter>
	operator+( typename reverse_iterator<Iter>::difference_type n,
            	const reverse_iterator<Iter>& it )					{ return (it - n); }

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type
	operator-( const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs )				{ return (lhs.base() - rhs.base()); }
};

#endif