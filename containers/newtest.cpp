#include <iostream>
// #include "MapIte.hpp"
#include "map.hpp"
#include <map>
#include "../utils/pair.hpp"

// using namespace ft;
using namespace ft;

int     main(){
    map<int, int> m;
    map<int, int>::iterator it;
    int i = 15;
    m.insert(pair<int, int>(i, i));
    i = 14;
    m.insert(pair<int, int>(i, i));           // ICI 1
    i = 15;
    m.insert(pair<int, int>(i, i));
    i = 16;
    m.insert(pair<int, int>(i, i));
    i = 37;
    m.insert(pair<int, int>(i, i));
    i = 18;
    m.insert(pair<int, int>(i, i));
    i = 40;
    m.insert(pair<int, int>(i, i));
    it = m.begin();
    // m.print();
    std::cout << "it = " << it->first << ":" << it->second << std::endl;
    std::string in;
    // while(1){
        std::getline(std::cin, in);
        if (in == "+")
            it++;
        // if (in == "-")
            // it--;
        // m.print();
        std::cout << "it = " << it->first << ":" << it->second << std::endl;
    // }
}