/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/15 15:36:15 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template <class T, class Distance = ptrdiff_t>
    class rvectiterator
    {
    private:
        T *_ptr;
    public:
        typedef Distance						difference_type;
        rvectiterator(T *ptr)
        {
            _ptr = ptr;
        }
        rvectiterator(const rvectiterator &other)
        {
            _ptr = other._ptr;
        }
        rvectiterator &operator=(const rvectiterator &other)
        {
            _ptr = other._ptr;
            return *this;
        }
        rvectiterator &operator++()
        {
            _ptr++;
            return *this;
        }
        rvectiterator &operator--()
        {
            _ptr--;
            return *this;
        }
        rvectiterator operator++(int)
        {
            rvectiterator tmp(*this);
            _ptr++;
            return tmp;
        }
        rvectiterator operator--(int)
        {
            rvectiterator tmp(*this);
            _ptr--;
            return tmp;
        }
        bool operator==(const rvectiterator &other) const
        {
            return _ptr == other._ptr;
        }
        bool operator!=(const rvectiterator &other) const
        {
            return _ptr != other._ptr;
        }
        rvectiterator &operator+(int i)
        {
            _ptr += i;
            return *this;
        }
        rvectiterator &operator-(int i)
        {
            _ptr -= i;
            return *this;
        }
        bool operator<(const rvectiterator &other) const
        {
            return _ptr < other._ptr;
        }
        bool operator>(const rvectiterator &other) const
        {
            return _ptr > other._ptr;
        }
        bool operator<=(const rvectiterator &other) const
        {
            return _ptr <= other._ptr;
        }
        bool operator>=(const rvectiterator &other) const
        {
            return _ptr >= other._ptr;
        }
        friend rvectiterator	operator-(difference_type n, const rvectiterator& it) 
        {
            return vector_iterator(it._ptr - n); 
        }
        friend difference_type	operator-(const rvectiterator& a, const rvectiterator& b)
        {
            return (a._ptr - b._ptr);
        }
        friend bool 	operator> (const rvectiterator& lhs, const rvectiterator& rhs) { return lhs._ptr > rhs._ptr; }
        T &operator*()
        {
            return *_ptr;
        }
    };
}