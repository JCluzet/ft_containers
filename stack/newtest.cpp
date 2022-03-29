#include <iostream>
#include "map.hpp"
#include <map>

int main()
{
    // create a map
    std::map<int, int> myMap;
    ft::map<int, int> myMap2;
    
    // create a Tree
    ft::Tree<int> myTree;

    while(1)
    {
        std::cout << "Enter a number: ";
        int number;
        std::cin >> number;
        myTree.insert(number);
        system("clear");
        myTree.print2D();
    }

    myMap.insert(std::pair<int, int>(1, 10));
    myMap.insert(std::pair<int, int>(2, 20));
    myMap.insert(std::pair<int, int>(2, 30));
}