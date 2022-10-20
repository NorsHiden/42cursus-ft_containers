/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:23:30 by nelidris          #+#    #+#             */
/*   Updated: 2022/10/17 16:33:09 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TYPE_TRAITS_
# define _TYPE_TRAITS_

namespace ft
{
	
	template <bool C, class _Tp = void> struct enable_if {};
	template <class _Tp> struct enable_if<true, _Tp> { typedef _Tp type; };

	template <class _Tp> struct is_integral { static const bool value = false; };

	template<> struct is_integral<bool> { static const bool value = true; };
	template<> struct is_integral<char> { static const bool value = true; };
	template<> struct is_integral<char16_t> { static const bool value = true; };
	template<> struct is_integral<char32_t> { static const bool value = true; };
	template<> struct is_integral<signed char> { static const bool value = true; };
	template<> struct is_integral<short int> { static const bool value = true; };
	template<> struct is_integral<int> { static const bool value = true; };
	template<> struct is_integral<long int> { static const bool value = true; };
	template<> struct is_integral<long long int> { static const bool value = true; };
	template<> struct is_integral<unsigned char> { static const bool value = true; };
	template<> struct is_integral<unsigned short int> { static const bool value = true; };
	template<> struct is_integral<unsigned long int> { static const bool value = true; };
	template<> struct is_integral<unsigned long long int> { static const bool value = true; };
	
};

#endif /* _TYPE_TRAITS_ */