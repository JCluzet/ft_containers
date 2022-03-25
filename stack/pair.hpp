/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:20:21 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/24 22:45:57 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
namespace ft
{
    template <class T1, class T2>
    class Pair
    {
    public:
        Pair(T1 first, T2 second) : _first(first), _second(second) {}
        Pair(const Pair &other) : _first(other._first), _second(other._second) {}
        ~Pair() {}
        Pair &operator=(const Pair &other)
        {
            _first = other._first;
            _second = other._second;
            return *this;
        }
        T1 first() const { return _first; }
        T2 second() const { return _second; }

    private:
        T1 _first;
        T2 _second;
    };
}
