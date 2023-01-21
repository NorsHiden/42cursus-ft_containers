/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:47:50 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/21 16:34:18 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _REDBLACKTREE_
# define _REDBLACKTREE_

# include <iostream>

# define RED true
# define BLACK false

template<class T, class Allocator = std::allocator<typename T::value_type>, class Compare = std::less<typename T::value_type> >
class RedBlackTree
{
	public:
		typedef	T							Node;
		typedef Allocator					allocator_type;
		typedef Compare						compare_type;
		typedef typename Node::value_type	value_type;

	private:
		Node													*root;
		allocator_type											alloc;
		typename allocator_type::template rebind<Node>::other 	alloc_node;
		compare_type											comp;

		void	insertNewNode(Node* node, const Node* ext_node)
		{
			node->color = ext_node->color;
			node->content = alloc.allocate(1);
			alloc.construct(node->content, *ext_node->content);
			if (ext_node->left)
			{
				node->left = alloc_node.allocate(1);
				alloc_node.construct(node->left, Node());
				insertNewNode(node->left, ext_node->left);
				node->left->parent = node;
			}
			if (ext_node->right)
			{
				node->right = alloc_node.allocate(1);
				alloc_node.construct(node->right, Node());
				insertNewNode(node->right, ext_node->right);
				node->right->parent = node;
			}
		}

		void	deleteNode(Node *node)
		{
			if (!node) return ;
			
			deleteNode(node->left);
			deleteNode(node->right);
			alloc.destroy(node->content);
			alloc.deallocate(node->content, 1);
			alloc_node.destroy(node);
			alloc_node.deallocate(node, 1);
		}

		void	insertionColorFlip(Node *node)
		{
			node->color = RED;
			if (node->right)
				node->right->color = BLACK;
			if (node->left)
				node->left->color = BLACK;
		}

		void	rotateRight(Node *node)
		{
			if (!node->left) return ;

			Node	*node_parent = node->parent;
			Node	*node_left = node->left;

			if (!node->parent)
				root = node_left;
			node->parent = node_left;
			node->left = node_left->right;
			if (node_left->right)
				node_left->right->parent = node;
			node_left->parent = node_parent;
			node_left->right = node;
			if (node_parent && node_parent->right == node)
				node_parent->right = node_left;
			else if (node_parent)
				node_parent->left = node_left;
		}

		void	rotateLeft(Node *node)
		{
			if (!node->right) return ;

			Node	*node_parent = node->parent;
			Node	*node_right = node->right;

			if (!node->parent)
				root = node_right;
			node->parent = node_right;
			node->right = node_right->left;
			if (node_right->left)
				node_right->left->parent = node;
			node_right->parent = node_parent;
			node_right->left = node;
			if (node_parent && node_parent->right == node)
				node_parent->right = node_right;
			else if (node_parent)
				node_parent->left = node_right;
		}

		void	checkInsertionViolations(Node *node)
		{
			if (!node->parent)
				node->color = BLACK;
			else if (node->color == RED && node->parent->color == RED)
			{
				if ((node->parent->parent->left == node->parent
					&& node->parent->parent->right && node->parent->parent->right->color == RED)
					|| (node->parent->parent->right == node->parent
					&& node->parent->parent->left && node->parent->parent->left->color == RED))
				{
					insertionColorFlip(node->parent->parent);
					checkInsertionViolations(node->parent->parent);
				}
				else if (node->parent->parent->left == node->parent && node->parent->right == node)
				{
					rotateLeft(node->parent);
					checkInsertionViolations(node->left);
				}
				else if (node->parent->parent->right == node->parent && node->parent->left == node)
				{
					rotateRight(node->parent);
					checkInsertionViolations(node->right);
				}
				else if (node->parent->parent->left == node->parent)
				{
					rotateRight(node->parent->parent);
					node->parent->color = BLACK;
					node->parent->left->color = RED;
					node->parent->right->color = RED;
				}
				else if (node->parent->parent->right == node->parent)
				{
					rotateLeft(node->parent->parent);
					node->parent->color = BLACK;
					node->parent->left->color = RED;
					node->parent->right->color = RED;
				}
			}
		}

