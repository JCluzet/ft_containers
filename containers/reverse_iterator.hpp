/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/21 13:40:24 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template <class Category, class T, class notconst_T = T>
    class reverse_iterator_map
    {
    public:
        typedef typename T::value_type value_type;
        typedef typename notconst_T::Node Node;
        typedef typename T::key_type key_type;
        typedef typename T::mapped_type mapped_type;
        typedef typename T::key_compare key_compare;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
        typedef ptrdiff_t difference_type;
        typedef Category iterator_category;

        reverse_iterator_map() {}
        reverse_iterator_map(const reverse_iterator_map<Category, notconst_T> &toCopy) : _begin(toCopy.base()), _end(toCopy.end()) {}
        reverse_iterator_map(Node *node, Node *end)
        {
            this->_begin = node;
            this->_end = end;
        }

        Node *base() const { return this->_begin; }
        Node *end() const { return this->_end; }

        virtual ~reverse_iterator_map() {}

        reference operator*() const { return this->_begin->pair; }

        bool operator!=(const reverse_iterator_map<Category, T, notconst_T> &other) const
        {
            return this->_begin != other._begin;
        }

        bool operator==(const reverse_iterator_map<Category, T, notconst_T> &other) const
        {
            return this->_begin == other._begin;
        }

        pointer operator->() const
        {
            if (this->_begin == nullptr)
                return nullptr;
            return &(operator*)();
        }

        reverse_iterator_map &operator++()
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

        reverse_iterator_map &operator--()
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

        reverse_iterator_map operator++(int)
        {
            reverse_iterator_map tmp = *this;
            ++*this;
            return tmp;
        }
        reverse_iterator_map operator--(int)
        {
            reverse_iterator_map tmp = *this;
            --*this;
            return tmp;
        }

    private:
        Node *_begin;
        Node *_end;
        key_compare _comp;
    };

    template <class Category, class T, class Distance = ptrdiff_t, class Reference = T &, class Pointer = T *>
    class reverse_iterator_vec
    {
    private:
        T *_ptr;

    public:
        typedef T value_type;
        // typedef Pointer   						Pointer;
        typedef Category iterator_category;
        typedef Reference reference;
        typedef Distance difference_type;
        reverse_iterator_vec(T *ptr)
        {
            _ptr = ptr;
        }
        reverse_iterator_vec(const reverse_iterator_vec &other)
        {
            _ptr = other._ptr;
        }
        virtual ~reverse_iterator_vec(){};
        reverse_iterator_vec &operator=(const reverse_iterator_vec &other)
        {
            _ptr = other._ptr;
            return *this;
        }
        reverse_iterator_vec &operator++()
        {
            _ptr++;
            return *this;
        }
        reverse_iterator_vec &operator--()
        {
            _ptr--;
            return *this;
        }
        reverse_iterator_vec operator++(int)
        {
            reverse_iterator_vec tmp(*this);
            _ptr--;
            return tmp;
        }
        reverse_iterator_vec operator--(int)
        {
            reverse_iterator_vec tmp(*this);
            _ptr++;
            return tmp;
        }
        bool operator==(const reverse_iterator_vec &other) const
        {
            return _ptr == other._ptr;
        }
        bool operator!=(const reverse_iterator_vec &other) const
        {
            return _ptr != other._ptr;
        }
        reverse_iterator_vec &operator+(int i)
        {
            _ptr += i;
            return *this;
        }
        reverse_iterator_vec &operator-(int i)
        {
            _ptr -= i;
            return *this;
        }
        bool operator<(const reverse_iterator_vec &other) const
        {
            return _ptr < other._ptr;
        }
        bool operator>(const reverse_iterator_vec &other) const
        {
            if (_ptr < other._ptr)
                return false;
            return true;
        }
        bool operator<=(const reverse_iterator_vec &other) const
        {
            return _ptr <= other._ptr;
        }
        bool operator>=(const reverse_iterator_vec &other) const
        {
            return _ptr >= other._ptr;
        }
        friend reverse_iterator_vec operator-(difference_type n, const reverse_iterator_vec &it)
        {
            return vector_iterator(it._ptr - n);
        }
        friend difference_type operator-(const reverse_iterator_vec &a, const reverse_iterator_vec &b)
        {
            return (a._ptr - b._ptr);
        }
        // friend bool 	operator> (const reverse_iterator_vec& lhs, const reverse_iterator_vec& rhs) { return lhs._ptr > rhs._ptr; }
        T &operator*()
        {
            return *_ptr;
        }
        T *operator->()
        {
            return &(operator*)();
        }
    };
}