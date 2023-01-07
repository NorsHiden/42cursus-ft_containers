/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 12:06:27 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/07 12:06:29 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECTOR_H_
# define _VECTOR_H_

# include <iostream>
# include "equal.hpp"
# include "random_access_iterator.hpp"
# include "type_traits.hpp"
# include "reverse_iterator.hpp"
# include "lexicographical_compare.hpp"

# define ENABLE_IF typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
		private:
			T*					_arr;
			Allocator			_alloc;
			size_t				_size;
			size_t				_capacity;
		
		public:
			typedef T																	value_type;
			typedef Allocator															allocator_type;
			typedef std::size_t															size_type;
			typedef std::ptrdiff_t														difference_type;
			typedef value_type&															reference;
			typedef const value_type&													const_reference;
			typedef typename Allocator::pointer											pointer;
			typedef typename Allocator::const_pointer									const_pointer;
			typedef ft::RandomAccessIterator<T*>										iterator;
			typedef ft::RandomAccessIterator<const T*>									const_iterator;
			typedef ft::reverse_iterator< ft::RandomAccessIterator<T*> >				reverse_iterator;
			typedef ft::reverse_iterator< ft::RandomAccessIterator<const T*> >			const_reverse_iterator;

			/* Constructors && Destructor */
			vector(): _arr(0), _alloc(Allocator()), _size(0), _capacity(0) {}

			explicit vector( const Allocator& alloc ): _arr(0), _alloc(alloc), _size(0), _capacity(0) {}

			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()):
				_arr(0), _alloc(alloc), _size(0), _capacity(0) { assign(count, value); }

			template<class InputIt>
			vector(InputIt first, ENABLE_IF last, const Allocator& alloc = Allocator()): 
				_arr(0), _alloc(alloc), _size(0), _capacity(0) { assign(first, last); }

			vector( const vector& other ):
				_alloc(other.get_allocator()), _size(other._size), _capacity(other._capacity)
			{
				if (!_capacity){
					_arr = 0;
					return ;
				}
				_arr = _alloc.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&_arr[i], other._arr[i]);
			}
			
			~vector()
			{
				for (size_t i = _size; i > 0; i--)
					_alloc.destroy(&_arr[i - 1]);
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);

			}

			/* Copy assignment operator */
			vector& operator=( const vector& other )
			{
				if (this == &other)
					return (*this);
				assign(other.begin(), other.end());
				return (*this);
			}

			/* Assign member functions */
			void assign( size_type count, const T& value )
			{
				if (_alloc.max_size() < count)
					throw (std::length_error("vector"));
				clear();
				for (size_type i = 0; i < count; i++)
					push_back(value);
			}
			
			template< class InputIt>
			void assign(InputIt first, ENABLE_IF last)
			{
				clear();
				for (InputIt it = first; it != last; ++it)
					push_back(*it);
			}

			/* get_allocator member functions */
			allocator_type get_allocator() const { return (_alloc); }

			/* Element access */
			reference at( size_type pos )
			{
				if (pos >= _size || pos < 0)
					throw (std::out_of_range("vector"));
				return (_arr[pos]);
			}

			const_reference at( size_type pos ) const
			{
				if (pos >= _size || pos < 0)
					throw (std::out_of_range("vector"));
				return (_arr[pos]);
			}

			reference operator[]( size_type pos ) { return (_arr[pos]); }

			const_reference operator[]( size_type pos ) const { return (_arr[pos]); }

			reference front() { return (_arr[0]); }
			const_reference front() const { return (_arr[0]); }

			reference back() { return (_arr[_size - 1]); }
			const_reference back() const { return (_arr[_size - 1]); }

			pointer data() { return (_arr); }
			const_pointer data() const { return (_arr); }

			/* Iterators */
			iterator begin() { return (_arr); }
			iterator end() { return (_arr + _size); }

			const_iterator begin() const { return (_arr); }
			const_iterator end() const { return (_arr + _size); }

			reverse_iterator rbegin() { return ( reverse_iterator( end() ) ); }
			reverse_iterator rend() { return ( reverse_iterator( begin() )  ); }

			const_reverse_iterator rbegin() const { return ( const_reverse_iterator( end() ) ); }
			const_reverse_iterator rend() const { return ( const_reverse_iterator( begin() )  ); }

			/* Capacity */
			bool empty() const { return (!_size); }

			size_type size() const { return (_size); }

			size_type max_size() const { return (_alloc.max_size()); }

			void reserve( size_type new_cap )
			{
				if (_capacity >= new_cap)
					return ;
				T* tmp = _alloc.allocate(new_cap);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&tmp[i], _arr[i]);
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_arr[i]);
				if (_arr)
					_alloc.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = new_cap;
			}

			size_type capacity() const { return (_capacity); }

			/* Modifiers */
			void clear()
			{
				if (!_size)
					return ;
				for (size_t i = _size; i > 0; i--)
						_alloc.destroy(&_arr[i - 1]);
				_size = 0;
			}

			iterator insert( const_iterator pos, const T& value ) { return (insert(pos, 1, value)); }

			iterator insert( const_iterator pos, size_type count, const T& value )
			{
				size_t pos_loc = pos - begin();

				if (!count) return (begin() + pos_loc);

				if (!_capacity)
					reserve(count);
				else if (_size + count > _capacity * 2)
					reserve(_size + count);
				else if (_size + count > _capacity)
					reserve(_capacity * 2);
				size_t i;
				for (i = _size; i > pos_loc; i--)
				{
					_alloc.construct(&_arr[i + count - 1], _arr[i - 1]);
					_alloc.destroy(&_arr[i - 1]);
				}
				size_t new_pos = pos_loc;
				for (size_t j = count; j > 0; j--)
					_alloc.construct(&_arr[pos_loc++], value);
				_size += count;
				return (&_arr[new_pos]);
			}

			template< class InputIt >
			void insert( const_iterator pos, InputIt first, ENABLE_IF last )
			{
				pointer tmp = _arr;
				size_type tmp_size = _size;
				size_type tmp_capacity = _capacity;

				if (first == last) return ;

				iterator itbeg = begin();
				iterator itend = end();
				iterator itcur;
				_arr = 0;
				_size = 0;
				_capacity = 0;
				reserve(tmp_capacity);
				for (itcur = itbeg; itcur != itend && itcur != pos; itcur++)
					push_back(*itcur);
				for (InputIt it = first; it != last; it++)
					push_back(*it);
				for (; itcur != itend; itcur++)
					push_back(*itcur);
				for (size_t i = tmp_size; i > 0; i--)
					_alloc.destroy(&tmp[i - 1]);
				if (tmp)
					_alloc.deallocate(tmp, tmp_capacity);
			}

			iterator erase( iterator pos ) { return (erase(pos, pos + 1)); }

			iterator erase( iterator first, iterator last )
			{
				if (first == last) return (first);

				size_t i = 0;
				for (i = 0; last + i < end(); i++)
					*(first + i) = *(last + i);
				while (first + i != end())
					_alloc.destroy(&*(first + i++));
				_size -= last - first;
				return (first);
			}

			void push_back( const T& value )
			{
				pointer tmp;

				if (!_capacity)
					tmp = _alloc.allocate(1);
				else if (_size == _capacity)
					tmp = _alloc.allocate(_capacity * 2);
				else
					tmp = _arr;
				for (size_t i = 0; _capacity && _size == _capacity && i < _size; i++)
					_alloc.construct(&tmp[i], _arr[i]);
				_alloc.construct(&tmp[_size], value);
				for (size_t i = _size; _capacity && _size == _capacity && i > 0; i--)
					_alloc.destroy(&_arr[i - 1]);
				if (_capacity && _size == _capacity)
				{
					_alloc.deallocate(_arr, _capacity);
					_capacity *= 2;
				}
				else if (!_capacity)
					_capacity++;
				_size++;
				_arr = tmp;
			}

			void pop_back()
			{
				_alloc.destroy(&_arr[_size - 1]);
				_size--;
			}

			void resize( size_type count, const T& value = T() )
			{
				if (count == _size) return ;

				if (!count) { clear(); return ; }

				if (count > _capacity || count > _size)
				{
					reserve(count);
					for (size_t i = _size ; i < count; i++)
						_alloc.construct(&_arr[i], value);
				}
				else if (count < _size)
				{
					for (size_t i = _size; i > count; i--)
						_alloc.destroy(&_arr[i - 1]);
				}
				_size = count;
			}

			void swap( vector& other )
			{
				std::swap(_arr, other._arr);
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_alloc, other._alloc);
			}
	};

	/* Non-member functions */
	template< class T, class Alloc >
	bool operator==( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator<( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs )
	{
		if (lhs.size() > rhs.size())
			return (false);
		if (lhs.size() < rhs.size())
			return (true);
		if (!lhs.size() && rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs )
	{
		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) || ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		return (false);
	}

	template< class T, class Alloc >
	bool operator>( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs )
	{
		if (lhs.size() < rhs.size())
			return (false);
		if (lhs.size() > rhs.size())
			return (true);
		if (!rhs.size() && lhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs )
	{
		if (lhs.size() > rhs.size())
			return (true);
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) || !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		return (false);
	}

	template< class T, class Alloc >
	void swap( ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs ) { lhs.swap(rhs); }
};

#endif /* _VECTOR_H_ */