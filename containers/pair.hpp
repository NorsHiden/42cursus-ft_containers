/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:13:06 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/01 13:52:51 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PAIR_H_
# define _PAIR_H_

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		typedef	T1 first_type;
		typedef	T2 second_type;

		first_type	first;
		second_type	second;

		/* Constructors */
		pair() {}
		pair( const first_type& a, const second_type& b ): first(a), second(b) {}
		
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ): first(p.first), second(p.second) {}

		/*Copy assignment operator */
		pair& operator=(const pair& pr)
		{
			if (this == &pr)
				return (*this);
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};
	
	/* Non-member Functions */
	template< class T1, class T2 >
	ft::pair<T1, T2> make_pair( T1 t, T2 u ) { return (ft::pair(t, u)); }

	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (lhs.first < rhs.first && lhs.second < rhs.second);
	}
	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return ((lhs < rhs) || (lhs == rhs));
	}

	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(lhs < rhs));
	}
	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return ((lhs > rhs) || (lhs == rhs));
	}
};


#endif /* _PAIR_H_ */