		Node	*predecessor_node(Node *node)
		{
			Node	*curr = node->left;

			while (curr && curr->right)
				curr = curr->right;
			return (curr);
		}

		Node	*successor_node(Node *node)
		{
			Node	*curr = node->right;

			while (curr && curr->left)
				curr = curr->left;
			return (curr);
		}

		void	swapColors(Node *node1, Node *node2)
		{
			bool color = node1->color;
			node1->color = node2->color;
			node2->color = color;
		}

		void	checkEraseViolations(Node *node)
		{
			if (!node || node->color == RED || !node->parent)
			{
				if (node)
					node->color = BLACK;
				return ;
			}
			
			if (node->parent->right == node && node->parent->left->color == RED) // sibling is RED
			{
				swapColors(node->parent, node->parent->left);
				rotateRight(node->parent);
				checkEraseViolations(node);
			}
			else if (node->parent->left == node && node->parent->right->color == RED) // sibling is RED
			{
				swapColors(node->parent, node->parent->right);
				rotateLeft(node->parent);
				checkEraseViolations(node);
			}
			else if (node->parent->right == node
				&& (!node->parent->left->left || node->parent->left->left->color == BLACK)
				&& (!node->parent->left->right || node->parent->left->right->color == BLACK)) // sibling's children are BLACK
			{
				node->parent->left->color = RED;
				if (node->parent->color == BLACK)
					checkEraseViolations(node->parent);
				else
					node->parent->color = BLACK;
			}
			else if (node->parent->left == node
				&& (!node->parent->right->left || node->parent->right->left->color == BLACK)
				&& (!node->parent->right->right || node->parent->right->right->color == BLACK)) // sibling's children are BLACK
			{
				node->parent->right->color = RED;
				if (node->parent->color == BLACK)
					checkEraseViolations(node->parent);
				else
					node->parent->color = BLACK;
			}
			else if (node->parent->right == node
				&& (node->parent->left->right && node->parent->left->right->color == RED)) // near nephew is RED
			{
				rotateLeft(node->parent->left);
				swapColors(node->parent->left, node->parent->left->left);
				checkEraseViolations(node);
			}
			else if (node->parent->left == node
				&& (node->parent->right->left && node->parent->right->left->color == RED)) // near nephew is RED
			{
				rotateRight(node->parent->right);
				swapColors(node->parent->right, node->parent->right->right);
				checkEraseViolations(node);
			}
			else if (node->parent->right == node
				&& (node->parent->left->left && node->parent->left->left->color == RED)) // far nephew is RED
			{
				rotateRight(node->parent);
				swapColors(node->parent, node->parent->parent);
				node->parent->parent->left->color = BLACK;
			}
			else if (node->parent->left == node
				&& (node->parent->right->right && node->parent->right->right->color == RED)) // far nephew is RED
			{
				rotateLeft(node->parent);
				swapColors(node->parent, node->parent->parent);
				node->parent->parent->right->color = BLACK;
			}
		}


		void	swapNodes(Node *node, Node* other)
		{
			// swap parents
			Node *x = node->parent;
			node->parent = other->parent;
			other->parent = x;
			if (node->parent)
			{
				if (node->parent->right == other)
					node->parent->right = node;
				else
					node->parent->left = node;
			}
			if (other->parent)
			{
				if (other->parent->right == node)
					other->parent->right = other;
				else
					other->parent->left = other;
			}

			//swap right child
			x = node->right;
			node->right = other->right;
			other->right = x;
			if (node->right)
				node->right->parent = node;
			if (other->right)
				other->right->parent = other;

			//swap left child
			x = node->left;
			node->left = other->left;
			other->left = x;
			if (node->left)
				node->left->parent = node;
			if (other->left)
				other->left->parent = other;

			//swap colors
			bool color = node->color;
			node->color = other->color;
			other->color = color;

			// checking if one of them is root
			if (node == root)
				root = other;
		}

	public:
		RedBlackTree(const allocator_type& alloc = allocator_type(), const compare_type& comp = compare_type()): root(nullptr), alloc(alloc), alloc_node(), comp(comp) {}
		
		RedBlackTree(const RedBlackTree &x): root(nullptr), alloc(x.alloc), alloc_node(), comp(x.comp) { *this = x; }

