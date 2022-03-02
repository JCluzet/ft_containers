/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 03:56:12 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/02 16:36:12 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"

namespace ft
{
    template <typename T>
    class stack
    {
    private:
        ft::vector<T> tab;

    public:
        stack() {};
        ~stack() {};
        void push(T i) { tab.push_back(i); }
        void pop() { tab.pop_back(); }
        int top() { return tab.back(); }
        int size() { return tab.size(); }
        bool empty() { return tab.empty(); }

        // OPERATOR OVERLOADING
        bool operator==(const stack &rhs) const
        {
            return tab == rhs.tab;
        }
        bool operator!=(const stack &rhs) const
        {
            return tab != rhs.tab;
        }
        bool operator<(const stack &rhs) const
        {
            return tab < rhs.tab;
        }
        bool operator>(const stack &rhs) const
        {
            return tab > rhs.tab;
        }
        bool operator<=(const stack &rhs) const
        {
            return tab <= rhs.tab;
        }
        bool operator>=(const stack &rhs) const
        {
            return tab >= rhs.tab;
        }
    };
}