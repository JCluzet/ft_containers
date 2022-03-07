/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:30 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/06 21:59:09 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <vector>
#include "stack/stack.hpp"
#include "stack/vector.hpp"

int main()
{
    ft::vector<int> s1;

    s1.push_back(1);
    s1.push_back(2);
    s1.push_back(3);
    s1.push_back(4);

//     // fill constructor
    ft::vector<int> s4(10, 2);
    ft::vector<int>::iterator p1 = s4.begin();
    ft::vector<int>::iterator p2 = s4.end();
    while (p1 != p2)
    {
        std::cout << *p1 << std::endl;
        p1++;
    }
    std::cout << std::endl;



    // use of iterator
    ft::vector<int>::iterator it = s1.begin();
    ft::vector<int>::iterator it2 = s1.end();
    while (it != it2)
    {
        std::cout << *it << std::endl;
        it++;
    }

    //copy constructor
    ft::vector<int> s2(s1);
    ft::vector<int>::iterator itr = s2.begin();
    ft::vector<int>::iterator it2r = s2.end();
    while (itr != it2r)
    {
        std::cout << *itr << std::endl;
        itr++;
    }

//     // range constructor
    ft::vector<int> s3(s1.begin(), s1.end());
    ft::vector<int>::iterator it3 = s3.begin();
    ft::vector<int>::iterator it4 = s3.end();
    while (it3 != it4)
    {
        std::cout << *it3 << std::endl;
        it3++;
    }


}