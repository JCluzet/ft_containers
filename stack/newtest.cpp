#include <iostream>
#include "map.hpp"
#include <map>

int main()
{
    // create a map
    std::map<int, int> myMap;
    ft::map<int, int> myMap2;
    
    // create a Tree
    ft::Tree<int, int> myTree;

    // test size
    std::cout << "size: " << myMap2.size() << std::endl;
    std::cout << "max_size: " << myMap2.max_size() << std::endl;

    // myMap2._tree.print2D();

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