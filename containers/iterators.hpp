/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/15 18:55:40 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	struct random_access_iterator_tag {};
	struct bidirectional_iterator_tag {};
	
    template <class Category, class T, class Distance = ptrdiff_t, class Reference = T&,  class Pointer = T*>
    class vectiterator
    {
    private:
        T *_ptr;
    public:
        typedef T                               value_type;
		// typedef Pointer   						Pointer;
        typedef Category						iterator_category;
		typedef Reference 						reference;
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

    
    template < class Category, class T, class notconst_T = T>
	class map_iterator
	{
		public:
			typedef typename T::value_type				value_type;
			typedef typename notconst_T::Node			Node;
			typedef typename T::key_type				key_type;
			typedef typename T::mapped_type				mapped_type;
			typedef	typename T::key_compare				key_compare;
			typedef typename T::pointer   				pointer;
			typedef typename T::reference 				reference;
			typedef ptrdiff_t							difference_type;
			typedef Category							iterator_category;
 
			map_iterator() {}
			map_iterator(const map_iterator<Category, notconst_T> &toCopy) : _begin(toCopy.base()), _end(toCopy.end()) {}
			map_iterator(Node* node, Node* end) {
				this->_begin = node;
				this->_end = end;
			}

			Node*			base() const { return this->_begin; }
			Node*			end() const { return this->_end; }



			virtual ~map_iterator() {}

            
            reference   	operator*() const { return this->_begin->pair; }


            bool operator!=(const map_iterator<Category, T, notconst_T> &other) const
            {
                return this->_begin != other._begin;
            }

            bool operator==(const map_iterator<Category, T, notconst_T> &other) const
            {
                return this->_begin == other._begin;
            }

            pointer operator->() const
            {
                if (this->_begin == nullptr)
                    return nullptr;
                return &(operator*)();
            }

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

            map_iterator&  operator--()
            {
                // find the smallest greater
                if (this->_begin->left)
                {
                    this->_begin = this->_begin->left->max();
                    return *this;
                }
                else if (this->_begin->parent)
                {
                    // find first previous greater node
                    key_type key = this->_begin->pair.first;
                    Node *tmp = this->_begin->parent;
                    while (tmp && this->_comp(key, tmp->pair.first))
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

            map_iterator    operator++(int) { map_iterator tmp = *this; ++*this; return tmp; }
            map_iterator    operator--(int) { map_iterator tmp = *this; --*this; return tmp; }
            private:
                Node*		_begin;
                Node*		_end;
                key_compare _comp;
    };
}