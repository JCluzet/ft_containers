/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 03:56:12 by jcluzet           #+#    #+#             */
/*   Updated: 2022/02/20 23:24:14 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "vector.hpp"

// create the stack class, is a copy of std::stack

namespace ft 
{

template <typename T>
class Stack
{
    private:
        ft::Vector<T> tab;
    public:
        Stack() {};
        ~Stack() {};
        void push(T i) {
            tab.push_back(i);
        }
        void pop() {
            tab.pop_back();
        }
        int top() {
            return tab.back();
        }
        int size() {
            return tab.size();
        }
        bool empty() {
            return tab.empty();
        }
};

}