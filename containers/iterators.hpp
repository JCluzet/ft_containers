// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   iterators.hpp                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/10/05 17:07:19 by besellem          #+#    #+#             */
// /*   Updated: 2022/04/12 23:01:41 by jcluzet          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef TREE_ITERATOR_HPP
// # define TREE_ITERATOR_HPP

// # include <iostream>

// # include "iterator.hpp"
// # include "RedBlackTree.hpp"
// # include "utils.hpp"


// _BEGIN_NAMESPACE_FT

// template <class T, class Node>
// class tree_iterator : public iterator<bidirectional_iterator_tag, T>
// {

// 	public:
// 		typedef T                                                 value_type;
// 		typedef Node                                              node_type;
// 		typedef Node*                                             node_pointer;
		
// 		typedef iterator<bidirectional_iterator_tag, value_type>  iterator_type;
// 		typedef typename iterator_type::iterator_category         iterator_category;
// 		typedef typename iterator_type::difference_type           difference_type;
// 		typedef typename iterator_type::pointer                   pointer;
// 		typedef typename iterator_type::reference                 reference;


// 	public:
// 		tree_iterator(void) : _begin(nullptr_), _end(nullptr_), _cur(nullptr_) {}
		
// 		tree_iterator(node_pointer const& begin, node_pointer const& end, node_pointer const& current) :
// 			_begin(begin),
// 			_end(end),
// 			_cur(current)
// 		{}

// 		tree_iterator(tree_iterator const& u)
// 		{
// 			*this = u;
// 		}

// 		tree_iterator&		operator=(const tree_iterator& u)
// 		{
// 			if (this == &u)
// 				return *this;
			
// 			_begin = u._begin;
// 			_end = u._end;
// 			_cur = u._cur;
// 			return *this;
// 		}
		
// 		~tree_iterator() {}

// 		node_pointer		get_current(void) const
// 		{
// 			return _cur;
// 		}

// 		reference			operator*() const
// 		{
// 			return _cur->val;
// 		}
		
// 		pointer				operator->() const
// 		{
// 			return &(operator*());
// 		}

// 		tree_iterator&		operator++()
// 		{
// 			if (_cur == max(_begin))
// 			{
// 				_cur = _end;
// 				return *this;
// 			}
// 			else if (_cur == _end)
// 			{
// 				_cur = nullptr_;
// 				return *this;
// 			}
// 			_cur = successor(_cur);
// 			return *this;
// 		}
		
// 		tree_iterator		operator++(int)
// 		{
// 			tree_iterator	tmp(*this);
// 			operator++();
// 			return tmp;
// 		}
		
// 		tree_iterator&		operator--()
// 		{
// 			if (_cur == _end)
// 			{
// 				_cur = max(_begin);
// 				return *this;
// 			}
// 			_cur = predecessor(_cur);
// 			return *this;
// 		}
		
// 		tree_iterator		operator--(int)
// 		{
// 			tree_iterator	tmp(*this);
// 			operator--();
// 			return tmp;
// 		}

// 		// needed for conversion to a const_iterator
// 		operator			tree_iterator<const T, Node> (void)
// 		{
// 			return tree_iterator<const T, Node>(_begin, _end, _cur);
// 		}


// 	private:
// 		node_pointer	min(node_pointer s)
// 		{
// 			for ( ; s->left != _end; s = s->left);
// 			return s;
// 		}

// 		node_pointer	max(node_pointer s)
// 		{
// 			for ( ; s->right != _end; s = s->right);
// 			return s;
// 		}

// 		node_pointer	successor(node_pointer s)
// 		{
// 			if (s->right != _end)
// 				return min(s->right);

// 			node_pointer	tmp = s->parent;
// 			while (tmp != _end && s == tmp->right)
// 			{
// 				s = tmp;
// 				tmp = tmp->parent;
// 			}
// 			return tmp;
// 		}

// 		node_pointer	predecessor(node_pointer s)
// 		{
// 			if (s->left != _end)
// 				return max(s->left);

// 			node_pointer	tmp = s->parent;
// 			while (tmp != _end && s == tmp->left)
// 			{
// 				s = tmp;
// 				tmp = tmp->parent;
// 			}
// 			return tmp;
// 		}


// 	private:
// 		node_pointer	_begin;
// 		node_pointer	_end;
// 		node_pointer	_cur;

// }; /* tree_iterator */

// template <class IteratorL, class IteratorR, class _Node>
// bool	operator==(tree_iterator<IteratorL, _Node> const& x,
// 				   tree_iterator<IteratorR, _Node> const& y)
// { return x.get_current() == y.get_current(); }

// template <class IteratorL, class IteratorR, class _Node>
// bool	operator!=(tree_iterator<IteratorL, _Node> const& x,
// 				   tree_iterator<IteratorR, _Node> const& y)
// { return x.get_current() != y.get_current(); }


// _END_NAMESPACE_FT

// #endif /* define TREE_ITERATOR_HPP */








