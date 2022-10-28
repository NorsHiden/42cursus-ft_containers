/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:02:31 by nelidris          #+#    #+#             */
/*   Updated: 2022/10/28 10:04:08 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_TRAITS_H
# define ITER_TRAITS_H

# include <iostream>

namespace ft
{
	template <class T>
	struct iterator_traits
	{
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
};

#endif /* ITER_TRAITS_H */