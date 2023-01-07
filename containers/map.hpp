/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:06:15 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/07 12:39:20 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CON_MAP_
# define _CON_MAP_

# include <iostream>
# include "pair.hpp"

namespace ft
{
	template<
    	class Key,
    	class T,
		class Compare = std::less<Key>,
    	class Allocator = std::allocator<ft::pair<const Key, T> >
	> class map
	{
		public:
			typedef	Key						key_type;
			typedef	mapped_type				T;
			typedef	value_type				ft::pair<const Key, T>;
			typedef	size_type				std::size_t;
			typedef	difference_type			std::ptrdiff_t;
			typedef	key_compare				Compare;
			typedef	allocator_type			Allocator;
			typedef	reference				allocator_type::reference;
			typedef	const_reference			allocator_type::const_reference;
			typedef	pointer					allocator_type::pointer;
			typedef	const_pointer			allocator_type::const_pointer;
			typedef	iterator				std::map<Key, T, Compare, Allocator>::iterator;
			typedef	const_iterator			std::map<Key, T, Compare, Allocator>::const_iterator;
			typedef	reverse_iterator		std::map<Key, T, Compare, Allocator>::reverse_iterator;
			typedef	const_reverse_iterator	std::map<Key, T, Compare, Allocator>::const_reverse_iterator;
			
			private:
				// is coming soon..
			
			public:
				/* Function object */
				class value_compare;
				
				/* Constructors & Destructor */
				map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
				
				template<class InputIterator>
				map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& = allocator_type());

				map (const map& x);

				map& operator= (const map& x);

				~map ();

				/* Iterators */
				iterator begin ();

				const_iterator begin () const;
				
				iterator end ();
				
				const_iterator end () const;

				reverse_iterator rbegin ();
				
				const_reverse_iterator rbegin () const;

				reverse_iterator rend ();
				
				const_reverse_iterator rend () const;

				/* Capacity */
				bool empty () const;

				size_type size () const;
				
				size_type max_size () const;

				/* Element access */
				mapped_type& operator[] (const key_type& k);
				
				mapped_type& at (const key_type& k);
				
				const mapped_type& at (const key_type& k) const;

				/* Modifiers */
				pair<iterator,bool> insert (const value_type& val);

				iterator insert (iterator position, const value_type& val);

				template <class InputIterator> 
				void insert (InputIterator first, InputIterator last);
				
				void erase (iterator position);
				
				size_type erase (const key_type& k);
				
				void erase (iterator first, iterator last);
				
				void swap (map& x);

				void clear();

				/* Lookup */
				iterator find (const key_type& k);
				
				const_iterator find (const key_type& k) const;
				
				size_type count (const key_type& k) const;

				iterator lower_bound (const key_type& k);
				
				const_iterator lower_bound (const key_type& k) const;

				iterator upper_bound (const key_type& k);
				
				const_iterator upper_bound (const key_type& k) const;

				pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
				
				pair<iterator,iterator>	equal_range (const key_type& k);

				/* Allocator */
				allocator_type get_allocator() const;
	};
};

#endif /* _CON_MAP_ */