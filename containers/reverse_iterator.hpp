/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/15 16:41:31 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
    template <class T, class Distance = ptrdiff_t>
    class r_iterator
    {
    private:
        T *_ptr;
    public:
		typedef T        				        type;
        typedef Distance						difference_type;

		// reference   		operator*() const { return *_ptr; }
        

        r_iterator(T *ptr)
        {
            _ptr = ptr;
        }
        r_iterator(const r_iterator &other)
        {
            _ptr = other._ptr;
        }
        r_iterator &operator=(const r_iterator &other)
        {
            _ptr = other._ptr;
            return *this;
        }
        r_iterator &operator++()
        {
            _ptr++;
            return *this;
        }
        r_iterator &operator--()
        {
            _ptr--;
            return *this;
        }
        r_iterator operator++(int)
        {
            r_iterator tmp(*this);
            _ptr++;
            return tmp;
        }
        r_iterator operator--(int)
        {
            r_iterator tmp(*this);
            _ptr--;
            return tmp;
        }
        bool operator==(const r_iterator &other) const
        {
            return _ptr == other._ptr;
        }
        bool operator!=(const r_iterator &other) const
        {
            return _ptr != other._ptr;
        }
        r_iterator &operator+(int i)
        {
            _ptr += i;
            return *this;
        }
        r_iterator &operator-(int i)
        {
            _ptr -= i;
            return *this;
        }
        bool operator<(const r_iterator &other) const
        {
            return _ptr < other._ptr;
        }
        bool operator>(const r_iterator &other) const
        {
            return _ptr > other._ptr;
        }
        bool operator<=(const r_iterator &other) const
        {
            return _ptr <= other._ptr;
        }
        bool operator>=(const r_iterator &other) const
        {
            return _ptr >= other._ptr;
        }
        friend r_iterator	operator-(difference_type n, const r_iterator& it) 
        {
            return vector_iterator(it._ptr - n); 
        }
        friend difference_type	operator-(const r_iterator& a, const r_iterator& b)
        {
            return (a._ptr - b._ptr);
        }
        friend bool 	operator> (const r_iterator& lhs, const r_iterator& rhs) { return lhs._ptr > rhs._ptr; }
        T &operator*()
        {
            return *_ptr;
        }
    };
}