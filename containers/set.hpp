/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:40:41 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/23 14:01:21 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SET_HPP_
# define _SET_HPP_

# include <iostream>
# include "../utils/pair.hpp"
# include "../utils/lexicographical_compare.hpp"
# include "../utils/RedBlackTree.hpp"
# include "../utils/bidirectional_iterator.hpp"
# include "../utils/reverse_iterator.hpp"

namespace ft
{
	template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
	> class set
	{
		private:
			class Node
			{
				public:
					typedef	Key	value_type;
					
					value_type	*content;
					Node		*parent;
					Node		*left;
					Node		*right;
					bool		right_null;
					bool		color;

					Node(): content(0), parent(0), left(0), right(0), color(RED) {}
					Node(const Node& x): content(x.content), parent(x.parent), left(x.left), right(x.right), color(x.color) {}

					bool	lhs_compare(const value_type value, const Compare &comp)
					{
						return (comp(*content, value));
					}
					
					bool	rhs_compare(const value_type& value, const Compare &comp)
					{
						return (comp(value, *content));
					}
			};
		public:
			typedef Key																			key_type;
			typedef Key																			value_type;
			typedef std::size_t																	size_type;
			typedef std::ptrdiff_t																difference_type;
			typedef Compare																		key_compare;
			typedef	Compare																		value_compare;
			typedef	Allocator																	allocator_type;
			typedef	value_type&																	reference;
			typedef	const value_type&															const_reference;
			typedef typename Allocator::pointer													pointer;
			typedef typename Allocator::const_pointer											const_pointer;
			typedef ft::BidirectionalIterator<Node, const value_type>							iterator;
			typedef ft::BidirectionalIterator<Node, const value_type>							const_iterator;
			typedef ft::reverse_iterator< ft::BidirectionalIterator<Node, const value_type> >	reverse_iterator;
			typedef ft::reverse_iterator< ft::BidirectionalIterator<Node, const value_type> >	const_reverse_iterator;
			
		private:
			RedBlackTree<Node, allocator_type, key_compare>			rbt;
			size_type												_size;
			allocator_type											alloc;
			key_compare												comp;
		
		public:
			/* Constructors && Destructor */
			set( const Compare& comp = Compare(), const Allocator& alloc = Allocator() ): rbt(), _size(), alloc(alloc), comp(comp)	{}

			template< class InputIt >
			set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
			: rbt(), _size(), alloc(alloc), comp(comp) { insert(first, last); }
			
			set( const set& other ): rbt(other.rbt), _size(other._size), alloc(other.alloc), comp(other.comp) {}

			set& operator=( const set& other )
			{
				if (this == &other)
					return (*this);
				rbt = other.rbt;
				_size = other._size;
				return (*this);
			}

			~set() {}

			allocator_type get_allocator() const { return (allocator_type()); }

			/* Iterators */
			iterator begin () { return (iterator(rbt.begin(), rbt.base())); }

			const_iterator begin () const { return (const_iterator(rbt.begin(), rbt.base())); }
				
			iterator end () { return (iterator(rbt.end(), rbt.base())); }
				
			const_iterator end () const { return (const_iterator(rbt.end(), rbt.base())); }

			reverse_iterator rbegin () { return (reverse_iterator(iterator(rbt.end(), rbt.base()))); }
				
			const_reverse_iterator rbegin () const { return (const_reverse_iterator(const_iterator(rbt.end(), rbt.base()))); }

			reverse_iterator rend () { return (reverse_iterator(iterator(rbt.begin(), rbt.base()))); }
				
			const_reverse_iterator rend () const { return (const_reverse_iterator(const_iterator(rbt.begin(), rbt.base()))); }

			/* Capacity */
			bool empty () const { return (!_size); }

			size_type size () const { return (_size); }
				
			size_type max_size () const { return (alloc.max_size()); }

			/* Modifiers */
			void clear()
			{
				rbt.clear();
				_size = 0;
			}
			ft::pair<iterator,bool> insert (const value_type& value)
			{
				Node	*node = rbt.search(value);
				if (node)
					return (pair<iterator, bool>(iterator(node, rbt.base()), false));
				_size++;
				return (pair<iterator, bool>(iterator(rbt.insert(value), rbt.base()), true));
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (insert(val).first);
			}

			template <class InputIterator> 
			void insert (InputIterator first, InputIterator last)
			{
				for (InputIterator it = first; it != last; ++it)
					insert(*it);
			}

			void erase (iterator position) { erase(*position); }

			void erase( iterator first, iterator last )
			{
				iterator it = first;
				while (it != last)
				{
					iterator tmp = it++;
					erase(*tmp);
				}
			}

			size_type erase( const key_type& key )
			{
				size_type count = rbt.erase(key);
				if (count)
					_size--;
				return (count);
			}

			void swap( set& other )
			{
				rbt.swap(other.rbt);	
				size_type s = other._size;
				other._size = _size;
				_size = s;				
			}

			/* Lookup */
			size_type count( const Key& key ) const
			{
				Node	*cont = rbt.search(key);
				if (!cont)
					return (false);
				return (true);
			}

			iterator find( const Key& key )
			{
				Node	*cont = rbt.search(key);
				if (!cont)
					return (end());
				return (iterator(cont, rbt.base()));
			}

			const_iterator find( const Key& key ) const
			{
				Node	*cont = rbt.search(key);
				if (!cont)
					return (end());
				return (iterator(cont, rbt.base()));
			}

			iterator lower_bound (const key_type& k) { return (iterator(rbt.lower_bound(k), rbt.base())); }
				
			const_iterator lower_bound (const key_type& k) const { return (const_iterator(rbt.lower_bound(k), rbt.base())); }

			iterator upper_bound (const key_type& k) { return (iterator(rbt.upper_bound(k), rbt.base()));}
			
			const_iterator upper_bound (const key_type& k) const { return (const_iterator(rbt.upper_bound(k), rbt.base()));}

			ft::pair<iterator,iterator>	equal_range (const key_type& k) { return (ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k))); }
			
			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return (ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k))); }

			/* Observers */
			key_compare key_comp() const { return (comp); }

			value_compare value_comp() const { return (comp); }

	};

	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (lhs < rhs || lhs == rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (lhs > rhs || lhs == rhs);
	}

	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
};

#endif /* _SET_HPP_ */