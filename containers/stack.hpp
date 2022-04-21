/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 03:56:12 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/21 14:02:03 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
    public:
        typedef Container	container_type;
		typedef	T			value_type;
		typedef size_t		size_type;
    protected:
        container_type _container;
    public:
        explicit stack(const container_type& ctnr = container_type())
        {
            _container = ctnr;
        }
        ~stack() {};
        void push(const value_type& val) { _container.push_back(val); }
        void pop() { _container.pop_back(); }
        value_type &top() { return _container.back(); }
        value_type &top() const { return _container.back(); }
        size_type size() { return _container.size(); }
        bool empty() { return _container.empty(); }

        // OPERATOR OVERLOADING
        bool operator==(const stack &rhs) const
        {
            return _container == rhs._container;
        }
        bool operator!=(const stack &rhs) const
        {
            return _container != rhs._container;
        }
        bool operator<(const stack &rhs) const
        {
            return _container < rhs._container;
        }
        bool operator>(const stack &rhs) const
        {
            return _container > rhs._container;
        }
        bool operator<=(const stack &rhs) const
        {
            return _container <= rhs._container;
        }
        bool operator>=(const stack &rhs) const
        {
            return _container >= rhs._container;
        }
    };
}