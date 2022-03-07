/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:25 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/07 02:31:45 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterators.hpp"
#include "../utils/enable_if.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector // Based on std::vector class with cplusplus.com prototype
    {
    public:
        // --------------------------TYPEDEF------------------------------ //   ✅

        typedef Alloc allocator_type; // alloc use?
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef T value_type;
        typedef vectiterator<T> iterator;
        typedef size_t size_type;
        typedef typename allocator_type::pointer pointer;

        // --------------------------CONSTRUCTOR-------------------------- //   ✅

        explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0) // empty constructor
        {
            _begin = nullptr;
        }

        explicit vector(size_type n, const value_type &val = value_type(), // fill constructor
                        const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
        {
            _begin = _alloc.allocate(n);
            for (size_type i = 0; i < n; i++)
                _alloc.construct(&_begin[i], val);
            
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), // range constructor
               typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer>::type * = 0) : _alloc(alloc), _size(0), _capacity(0)
        {
            _begin = nullptr;
            for (; first != last;)
                push_back(*first++);
        }

        vector(const vector &x) // copy constructor
        {
            _size = x._size;
            _capacity = x._capacity;
            _begin = new T[x._capacity];
            for (size_type i = 0; i < _size; i++)
                _begin[i] = x._begin[i];
        }

        ~vector() {}

        vector &operator=(const vector &x)
        {
            _size = x._size;
            _capacity = x._capacity;
            _begin = new T[_capacity];
            for (size_t i = 0; i < _size; i++)
                _begin[i] = x._begin[i];
            return *this;
        }

        // --------------------------CAPACITY----------------------------- //   ✅

        size_type size() const { return _size; }

        size_type max_size() const { return _capacity; }

        size_type capacity() const { return _capacity; }

        bool empty() const { return _size == 0; }

        void resize(size_type n, value_type val = value_type())
        {
            if (n > _capacity)
                reserve(n);
            if (n > _size)
            {
                for (size_type i = _size; i < n; i++)
                    _alloc.construct(&_begin[i], val);
            }
            else if (n < _size)
            {
                for (size_type i = n; i < _size; i++)
                    _alloc.destroy(&_begin[i]);
            }
            _size = n;
        }

        void reserve(size_type n)
        {
            if (n <= _capacity)
                return;
            pointer x = _begin;

            _begin = _alloc.allocate(n);
            for (size_type i = 0; i < _size; i++)
            {
                this->_alloc.construct(&this->_begin[i], x[i]);
                this->_alloc.destroy(&x[i]);
            }

            this->_alloc.deallocate(x, this->_capacity);
            this->_capacity = n;
        }

        // --------------------------ELEMENT_ACCESS----------------------------- // ✅

        reference operator[](size_type n) { return _begin[n]; }

        const_reference operator[](size_type n) const { return _begin[n]; }

        reference at(size_type n)
        {
            if (n >= _size)
                throw std::out_of_range("out of range");
            return _begin[n];
        }

        const_reference at(size_type n) const
        {
            if (n >= _size)
                throw std::out_of_range("out of range");
            return _begin[n];
        }

        reference &front() { return _begin[0]; }

        const_reference &front() const { return _begin[0]; }

        reference &back() { return _begin[_size - 1]; }

        const_reference &back() const { return _begin[_size - 1]; }

        // --------------------------MODIFIERS----------------------------- //      ✅

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            for (; first != last;)
                push_back(*first++);
        }

        void assign(size_type n, const value_type &val)
        {
            for (size_type i = 0; i < n; i++)
                _begin[i] = val;
        }

        void push_back(const value_type &val)
        {
            if (this->_capacity > _size)
            {
                this->_alloc.construct(&this->_begin[_size], val);
                _size++;
                return;
            }
            pointer tmp = this->_begin;
            this->_begin = this->_alloc.allocate(this->_size + 1);
            for (size_type i = 0; i < this->_size; i++)
            {
                this->_alloc.construct(&this->_begin[i], tmp[i]);
                this->_alloc.destroy(&tmp[i]);
            }
            this->_alloc.construct(&this->_begin[this->_size], val);
            this->_alloc.deallocate(tmp, this->_capacity);
            _size++;
            this->_capacity = _size;
        }

        void pop_back()
        {
            if (_size == 0)
                throw std::out_of_range("out of range");
            _alloc.destroy(&_begin[_size - 1]);
            _size--;
        }

        iterator insert(iterator position, const value_type &val)
        {
            if (_size == _capacity)
                resize(_size + 1);
            for (size_type i = _size; i > position - _begin; i--)
                _begin[i] = _begin[i - 1];
            _alloc.construct(&_begin[position - _begin], val);
            _size++;
            return position;
        }

        void insert(iterator position, size_type n, const value_type &val)
        {
            if (n > _capacity)
                resize(_size + n);
            for (size_type i = _size; i > position - _begin; i--)
                _begin[i] = _begin[i - n];
            for (size_type i = 0; i < n; i++)
                _alloc.construct(&_begin[position - _begin + i], val);
            _size += n;
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            for (; first != last;)
                insert(position, *first++);
        }

        void erase(iterator position)
        {
            for (size_type i = position - _begin; i < _size - 1; i++)
                _begin[i] = _begin[i + 1];
            _alloc.destroy(&_begin[_size - 1]);
            _size--;
        }

        iterator erase(iterator first, iterator last)
        {
            for (size_type i = first - _begin; i < last - _begin; i++)
                _alloc.destroy(&_begin[i]);
            for (size_type i = first - _begin; i < _size - (last - _begin); i++)
                _begin[i] = _begin[i + (last - first)];
            _size -= (last - first);
            return first;
        }

        void swap(vector &x)
        {
            vector tmp(x);
            x = *this;
            *this = tmp;
        }

        void clear()
        {
            _size = 0;
            resize(0);
        }

        // --------------------------ITERATORS----------------------------- // missing const iterator

        iterator begin() { return iterator(this->_begin); }

        iterator end() { return iterator(this->_begin) + _size; }

        iterator rbegin() { return iterator(this->_begin) + _size - 1; }

        iterator rend() { return iterator(this->_begin) - 1; }

        // --------------------------ALLOCATOR------------------------------- //  ✅

        allocator_type get_allocator() const { return _alloc; }

        // --------------------------------------------PRIVATE--------------------------------------------
    private:
        pointer _begin;
        allocator_type _alloc;
        size_type _size;
        size_type _capacity;
    };
}