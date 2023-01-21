/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:06:15 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/21 16:31:31 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CON_MAP_
# define _CON_MAP_

# include <iostream>
# include <functional>
# include "../utils/pair.hpp"
# include "../utils/equal.hpp"
# include "../utils/lexicographical_compare.hpp"
# include "../utils/RedBlackTree.hpp"
# include "../utils/bidirectional_iterator.hpp"
# include "../utils/reverse_iterator.hpp"

namespace ft
{
	template<
    	class Key,
    	class T,
		class Compare = std::less<Key>,
    	class Allocator = std::allocator<ft::pair<const Key, T> >
	> class map
	{
		private:
			class Node
			{
				public:
					typedef	ft::pair<const Key, T>	value_type;
					
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
						return (comp(content->first, value.first));
					}
					
					bool	rhs_compare(const value_type& value, const Compare &comp)
					{
						return (comp(value.first, content->first));
					}
			};
			
		public:
			typedef	Key																			key_type;
			typedef	T																			mapped_type;
			typedef	ft::pair<const key_type, mapped_type>										value_type;
			typedef	std::size_t																	size_type;
			typedef	std::ptrdiff_t																difference_type;
			typedef	Compare																		key_compare;
			typedef	Allocator																	allocator_type;
			typedef	typename allocator_type::reference											reference;
			typedef	typename allocator_type::const_reference									const_reference;
			typedef	typename allocator_type::pointer											pointer;
			typedef	typename allocator_type::const_pointer										const_pointer;
			typedef ft::BidirectionalIterator<Node, value_type>									iterator;
			typedef ft::BidirectionalIterator<Node, const value_type>							const_iterator;
			typedef ft::reverse_iterator< ft::BidirectionalIterator<Node, value_type> >			reverse_iterator;
			typedef ft::reverse_iterator< ft::BidirectionalIterator<Node, const value_type> >	const_reverse_iterator;
			
		private:
			RedBlackTree<Node, allocator_type, key_compare>			rbt;
			size_type												_size;
			allocator_type											alloc;
			key_compare												comp;
		
		public:
			/* Function object */
			class value_compare
			{
				public:
					typedef typename std::binary_function<value_type, value_type, bool>::result_type				result_type;
					typedef typename std::binary_function<value_type, value_type, bool>::first_argument_type		first_argument_type;
					typedef typename std::binary_function<value_type, value_type, bool>::second_argument_type	second_argument_type;
				protected:
					key_compare comp;
				
				public:
					value_compare() {}
					result_type	operator()(const value_type& lhs, const value_type& rhs) const
					{
						return (comp(lhs.first, rhs.first));
					}
					~value_compare() {}
			};
			
			/* Constructors & Destructor */
			map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: rbt(), _size(0), alloc(alloc), comp(comp) {}
			
			template<class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: rbt(), _size(0), alloc(alloc), comp(comp)
			{
				for (InputIterator it = first; it != last; ++it)
				{
					rbt.insert(*it);
					_size++;
				}
				// rbt.printTree();
			}

			map (const map& x): rbt(x.rbt), _size(x._size), alloc(x.alloc), comp(x.comp) {}

			map& operator=(const map& x)
			{
				if (this == &x)
					return (*this);
				rbt = x.rbt;
				_size = x._size;
				return (*this);
			}

			~map () {}

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

			/* Element access */
			mapped_type& operator[] (const key_type& k)
			{
				Node	*node = rbt.search(value_type(k, mapped_type()));
				if (!node)
				{
					node = rbt.insert(value_type(k, mapped_type()));
					_size++;
				}
				return (node->content->second);
			}
			
			mapped_type& at (const key_type& k)
			{
				Node	*cont = rbt.search(value_type(k, mapped_type()));
				if (!cont)
					throw (std::out_of_range("map::at: key not found"));
				return (cont->content->second);
			}
			
			const mapped_type& at (const key_type& k) const
			{
				const Node	*cont = rbt.search(value_type(k, mapped_type()));
				if (!cont)
					throw (std::out_of_range("map::at: key not found"));
				return (cont->content->second);
			}

			/* Modifiers */
			pair<iterator,bool> insert (const value_type& val)
			{
				Node	*node = rbt.search(val);
				if (node)
					return (pair<iterator, bool>(iterator(node, rbt.base()), false));
				value_type*	cont = new value_type(val);
				_size++;
				return (pair<iterator, bool>(iterator(rbt.insert(*cont), rbt.base()), true));
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
			
			void erase (iterator position) { erase(position->first); }
			
			size_type erase (const key_type& k)
			{
				size_type count = rbt.erase(value_type(k, mapped_type()));
				if (count)
					_size--;
				return (count);
			}
			
			void erase (iterator first, iterator last)
			{
				iterator it = first;
				while (it != last)
				{
					iterator tmp = it++;
					erase(tmp->first);
				}
			}
			
			void swap (map& x)
			{	
				rbt.swap(x.rbt);	
				size_type s = x._size;
				x._size = _size;
				_size = s;				
			}

			void clear()
			{
				rbt.clear();
				_size = 0;
			}

			/* Lookup */
			iterator find (const key_type& k)
			{
				Node	*cont = rbt.search(value_type(k, mapped_type()));
				if (!cont)
					return (end());
				return (iterator(cont, rbt.base()));
			}
			
			const_iterator find (const key_type& k) const
			{
				Node	*cont = rbt.search(value_type(k, mapped_type()));
				if (!cont)
					return (end());
				return (iterator(cont, rbt.base()));
			}
			
			size_type count (const key_type& k) const
			{
				Node	*cont = rbt.search(value_type(k, mapped_type()));
				if (!cont)
					return (false);
				return (true);
			}

			iterator lower_bound (const key_type& k) { return (iterator(rbt.lower_bound(value_type(k, mapped_type())), rbt.base())); }
			
			const_iterator lower_bound (const key_type& k) const { return (const_iterator(rbt.lower_bound(value_type(k, mapped_type())), rbt.base())); }

			iterator upper_bound (const key_type& k) { return (iterator(rbt.upper_bound(value_type(k, mapped_type())), rbt.base()));}
			
			const_iterator upper_bound (const key_type& k) const { return (const_iterator(rbt.upper_bound(value_type(k, mapped_type())), rbt.base()));}

			pair<iterator,iterator>	equal_range (const key_type& k) { return (pair<iterator,iterator>(lower_bound(k), upper_bound(k))); }
			
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return (pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k))); }		

			/* Allocator */
			allocator_type get_allocator() const { return (allocator_type()); }
			/* Observers */
			key_compare key_comp() const { return (comp); }
			value_compare value_comp() const { return (value_compare()); }
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() > rhs.size())
			return (false);
		if (lhs.size() < rhs.size())
			return (true);
		if (!lhs.size() && rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) || ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		return (false);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() < rhs.size())
			return (false);
		if (lhs.size() > rhs.size())
			return (true);
		if (!rhs.size() && lhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() > rhs.size())
			return (true);
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) || !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		return (false);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
};

#endif /* _CON_MAP_ */ 