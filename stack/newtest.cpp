#include <iostream>
#include "map.hpp"
#include "iterators.hpp"
#include "../utils/pair.hpp"

// int     main(){
// ft::map<int, int> m;
// m.insert(ft::pair<int, int>(1, 1));   // first constructor of insert
// m.insert(ft::pair<int, int>(3, 3));
// ft::pair<ft::pair, int> p;
// int r = 0;
// srand (time(NULL));
// for (int i = 0; i < 100; i++){
//     r = i;
//     p = m.insert(ft::pair<int, int>(r, r));
//     std::cout << m[r] << std::endl;
// }

// // use of second constructor with iterator
// // m.insert(m.begin(), ft::pair<int, int>(2, 4));
// std::cout << m[2] << std::endl;
// std::cout << m[1] << std::endl;
// std::cout << m[3] << std::endl;
// }


int     main(){
ft::map<int, int> m;
ft::map<int, int>::iterator it;
m.insert(ft::pair<int, int>(1, 1));
m.insert(ft::pair<int, int>(1, 1));
int r = 0;
srand (time(NULL));
// for (int i = 0; i < 30; i++){
    // r = rand() % 10000;
    // m.insert(ft::pair<int, int>(r, r));
// }
    m.insert(ft::pair<int, int>(28, 28));
it = m.find(28);
m.print();
ft::map<int, int >::iterator it2 = m.begin();
it2++;
std::cout << "--------" << std::endl;
// m.erase(it);
m.print();
// std::cout << m[28] << std::endl;
std::cout << (*(m.insert(ft::pair<int, int>(28, 28)).first)).second << "***" << std::endl;
std::cout << "find 28: " << (*(it)).first << " " << (*(it)).second << std::endl;
}