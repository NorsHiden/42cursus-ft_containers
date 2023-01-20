/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:52:11 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/20 12:42:32 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RANDOMACCESSITERATORS_H_
# define _RANDOMACCESSITERATORS_H_

# include <iostream>
# include "iterator_traits.hpp"

namespace ft
{
	template<class T, class Value>
	class BidirectionalIterator
	{
		public:
			typedef typename std::bidirectional_iterator_tag		iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;
			typedef	const pointer									const_pointer;
			typedef const reference									const_reference;
			typedef Value											content_value;
			
		private:
			pointer		_p;
			pointer		_root;
			
		public:
			/* Constructors && Destructor */
			BidirectionalIterator(): _p(0), _root(0)														{}
			BidirectionalIterator(const_pointer p, const_pointer root): _p(p), _root(root)					{}
			template<class U, class V>
			BidirectionalIterator(const BidirectionalIterator<U, V>& other): _p(other.base()), _root(other.root_base())		{}  // TODO: root need to be added
			~BidirectionalIterator()																		{}
			
			/* Copy assignment operator */
			template<class U, class V>
			BidirectionalIterator& operator=(const BidirectionalIterator<U, V>& other)
			{
				_p = other.base();
				_root = other.root_base();
				return (*this);
			}

			/* Comparison operators */
			template<class U, class V>
			bool	operator==(const BidirectionalIterator<U, V>& other) const	{ return (_p == other.base()); }
			template<class U, class V>
			bool	operator!=(const BidirectionalIterator<U, V>& other) const	{ return (_p != other.base()); }

			/* Dereference operators */
			content_value&			operator*()			{ return (*_p->content); }
			const content_value&	operator*() const	{ return (*_p->content); }
			
			content_value*			operator->()		{return (_p->content);}
			const content_value*	operator->() const	{return (_p->content);}

			/* Arithmetic operators */
			BidirectionalIterator&	operator++()
			{
				if (!_p)
				{
					_p = _root;
					while (_p->left)
						_p = _p->left;
				}
				else if (_p->right)
				{
					_p = _p->right;
					while (_p->left)
						_p = _p->left;
				}
				else if (_p->parent && _p->parent->left == _p)
					_p = _p->parent;
				else if (_p->parent && _p->parent->right == _p)
				{
					_p = _p->parent;
					while (_p->parent && _p->parent->right == _p)
						_p = _p->parent;
					if (!_p->parent)
						_p = nullptr;
					else
						_p = _p->parent;
				}
				else
					_p = nullptr;
				return (*this);
			}
			
			BidirectionalIterator	operator++(int)
			{
				BidirectionalIterator it(_p, _root);
				if (!_p)
				{
					_p = _root;
					while (_p->left)
						_p = _p->left;
				}
				else if (_p->right)
				{
					_p = _p->right;
					while (_p->left)
						_p = _p->left;
				}
				else if (_p->parent && _p->parent->left == _p)
					_p = _p->parent;
				else if (_p->parent && _p->parent->right == _p)
				{
					_p = _p->parent;
					while (_p->parent && _p->parent->right == _p)
						_p = _p->parent;
					if (!_p->parent)
						_p = nullptr;
					else
						_p = _p->parent;
				}
				else
					_p = nullptr;
				return (it);
			}

			BidirectionalIterator&	operator--()
			{
				if (!_p)
				{
					_p = _root;
					while (_p->right)
						_p = _p->right;
				}
				else if (_p->left)
				{
					_p = _p->left;
					while (_p->right)
						_p = _p->right;
				}
				else if (_p->parent && _p->parent->right == _p)
					_p = _p->parent;
				else if (_p->parent && _p->parent->left == _p)
				{
					_p = _p->parent;
					while (_p->parent && _p->parent->left == _p)
						_p = _p->parent;
					if (!_p->parent)
						_p = nullptr;
					else
						_p = _p->parent;
				}
				else
					_p = nullptr;
				return (*this);
			}
			
			BidirectionalIterator	operator--(int)
			{
				BidirectionalIterator it(_p);
					if (!_p)
				{
					_p = _root;
					while (_p->right)
						_p = _p->right;
				}
				else if (_p->left)
				{
					_p = _p->left;
					while (_p->right)
						_p = _p->right;
				}
				else if (_p->parent && _p->parent->right == _p)
					_p = _p->parent;
				else if (_p->parent && _p->parent->left == _p)
				{
					_p = _p->parent;
					while (_p->parent && _p->parent->left == _p)
						_p = _p->parent;
					if (!_p->parent)
						_p = nullptr;
					else
						_p = _p->parent;
				}
				else
					_p = nullptr;
				return (it);
			}

			/* Member function */
			pointer	base() const { return (_p); }
			pointer	root_base() const { return (_root); }
			// pointer const base() const { return (_p); }
	};
	
};

#endif /* _RANDOMACCESSITERATORS_H_ */