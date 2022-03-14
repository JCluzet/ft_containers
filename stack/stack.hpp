/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 03:56:12 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/13 16:49:16 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
    private:
        ft::vector<T> tab;
    public:
        typedef Container container_type;
        typedef T value_type;
        explicit stack(const container_type& ctnr = container_type())
        {
            tab = ctnr;
        }
        ~stack() {};
        void push(const value_type& val) { tab.push_back(val); }
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