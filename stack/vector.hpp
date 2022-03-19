/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:25 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/19 22:29:26 by jcluzet          ###   ########.fr       */
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

        typedef T value_type;
        typedef Alloc allocator_type; // alloc use?
        typedef typename std::ptrdiff_t						difference_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef vectiterator<T> iterator;
        typedef size_t size_type;
        typedef typename allocator_type::pointer pointer;

        // --------------------------CONSTRUCTOR-------------------------- //   ✅

        explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0) // empty constructor
        {
            _begin = NULL;
        }

        explicit vector(size_type n, const value_type &val = value_type(), // fill constructor
                        const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
        {
            _begin = _alloc.allocate(n);
            for (size_type i = 0; i < n; i++)
                _alloc.construct(&_begin[i], val);
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
		: _alloc(alloc), _size(0){
            size_type n = 0;
			for (InputIterator it = first; it != last; it++)
				++n;
			_capacity = n;
            _size = n;
			_begin = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(&_begin[i], *first);
				first++;
			}
		}

        vector(const vector &x) // copy constructor
        {
            *this = x;
        }

        ~vector()
        {
            this->clear();
            this->_alloc.deallocate(this->_begin, this->_capacity);
        }

        vector &operator=(const vector &x)
        {
            clear();
            reserve(x.size());
            for (size_type i = 0; i < x.size(); i++)
                _alloc.construct(&_begin[i], x._begin[i]);
            _size = x.size();
            return *this;
        }

        // --------------------------CAPACITY----------------------------- //   ✅

        size_type size() const { return _size; }

        size_type max_size() const throw() { return std::numeric_limits<long>::max() / sizeof(T); }

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
        void assign(InputIterator first, InputIterator last, typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer>::type * = 0)
        {
            while (_size > 0)
                _alloc.destroy(&_begin[_size--]);
            _size = 0;
            for (; first != last;)
                push_back(*first++);
        }

        void assign(size_type n, const value_type &val)
        {
            while (_size > 0)
                _alloc.destroy(&_begin[_size--]);
            *this = vector(n, val);
        }

        void push_back(const value_type &val)
        {
            size_type oldcap = 1;
            if (_capacity >= _size + 1)
            {
                this->_alloc.construct(&this->_begin[_size], val);
                _size++;
                return;
            }
            if (this->_capacity > 0)
            {
                oldcap = _capacity;
                this->_capacity = _capacity * 2;
            }
            else
                this->_capacity = 1;
            pointer tmp = this->_begin;
            this->_begin = this->_alloc.allocate(oldcap);
            for (size_type i = 0; i < this->_size; i++)
            {
                this->_alloc.construct(&this->_begin[i], tmp[i]);
                this->_alloc.destroy(&tmp[i]);
            }
            this->_alloc.construct(&this->_begin[this->_size], val);
            this->_alloc.deallocate(tmp, this->_capacity);
            _size++;
        }

        void pop_back()
        {
            if (_size == 0)
                throw std::out_of_range("out of range");
            _alloc.destroy(&_begin[_size - 1]);
            _size--;
        }

		iterator insert (iterator position, const value_type& val) {
			difference_type n = position - begin();
			insert(position, 1, val);
			return (begin() + n);
		}
		void insert (iterator position, size_type n, const value_type& val) {
			iterator	it = end();
			vector		tmp(position, it);
			while (it != position){
				pop_back();
				it--;
			}
			while (n){
				push_back(val);
				n--;
			}
			it = tmp.begin();
			while (it != tmp.end()){
				push_back(*it);
				it++;
			}
		}
        // template<typename InputIterator>
		// void insert (iterator position, InputIterator first, InputIterator last) {
		// 	typedef typename ft::is_integer_my<InputIterator>::type_my _Integral;
		// 	_insert(position, first, last, _Integral());
		// }
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) {
			iterator	it = end();
			vector		tmp(position, it);
			while (it != position){
				pop_back();
				it--;
			}
			while (first != last){
				push_back(*first);
				first++;
			}
			it = tmp.begin();
			while (it != tmp.end()){
				push_back(*it);
				it++;
			}
		}

        // void erase(iterator position)
        // {
        //     for (size_type i = position - _begin; i < _size - 1; i++)
        //         _begin[i] = _begin[i + 1];
        //     _alloc.destroy(&_begin[_size - 1]);
        //     _size--;
        // }

        // iterator erase(iterator position)
        // {
        //     size_type n = position - this->begin();
        //     for (size_type i = n; i < _size - 1; i++)
        //         _begin[i] = _begin[i + 1];
        //     _alloc.destroy(&_begin[_size - 1]);
        //     _size--;
        // }

        iterator erase(iterator position)
        {
            iterator it = end();
            vector tmp(position + 1, it);
            while (it != position)
            {
                pop_back();
                it--;
            }
            for (iterator ite = tmp.begin(); ite != tmp.end(); ite++)
                push_back(*ite);
            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            size_type n = last - first;
            size_type i = first - _begin;
            for (size_type j = i; j < _size - n; j++)
                _begin[j] = _begin[j + n];
            for (size_type j = _size - n; j < _size; j++)
                _alloc.destroy(&_begin[j]);
            _size -= n;
            return _begin + i;
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