/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:52:11 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/22 14:35:34 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BIDIRECTIONAL_ITERATOR_H_
# define _BIDIRECTIONAL_ITERATOR_H_

# include <iostream>
# include "iterator_traits.hpp"

namespace ft
{
	template<class Node, class Value>
	class BidirectionalIterator
	{
		public:
			typedef typename std::bidirectional_iterator_tag			iterator_category;
			typedef typename iterator_traits<Value*>::value_type		value_type;
			typedef typename iterator_traits<Value*>::difference_type	difference_type;
			typedef typename iterator_traits<Value*>::pointer			pointer;
			typedef typename iterator_traits<Value*>::reference			reference;
			typedef	const pointer										const_pointer;
			typedef const reference										const_reference;
			
		private:
			Node*	_p;
			Node*	_root;

			void	successor()
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
			}

			void	predecessor()
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
			}
			
		public:
			/* Constructors && Destructor */
			BidirectionalIterator(): _p(0), _root(0)								{}
			BidirectionalIterator(Node* p, Node* root): _p(p), _root(root)			{}
			BidirectionalIterator(const BidirectionalIterator<Node, Value>& other)
				: _p(other._p), _root(other._root)									{}
			~BidirectionalIterator()												{}
			
			/* Copy assignment operator */
			BidirectionalIterator& operator=(const BidirectionalIterator<Node, Value>& other)
			{
				_p = other._p;
				_root = other._root;
				return (*this);
			}

			operator	BidirectionalIterator<Node, const Value>()
			{
				return (BidirectionalIterator<Node, const Value>(_p, _root));
			}

			/* Comparison operators */
			template<class U, class V>
			bool	operator==(const BidirectionalIterator<U, V>& other) const	{ return (_p == other.base()); }
			template<class U, class V>
			bool	operator!=(const BidirectionalIterator<U, V>& other) const	{ return (_p != other.base()); }

			/* Dereference operators */
			reference			operator*()			{ return (*_p->content); }
			const_reference		operator*() const	{ return (*_p->content); }
			
			pointer				operator->()		{return (_p->content);}
			const_pointer				operator->() const	{return (_p->content);}

			/* Arithmetic operators */
			BidirectionalIterator&	operator++() { successor(); return (*this); }
			
			BidirectionalIterator	operator++(int)
			{
				BidirectionalIterator it(_p, _root);
				successor();
				return (it);
			}

			BidirectionalIterator&	operator--() { predecessor(); return (*this); }
			
			BidirectionalIterator	operator--(int)
			{
				BidirectionalIterator it(_p, _root);
				predecessor();
				return (it);
			}

			/* Member function */
			Node*	base() const { return (_p); }
	};
	
};

#endif /* _BIDIRECTIONAL_ITERATOR_H_ */