/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/25 00:03:32 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
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
    };
    	template <	class Category, class T, class not_const_T = T>
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
			map_iterator(const map_iterator<Category, not_const_T> &toCopy) : _begin(toCopy.base()), _end(toCopy.end()) {}
			map_iterator(Node* node, Node* end) {
				this->_begin = node;
				this->_end = end;
			}
			virtual ~map_iterator() {}

			Node*			base() const { return this->_ptr; }
			Node*			end() const { return this->_end; }
            private:
                Node*		_begin;
                Node*		_end;
    };
}