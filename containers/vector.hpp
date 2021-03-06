/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:25 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/22 14:01:25 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterators.hpp"
#include "reverse_iterator.hpp"
#include "../utils/enable_if.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector // Based on std::vector class with cplusplus.com prototype
    {
    public:
        // --------------------------TYPEDEF------------------------------ //   ✅
        typedef T                                               value_type;
        typedef Alloc                                           allocator_type;
        typedef typename std::ptrdiff_t						    difference_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef	vectiterator<random_access_iterator_tag, T>		iterator;
        typedef vectiterator<random_access_iterator_tag, T>             const_iterator;
        typedef	reverse_iterator_vec<random_access_iterator_tag, T>		reverse_iterator;
        typedef reverse_iterator_vec<random_access_iterator_tag, T>	const_reverse_iterator;
        
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
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
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

        // constructor by copy
        vector(const vector &x) : _alloc(x._alloc), _size(x._size), _capacity(x._size)
        {
            _begin = _alloc.allocate(x._capacity);
            for (size_type i = 0; i < _size; i++)
                _alloc.construct(&_begin[i], x._begin[i]);
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

        size_type max_size() const {
        return (std::min((size_type) std::numeric_limits<difference_type>::max(),
						std::numeric_limits<size_type>::max() / sizeof(value_type)));}

        size_type capacity() const { return _capacity; }

        bool empty() const { return _size == 0; }

        void resize(size_type n, value_type val = value_type())
        {
            while (_size > n)
                pop_back();
            if ( n > _capacity * 2)
                reserve(n);
            while (_size < n)
                push_back(val);
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
  		void			assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
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

        void push_back (const value_type& val)
		{
			if (_capacity == 0){
				_capacity = 1;
				_begin = _alloc.allocate(_capacity);
				_alloc.construct(&_begin[0], val);
				_size++;
				return;
			}
			if (_capacity > _size)
            {
                _alloc.construct(&_begin[_size], val);
                _size++;
                return;
            }
			_capacity *= 2;
			pointer tmp = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(&tmp[i], _begin[i]);
				_alloc.destroy(&_begin[i]);
			}
			_alloc.deallocate(_begin, _capacity);
			_begin = tmp;
			_alloc.construct(&_begin[_size], val);
			_size++;
			return;
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
            if (n + _size > _capacity * 2)
                reserve(n + _size);
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

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
            iterator	it = end();
            vector tmp(position, it);
            if ((last - first) + _size > _capacity * 2)
                reserve((last-first) + _size);
            while ( it != position)
            {
                pop_back();
                it--;
            }
            for (; first != last;)
                push_back(*first++);
            it = tmp.begin();
            for (; it != tmp.end();)
            {
                push_back(*it);
                it++;
            }
		}

        iterator erase (iterator const &position) {
			size_type index = position - begin();
			_alloc.destroy(_begin + index);
			std::move(_begin + index + 1, _begin + _size, _begin + index);
			_size -= 1;
			return position;
		}

        // create iterator erase (iterator first, iterator last) with erase (iterator first)
        iterator erase (iterator const &first, iterator const &last)
        {
            // erase all elements in [first, last)
            difference_type n = last - first;
            difference_type index = first - begin();
            _alloc.destroy(_begin + index);
            std::move(_begin + index + n, _begin + _size, _begin + index);
            _size -= n;
            return first;
        }

        void swap (vector& x){
			pointer			bg = _begin;
			size_type		size = _size;
			size_type		capacity = _capacity;
			allocator_type	alloc = _alloc;
			_begin = x._begin;
			_size = x._size;
			_capacity = x._capacity;
			_alloc = x._alloc;
			x._begin = bg;
			x._size = size;
			x._capacity = capacity;
			x._alloc = alloc;
		}

        void clear()
        {
            _size = 0;
            resize(0);
        }

        // --------------------------ITERATORS-----------------------------

        iterator begin() { return iterator(this->_begin); }
        const_iterator begin() const { return const_iterator(this->_begin); }

        iterator end() { return iterator(this->_begin) + _size; }
        const_iterator end() const { return const_iterator(this->_begin) + _size; }

        reverse_iterator rbegin() { return reverse_iterator(this->_begin) + _size - 1; }
        reverse_iterator rend() { return reverse_iterator(this->_begin) - 1; }

        // reverse_iterator rend() { return reverse_iterator(this->_begin) - 1; }

        // --------------------------ALLOCATOR------------------------------- //  ✅

        allocator_type get_allocator() const { return _alloc; }

        // --------------------------------------------PRIVATE--------------------------------------------
    private:
        pointer _begin;
        allocator_type _alloc;
        size_type _size;
        size_type _capacity;
    };

    // OPERATORS

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); i++)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }
    template <class T, class Alloc>
    bool operator != (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }
    template <class T, class Alloc>
    bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) 
    { return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return rhs < lhs; }
    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs > rhs); }
    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs); }
}