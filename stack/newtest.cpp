#include <iostream>
// #include "map.hpp"
#include "map.hpp"

// int main()
// {

//     // Tree Tree;
//     ft::map<int> Tree;
//     std::string input;
//     while (1)
//     {
//         std::cout << "Enter values to insert in the tree : " << std::endl;
//         std::cin >> input;
//         Tree.insert(std::stoi(input));
//         // system("clear");
//         Tree.print2D();
//     }
//     // Tree->preorder_print();
//     // Tree->inorder_print();
//     // Tree->postorder_print();

//     // delete Tree;
//     return (0);
// }

#include <map>

int main()
{
    // create a map
    std::map<int, int> myMap;
    ft::map<int, int> myMap2;

    // ft::map<int, int> myMap2;
    // myMap.insert(1);
    // insert elements in the map
    myMap.insert(std::pair<int, int>(1, 10));
    myMap.insert(std::pair<int, int>(2, 20));
    myMap.insert(std::pair<int, int>(2, 30));

    // print the map
    // myMap.print2D();
    // std::cout << "The map contains: ";
    // for (std::map<int, int>::iterator it = myMap.begin(); it != myMap.end(); ++it)
    //     std::cout << '(' << it->first << ',' << it->second << ") ";
    // std::cout << '\n';

    
}