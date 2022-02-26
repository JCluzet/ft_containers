/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:42:30 by jcluzet           #+#    #+#             */
/*   Updated: 2022/02/26 22:38:15 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include "stack/stack.hpp"

int main(void)
{
    std::cout << "STD::stack :" << std::endl;
    std::stack<int> s1;
    std::cout << s1.empty() << std::endl;
    s1.push(3);

    std::cout << s1.top() << std::endl;
    s1.push(2);
    std::cout << s1.top() << std::endl;
    s1.push(3);
    s1.push(4);
    s1.top();
    s1.pop();
    s1.top();
}