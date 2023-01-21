/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:23:30 by nelidris          #+#    #+#             */
/*   Updated: 2022/10/28 14:34:58 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TYPE_TRAITS_
# define _TYPE_TRAITS_

namespace ft
{
	template <bool C, class _Tp = void> struct enable_if		{};
	template <class _Tp> struct enable_if<true, _Tp>			{ typedef _Tp type; };

	template< class T > struct remove_const          			{ typedef T type; };
	template< class T > struct remove_const<const T> 			{ typedef T type; };

	template< class T > struct remove_volatile             		{ typedef T type; };
	template< class T > struct remove_volatile<volatile T> 		{ typedef T type; };
	
	template< class T >
	struct remove_cv {
		typedef typename ft::remove_volatile<typename ft::remove_const<T>::type >::type type;
	};
	
	template <class _Tp> struct is_integral_base					{ static const bool value = false; };
	
	template<> struct is_integral_base<bool>						{ static const bool value = true; };
	template<> struct is_integral_base<char>						{ static const bool value = true; };
	template<> struct is_integral_base<signed char>					{ static const bool value = true; };
	template<> struct is_integral_base<short int>					{ static const bool value = true; };
	template<> struct is_integral_base<int>							{ static const bool value = true; };
	template<> struct is_integral_base<long int>					{ static const bool value = true; };
	template<> struct is_integral_base<long long int>				{ static const bool value = true; };
	template<> struct is_integral_base<unsigned char>				{ static const bool value = true; };
	template<> struct is_integral_base<unsigned short int>			{ static const bool value = true; };
	template<> struct is_integral_base<unsigned int>				{ static const bool value = true; };
	template<> struct is_integral_base<unsigned long int>			{ static const bool value = true; };
	template<> struct is_integral_base<unsigned long long int>		{ static const bool value = true; };

	template <class _Tp> struct is_integral : ft::is_integral_base< typename remove_cv<_Tp>::type > {};
};

#endif /* _TYPE_TRAITS_ */