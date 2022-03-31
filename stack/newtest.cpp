#include <iostream>
#include "map.hpp"
#include <map>

int main()
{
    ft::map<int,int> s1;
    // ft::pair<iterator,bool> p;
    std::cout << "size: " << s1.size() << std::endl;


    s1.insert(ft::pair<int,int>(1,1));
    s1.insert(ft::pair<int,int>(2,2));
    s1.insert(ft::pair<int,int>(3,3));

    s1[4] = 4;

    s1.print();

    // unsigned int i = 0;
    // while(1)
    // {
    //     std::cout << " Insert the key :";
    //     std::cin >> i;
    //     // output the value of the iterator in pair, catch from insert function

    //     s1.insert(ft::pair<int, int>(i, i));

    //     std::cout << "size: " << s1.size() << std::endl;

    //     std::cout << "Do you want to erase the key ? (y/n) :";
    //     char c;
    //     std::cin >> c;
    //     if (c == 'y')
    //     {
    //         std::cout << "Enter the key to erase :";
    //         std::cin >> i;
    //         // s1.clear();
    //         // s1.erase(i);
    //         std::cout << "size: " << s1.size() << std::endl;
    //     }

    //     system("clear");
    //     s1.print();
    //     i++;
    // }
    // std::cout << "size: " << s1.size() << std::endl;
}