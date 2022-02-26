/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:25 by jcluzet           #+#    #+#             */
/*   Updated: 2022/02/26 22:39:01 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>

// create the vector class, is a copy of std::vector

namespace ft
{

template <typename T>
class Vector 
{
    private:
        T *tab;
        unsigned int _size;
        unsigned int _capacity;
    public:
        Vector() {
            _size = 0;
            _capacity = 1;
            resize(0);
        };
        ~Vector() {
            delete [] tab;
        };
        void push_back(T i) {
            if (_size == _capacity)
                resize(++_capacity);
            tab[_size] = i;
            _size++;
        }
        void pop_back() {
            if (_size == 0)
                return;
            _size--;
            if (_size < _capacity / 4)
                resize(_capacity / 2);
        }
        T back() {
            return tab[_size - 1];
        }
        unsigned int size() {
            return _size;
        }
        bool empty() {
            return _size == 0;
        }
        void resize(unsigned int new_capacity) {
            T *new_tab = new T[new_capacity];
            for (unsigned int i = 0; i < _size; i++)
                new_tab[i] = tab[i];
            delete[] tab;
            tab = new_tab;
            _capacity = new_capacity;
            //std::cout << "resize is now " << new_capacity << std::endl;
        }
};
}