/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/12 15:36:40 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	struct random_access_iterator_tag {};
	struct bidirectional_iterator_tag {};
	
    template <class T, class Distance = ptrdiff_t>
    class vectiterator
    {
    private:
        T *_ptr;
    public:
        typedef Distance						difference_type;
        vectiterator(T *ptr)
        {
            _ptr = ptr;
        }
        vectiterator(const vectiterator &other)
        {
            _ptr = other._ptr;
        }
        virtual ~vectiterator() {};
        vectiterator &operator=(const vectiterator &other)
        {
            _ptr = other._ptr;
            return *this;
        }
        vectiterator &operator++()
        {
            _ptr++;
            return *this;
        }
        vectiterator &operator--()
        {
            _ptr--;
            return *this;
        }
        vectiterator operator++(int)
        {
            vectiterator tmp(*this);
            _ptr++;
            return tmp;
        }
        vectiterator operator--(int)
        {
            vectiterator tmp(*this);
            _ptr--;
            return tmp;
        }
        bool operator==(const vectiterator &other) const
        {
            return _ptr == other._ptr;
        }
        bool operator!=(const vectiterator &other) const
        {
            return _ptr != other._ptr;
        }
        vectiterator &operator+(int i)
        {
            _ptr += i;
            return *this;
        }
        vectiterator &operator-(int i)
        {
            _ptr -= i;
            return *this;
        }
        bool operator<(const vectiterator &other) const
        {
            return _ptr < other._ptr;
        }
        bool operator>(const vectiterator &other) const
        {
            if (_ptr < other._ptr)
                return false;
            return true;
        }
        bool operator<=(const vectiterator &other) const
        {
            return _ptr <= other._ptr;
        }
        bool operator>=(const vectiterator &other) const
        {
            return _ptr >= other._ptr;
        }
        friend vectiterator	operator-(difference_type n, const vectiterator& it) 
        {
            return vector_iterator(it._ptr - n); 
        }
        friend difference_type	operator-(const vectiterator& a, const vectiterator& b)
        {
            return (a._ptr - b._ptr);
        }
        // friend bool 	operator> (const vectiterator& lhs, const vectiterator& rhs) { return lhs._ptr > rhs._ptr; }
        T &operator*()
        {
            return *_ptr;
        }
        T *operator->()
        {
            return &(operator*)();
        }
    };

    
    template < class Category, class T, class not_const_T = T>
	class map_iterator
	{
		public:
			typedef typename T::value_type				value_type;
			typedef typename not_const_T::Node			Node;
			typedef typename T::key_type				key_type;
			typedef typename T::mapped_type				mapped_type;
			typedef	typename T::key_compare				key_compare;
			typedef typename T::pointer   				pointer;
			typedef typename T::reference 				reference;
			typedef ptrdiff_t							difference_type;
			typedef Category							iterator_category;
 
			map_iterator() {}
			// map_iterator(const map_iterator<Category, not_const_T> &toCopy) : _begin(toCopy.base()), _end(toCopy.end()) {}
			map_iterator(Node* node, Node* end) {
				this->_begin = node;
				this->_end = end;
			}
			virtual ~map_iterator() {}
            
            reference   	operator*() const { return this->_begin->pair; }

			// Node*			base() const { return this->_ptr; }
			Node*			end() const { return this->_end; }

            bool operator!=(const map_iterator<Category, T, not_const_T> &other) const
            {
                return this->_begin != other._begin;
            }

            bool operator==(const map_iterator<Category, T, not_const_T> &other) const
            {
                return this->_begin == other._begin;
            }

            pointer operator->() const
            {
                if (this->_begin == nullptr)
                    return nullptr;
                return &(operator*)();
            }

            // map_iterator& operator--(int)
            // {
            //     map_iterator tmp(*this);
                
            //     return tmp;
            // }

            // map_iterator& operator++()
            // {
            //     this->_begin = this->_begin->next;
            //     return *this;
            // }

		// map_iterator&
		// operator++() throw() {

		// 	if (!pair->right) {
		// 		pair = pair->_right;
		// 		if (pair->_last_node)
		// 			return iterator(ptr);
		// 		while (!ptr->_left->_last_node && !ptr->_left->_null)
		// 			ptr = ptr->_left;
		// 	} else {
		// 		if (_key_comp(ptr, ptr->_parent))
		// 			ptr = ptr->_parent;
		// 		else {
		// 			while (!_key_comp(ptr, ptr->_parent))
		// 				ptr = ptr->_parent;
		// 			ptr = ptr->_parent;
		// 		}
		// 	}
		// 	return iterator(ptr);
		// }

			map_iterator&   operator++()
			{
				// find the smallest greater
				if (this->_begin->right)
				{
					this->_begin = this->_begin->right->min();
					return *this;
				}
				else if (this->_begin->parent)
				{
					// find first previous greater node
					key_type key = this->_begin->pair.first;
					Node *tmp = this->_begin->parent;
					while (tmp && this->_comp(tmp->pair.first, key))
						tmp = tmp->parent;
					if (tmp)
					{
						this->_begin = tmp;
						return *this;
					}
				}
				this->_begin = this->_end;
				return *this;
			}

        // map_iterator& operator++()
        // {
        //     if (this->_begin->next)
        //         this->_begin = this->_begin->next;
        //     else
        //     {
        //         Node* tmp = this->_begin;
        //         while (tmp->next == NULL)
        //         {
        //             tmp = tmp->parent;
        //             if (tmp == NULL)
        //                 break;
        //         }
        //         if (tmp == NULL)
        //             this->_begin = NULL;
        //         else
        //             this->_begin = tmp->next;
        //     }
        //     return *this;
        // }
            

            // map_iterator&   operator++()
			// {
			// 	if (_begin->right)
			// 	{
			// 		_begin = _begin->right->min();
			// 		return *this;
			// 	}
			// 	else if (_begin->parent)
			// 	{
			// 		key_type key = _begin->pair.first;
			// 		Node *tmp = _begin->parent;
			// 		while (tmp && _comp(tmp->pair.first, key))
			// 			tmp = tmp->parent;
			// 		if (tmp)
			// 		{
			// 			_begin = tmp;
			// 			return *this;
			// 		}
			// 	}
			// 	_begin = _end;
			// 	return *this;
			// }

            map_iterator    operator++(int) { map_iterator tmp = *this; ++*this; return tmp; }
            private:
                Node*		_begin;
                Node*		_end;
                key_compare _comp;
    };
}