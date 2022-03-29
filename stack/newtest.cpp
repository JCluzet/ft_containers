#include <iostream>
#include "map.hpp"
#include <map>

int main()
{
    // create a map
    std::map<int, int> myMap;
    ft::map<int, int> myMap2;
    
    // create a Tree
    ft::pair<int, int> p1(1, 1);
    ft::Tree<ft::pair<int, int> > myTree;

    // test size
    std::cout << "size: " << myMap2.size() << std::endl;
    std::cout << "max_size: " << myMap2.max_size() << std::endl;

    // myMap2._tree.print2D();

    unsigned int i = 0;

    while(1)
    {
        // std::cout << "Enter a number: ";
        p1.first = i;
        p1.second = i;
        // int number;
        // std::cin >> number;
        myTree.insert(p1);
        system("clear");
        myTree.print2D();
        i++;
    }

    myMap.insert(std::pair<int, int>(1, 10));
    myMap.insert(std::pair<int, int>(2, 20));
    myMap.insert(std::pair<int, int>(2, 30));
}