/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:30 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/06 17:17:40 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <vector>
#include "stack/stack.hpp"
#include "stack/vector.hpp"

// int main(void)
// {
//     std::stack<int> s1;
//     std::cout << s1.empty() << std::endl;
//     s1.push(3);

//     std::cout << s1.top() << std::endl;
//     s1.push(2);
//     std::cout << s1.top() << std::endl;
//     s1.push(3);
//     s1.push(4);
//     s1.top();
//     s1.pop();
//     s1.top();

//     std::vector<int> v1;
//     std::cout << v1.empty() << std::endl;
//     v1.push_back(3);
//     v1.push_back(2);
//     v1.push_back(3);
//     v1.push_back(4);
//     v1.pop_back();
//     std::cout << "HERE" << std::endl;
    
//     for (unsigned long int i = 0; i < v1.size(); i++)
//         std::cout << v1[i] << std::endl;
// }

int main()
{
    std::vector<int> s1;

    s1.push_back(1);
    s1.push_back(2);
    s1.push_back(3);
    s1.push_back(4);

    // fill constructor
    std::vector<int> s4(10, 2);
    std::vector<int>::iterator p1 = s4.begin();
    std::vector<int>::iterator p2 = s4.end();
    while (p1 != p2)
    {
        std::cout << *p1 << std::endl;
        p1++;
    }
    std::cout << std::endl;



    // use of iterator
    std::vector<int>::iterator it = s1.begin();
    std::vector<int>::iterator it2 = s1.end();
    while (it != it2)
    {
        std::cout << *it << std::endl;
        it++;
    }

    // copy constructor
    std::vector<int> s2(s1);
    std::vector<int>::iterator itr = s2.begin();
    std::vector<int>::iterator it2r = s2.end();
    while (itr != it2r)
    {
        std::cout << *itr << std::endl;
        itr++;
    }

    // range constructor
    std::vector<int> s3(s1.begin(), s1.end());
    std::vector<int>::iterator it3 = s3.begin();
    std::vector<int>::iterator it4 = s3.end();
    while (it3 != it4)
    {
        std::cout << *it3 << std::endl;
        it3++;
    }
}
