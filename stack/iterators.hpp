/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/20 00:14:19 by jcluzet          ###   ########.fr       */
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
        friend vectiterator	operator-(difference_type n, const vectiterator& it) 
        {
            return vector_iterator(it._ptr - n); 
        }
        friend difference_type	operator-(const vectiterator& a, const vectiterator& b)
        {
            return (a._ptr - b._ptr);
        }
        friend bool 	operator> (const vectiterator& lhs, const vectiterator& rhs) { return lhs._ptr > rhs._ptr; }
        T &operator*()
        {
            return *_ptr;
        }
    };
}