		RedBlackTree& operator=(const RedBlackTree &x)
		{
			if (this == &x || !x.root)
				return (*this);
			clear();
			root = alloc_node.allocate(1);
			alloc_node.construct(root, Node());
			insertNewNode(root, x.root);
			return (*this);
		}

		~RedBlackTree() { clear(); }

		void	clear()
		{
			deleteNode(root);
			root = nullptr;
		}

		Node *begin() const
		{
			Node	*curr = root;
			while (curr && curr->left)
				curr = curr->left;
			return (curr);
		}

		Node *end() const { return (nullptr); }

		Node	*search(const value_type& content) const
		{
			Node	*curr = root;
			
			while (curr)
			{
				if (curr->lhs_compare(content, comp))
					curr = curr->right;
				else if (curr->rhs_compare(content, comp))
					curr = curr->left;
				else
					return (curr);
			}
			return (nullptr);			
		}

		Node	*insert(const value_type& content)
		{
			Node	*curr = root;
			Node	*new_node = alloc_node.allocate(1);
			
			alloc_node.construct(new_node, Node());
			new_node->content = alloc.allocate(1);
			alloc.construct(new_node->content, content);
			if (!root)
				root = new_node;
			while (curr)
			{
				if (curr->rhs_compare(content, comp))
				{
					if (!curr->left)
					{
						new_node->parent = curr;
						curr->left = new_node;
						break ;
					}
					curr = curr->left;
				}
				else
				{
					if (!curr->right)
					{
						new_node->parent = curr;
						curr->right = new_node;
						break ;
					}
					curr = curr->right;
				}
			}
			checkInsertionViolations(new_node);
			return (new_node);
		}

		bool	erase(const value_type& content)
		{
			Node *target = search(content);

			if (!target) return (false);

			value_type *cont = target->content;
			if (target->left && target->right)
			{
				Node *predecessor = predecessor_node(target);
				Node *successor = successor_node(target);

				if (predecessor->color == RED || successor->color == BLACK)
					swapNodes(target, predecessor);
				else
					swapNodes(target, successor);
			}
			if (target->left)
			{
				target->left->parent = target->parent;
				if (target->parent && target->parent->left == target)
					target->parent->left = target->left;
				else if (target->parent)
					target->parent->right = target->left;

				if (target->left->color == RED)
					target->left->color = BLACK;
				else
					checkEraseViolations(target->left);
				if (target == root)
					root = target->left;
				else
					target->parent = NULL;
			}
			else if (target->right)
			{
				target->right->parent = target->parent;
				if (target->parent && target->parent->left == target)
					target->parent->left = target->right;
				else if (target->parent)
					target->parent->right = target->right;

				if (target->right->color == RED)
					target->right->color = BLACK;
				else
					checkEraseViolations(target->right);
				if (target == root)
					root = target->right;
				else
					target->parent = NULL;
			}
			else
				checkEraseViolations(target);

			if (target->parent && target->parent->left == target)
				target->parent->left = NULL;
			else if (target->parent)
				target->parent->right = NULL;
			
			if (!target->parent && !target->left && !target->right)
				root = NULL;

			alloc.destroy(cont);
			alloc.deallocate(cont, 1);
			alloc_node.destroy(target);
			alloc_node.deallocate(target, 1);
			return (true);
		}
		
		void	swap(RedBlackTree& x)
		{
			Node *tmp = root;
			root = x.root;
			x.root = tmp;
		}

		Node* lower_bound (const value_type& content) const
		{
			Node *x = root;
			Node *close = 0;
			
			while (x)
			{
				if (x->rhs_compare(content, comp))
				{
					close = x;
					x = x->left;
				}
				else if (x->lhs_compare(content, comp))
					x = x->right;
				else
					return (x);
			}
			return (close);
		}

		Node* upper_bound (const value_type& content) const
		{
			Node *x = root;
			Node *close = 0;
			
			while (x)
			{
				if (x->rhs_compare(content, comp))
				{
					close = x;
					x = x->left;
				}
				else if (x->lhs_compare(content, comp))
					x = x->right;
				else
					x = x->right;
			}
			return (close);
		}
		
		Node	*base() const { return (root); }
};

#endif /* _REDBLACKTREE_ */
