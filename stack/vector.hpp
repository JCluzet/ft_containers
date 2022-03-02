/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:25 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/02 17:19:32 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterators.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> > // Class alloc ?? 
    class vector
    {
    public:
        // --------------------------TYPEDEF------------------------------ //
        typedef	Alloc								allocator_type; // alloc use?
        typedef	T									value_type;
        typedef vectiterator<T>						iterator;
        typedef	size_t								size_type;
        typedef	typename allocator_type::pointer	pointer;
        
        // --------------------------CONSTRUCTOR-------------------------- //
        vector()                 // empty constructor
        {
            _size = 0;
            _capacity = 1;
            _begin = new T[1];
            // resize(1);
        }
        vector(size_type n, value_type e)       // size constructor
        {
            _size = n;
            _capacity = n;
            _begin = new T[n];
            for (size_type i = 0; i < n; i++)
                _begin[i] = e;
        }
        vector(iterator begin, iterator end)    // range constructor
        {
            _size = 0;
            _capacity = 0;
            _begin = new T[0];
            for (iterator it = begin; it != end; it++)
                push_back(*it);
        }
        vector(const vector &other) // copy constructor 
        {
            _size = other._size;
            _capacity = other._capacity;
            _begin = new T[other._capacity];
            for (size_type i = 0; i < _size; i++)
                _begin[i] = other._begin[i];
        }
        



        ~vector() {}
        vector &operator=(const vector &other)
        {
            _size = other._size;
            _capacity = other._capacity;
            _begin = new T[_capacity];
            for (size_t i = 0; i < _size; i++)
                _begin[i] = other._begin[i];
            return *this;
        }

        // --------------------------CAPACITY----------------------------- //

        size_type size() { return _size; }
        size_type max_size() { return _capacity; }
        size_type capacity() { return _capacity; }
        bool empty() { return _size == 0; }
        void resize(unsigned int new_capacity)
        {
            T *new_tab = new T[new_capacity];
            for (unsigned int i = 0; i < _size; i++)
                new_tab[i] = _begin[i];
            delete[] _begin;
            _begin = new_tab;
            _capacity = new_capacity;
        }
        void reserve(unsigned int new_capacity)
        {
            if (new_capacity <= _capacity)
                return;
            resize(new_capacity);
        }

        // --------------------------ELEMENT_ACCESS----------------------------- //

        T operator[](size_type i) { return _begin[i]; }
        T at(size_type i)
        {
            if (i >= _size)
                throw std::out_of_range("out of range");
            return _begin[i];
        }
        T &front() { return _begin[0]; }
        T &back() { return _begin[_size - 1]; }


        // --------------------------MODIFIERS----------------------------- //
        
        void push_back(T i)
        {
            if (_size == _capacity)
                resize(++_capacity);
            _begin[_size] = i;
            _size++;
        }
        void pop_back()
        {
            if (_size == 0)
                return;
            _size--;
            if (_size < _capacity / 4)
                resize(_capacity / 2);
        }
        void insert() {
            if (_size == _capacity)
                resize(++_capacity);
            for (unsigned int i = _size; i > 0; i--)
                _begin[i] = _begin[i - 1];
            _size++;
        }
        void clear()
        {
            _size = 0;
            resize(1);
        }

        // --------------------------ITERATORS----------------------------- //

        iterator begin() { return iterator(this->_begin); }
        iterator end() { return iterator(this->_begin) + _size; }
        iterator rbegin() { return iterator(this->_begin) + _size - 1; }
        iterator rend() { return iterator(this->_begin) - 1; }

        // --------------------------OPERATOR------------------------------- //


    // --------------------------------------------PRIVATE--------------------------------------------
    private:
        pointer _begin;
        size_type _size;
        size_type _capacity;
    };
}