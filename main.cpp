/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:30 by jcluzet           #+#    #+#             */
/*   Updated: 2022/02/20 23:19:11 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include "stack/stack.hpp"

int main(void)
{
    std::cout << "OFFICIAL STACK :" << std::endl;
    std::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    for (unsigned int i = 0; i < s.size(); i++)
        std::cout << s.top() << std::endl;
    
    std::cout << "MY STACK :" << std::endl;
    ft::Stack<int> s2;
    s2.push(1);
    s2.push(2);
    s2.push(3);

    for (int i = 0; i < s2.size(); i++)
        std::cout << s2.top() << std::endl;
}