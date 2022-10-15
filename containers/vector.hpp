#ifndef _VECTOR_H_
# define _VECTOR_H_

# include <iostream>
# include <memory>

namespace ft
{

template<typename T, typename Allocator = std::allocator<T> >
class vector
{
	private:
		T*					_arr;
		Allocator			_alloc;
		size_t				_size;
		size_t				_capacity;
	
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
		vector(): _alloc(Allocator()), _arr(0), _size(0), _capacity(0) {}

		explicit vector( const Allocator& alloc ): _alloc(alloc), _arr(0), _size(0), _capacity(0) {}

		explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _arr(0), _size(0), _capacity(0), _alloc(alloc)
		{
			if (_alloc.max_size() < count)
				throw (std::length_error("vector"));
			assign(count, value);
		}

		template< class InputIt, class = typename std::enable_if<!std::is_integral<InputIt>::value, InputIt>::type >
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ): _arr(0), _alloc(alloc), _size(0), _capacity(0)
		{
			size_t count = 0;

			for (InputIt it = first; it != last; it++)
				count++;
			if (_alloc.max_size() < count)
				throw (std::length_error("vector"));
			assign(first, last);
		}

		vector( const vector& other ): _alloc(other.get_allocator()), _size(other._size), _capacity(other._capacity)
		{
			if (!_capacity){
				_arr = 0;
				return ;
			}
			_arr = _alloc.allocate(_capacity);
			for (size_t i = 0; i < _size; i++)
				_arr[i] = other._arr[i];
		}
		
		~vector() { _alloc.deallocate(_arr, _capacity); };

		/* Copy assignment */
		vector& operator=( const vector& other )
		{
			if (this == &other)
				return (*this);
			if (empty())
				_alloc.deallocate(_arr, _capacity);
			_capacity = other._capacity;
			_size = other._size;
			_alloc = other._alloc;
			if (!_capacity){
				_arr = 0;
				return (*this);
			}
			_arr = _alloc.allocate(_capacity);
			for (size_t i = 0; i < _size; i++)
				_arr[i] = other._arr[i];
			return (*this);
		}

		/* Assign member functions */
		void assign( size_type count, const T& value )
		{
			if (_alloc.max_size() < count)
				throw (std::length_error("vector"));
			if (_capacity < count)
			{
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(count);
				_size = _capacity = count;
			}
			else
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_arr[i]);
				_size = count;
			}
			for (size_t i = 0; i < count; i++)
				_arr[i] = value;

			std::cout << "ft: ";
			for (size_t i = 0; i < size(); i++)
				std::cout << _arr[i] << ' ';
			std::cout << std::endl;
		}
		
		template< class InputIt, class = typename std::enable_if<!std::is_integral<InputIt>::value, InputIt>::type>
		void assign( InputIt first, InputIt last )
		{
			size_t count = 0;

			for (InputIt it = first; it != last; it++)
				count++;

			if (_alloc.max_size() < count)
				throw (std::length_error("vector"));
			if (_capacity < count)
			{
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(count);
				_size = _capacity = count;
			}
			else
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_arr[i]);
				_size = count;
			}
			for (size_t i = 0; i < count; i++)
				_arr[i] = *(first + i);

			std::cout << "ft: ";
			for (size_t i = 0; i < size(); i++)
				std::cout << _arr[i] << ' ';
			std::cout << std::endl;
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
		// iterator begin();
		// iterator end();

		// const_iterator begin() const;
		// const_iterator end() const;

		// reverse_iterator rbegin();
		// reverse_iterator rend();

		// const_reverse_iterator rbegin() const;
		// const_reverse_iterator rend() const;

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
				tmp[i] = _arr[i];
			if (_arr)
				_alloc.deallocate(_arr, _capacity);
			_arr = tmp;
			_capacity = new_cap;
		}

		size_type capacity() const { return (_capacity); }

		/* Modifiers */
		void clear();

		// iterator insert( const_iterator pos, const T& value );
		// iterator insert( const_iterator pos, size_type count, const T& value );
		// template< class InputIt >
		// iterator insert( const_iterator pos, InputIt first, InputIt last );

		// iterator erase( iterator pos );
		// iterator erase( iterator first, iterator last );

		void push_back( const T& value );
		void pop_back();

		void resize( size_type count, T value = T() );

		void swap( vector& other );

		/* Non-member functions */
		// template< class T, class Alloc >
		// friend bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		// template< class T, class Alloc >
		// friend bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		// template< class T, class Alloc >
		// friend bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		// template< class T, class Alloc >
		// friend bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		// template< class T, class Alloc >
		// friend bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
		// template< class T, class Alloc >
		// friend bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );

		// template< class T, class Alloc >
		// friend void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs );
};

};

#endif /* _VECTOR_H_ */