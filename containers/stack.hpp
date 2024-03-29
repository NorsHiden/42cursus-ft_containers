/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/21 16:38:41 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STACK_H_
# define _STACK_H_

# include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
		
		protected:
			Container c;
		
		public:
			/* Constructors && Destructor */
			explicit stack( const Container& cont = Container() ): c(cont)	{}
			stack( const stack& other ): c(other.c)							{}
			~stack()														{}

			/* Copy assignment operator */
			stack& operator=( const stack& other )
			{
				if (this == &other)
					return (*this);
				c = other.c;
				return (*this);
			}

			/* Element access */
			reference top()							{ return (c.back()); }
			const_reference top() const				{ return (c.back()); }
			
			/* Capacity */
			bool empty() const						{ return (c.empty()); }
			size_type size() const					{ return (c.size()); }

			/* Modifiers */
			void push( const value_type& value )	{ c.push_back(value); }
			void pop()								{ c.pop_back(); }

			/* Friend functions */
			template< class _Tp, class _Container >
			friend bool operator==( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs );
			template< class  _Tp, class _Container >
			friend bool operator!=( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs );
			template< class  _Tp, class _Container >
			friend bool operator<( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs );
			template< class  _Tp, class _Container >
			friend bool operator<=( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs );
			template< class  _Tp, class _Container >
			friend bool operator>( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs );
			template< class  _Tp, class _Container >
			friend bool operator>=( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs );
	};

	/* Non-member functions */
	template< class _Tp, class _Container >
	bool operator==( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs )	{ return (lhs.c == rhs.c); }
	template< class _Tp, class _Container >
	bool operator!=( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs )	{ return (lhs.c != rhs.c); }
	template< class _Tp, class _Container >
	bool operator<( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs )	{ return (lhs.c < rhs.c); }
	template< class _Tp, class _Container >
	bool operator<=( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs )	{ return (lhs.c <= rhs.c); }
	template< class _Tp, class _Container >
	bool operator>( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs )	{ return (lhs.c > rhs.c); }
	template< class _Tp, class _Container >
	bool operator>=( const ft::stack<_Tp,_Container>& lhs, const ft::stack<_Tp,_Container>& rhs )	{ return (lhs.c >= rhs.c); }
};


#endif /* _STACK_H_ */