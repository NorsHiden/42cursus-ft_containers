#ifndef _VECTOR_H_
# define __VECTOR_H_

# include <iostream>
# include <memory>

namespace ft
{

template<typename T, Allocator = std::allocator<T> >
class vector
{
	private:
		T*			_arr;
		Allocator&	_alloc;
		size_t		_size;
		size_t		_capacity;
	
	public:
		typedef T									value_type;
		typedef Allocator							allocator_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		/* Constructors & Destructor */
		vector() _alloc(Allocator()): _arr(0), _size(0), _capacity(0) {}

		explicit vector( const Allocator& alloc );

		vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _alloc(alloc)
		{
			_arr = _alloc.allocate(count);
			for (size_t i = 0; i < count; i++)
				_arr[i] = value;
			_size = _capacity = count;
		}

		template< class InputIt >
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()): _alloc(alloc)
		{
			size_t len = 0;

			for (InputIt temp = first; temp != last; temp++)
				len++;
			_arr = _alloc.allocate(len);
			_size = len;
			_capacity = len;
			for (len = 0, InputIt temp = first; temp != last; temp++, len++)
				_arr[len] = *temp;
		}

		vector( const vector& other );
		~vector();

		/* Copy assignment */
		vector& operator=( const vector& other );

		/* Assign member functions */
		void assign( size_type count, const T& value );
		template< class InputIt >
		void assign( InputIt first, InputIt last );

		/* get_allocator member functions */
		allocator_type get_allocator() const;

		/* Element access */
		reference at( size_type pos );
		const_reference at( size_type pos ) const;

		reference operator[]( size_type pos );
		const_reference operator[]( size_type pos ) const;

		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		T* data();
		const T* data() const;

		/* Iterators */
		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

		reverse_iterator rbegin();
		reverse_iterator rend();

		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;

		/* Capacity */
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void reserve( size_type new_cap );
		size_type capacity() const;

		/* Modifiers */
		void clear();

		iterator insert( const_iterator pos, const T& value );
		iterator insert( const_iterator pos, size_type count, const T& value );
		template< class InputIt >
		iterator insert( const_iterator pos, InputIt first, InputIt last );

		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );

		void push_back( const T& value );
		void pop_back();

		void resize( size_type count, T value = T() );

		void swap( vector& other );

		/* Non-member functions */
		template< class T, class Alloc >
		bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		template< class T, class Alloc >
		bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		template< class T, class Alloc >
		bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		template< class T, class Alloc >
		bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		template< class T, class Alloc >
		bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		template< class T, class Alloc >
		bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );

		template< class T, class Alloc >
		void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs );
};

};

#endif /* _VECTOR_H_ */