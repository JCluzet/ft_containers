#include <iostream>
#include "map.hpp"
#include "../utils/pair.hpp"

int     main(){
ft::map<int, int> m;
m.insert(ft::pair<int, int>(1, 1));
m.insert(ft::pair<int, int>(1, 1));
int r = 0;
srand (time(NULL));
for (int i = 0; i < 10010000; i++){
    r = rand() % 10000;
    m.insert(ft::pair<int, int>(r, r));
    // std::cout << "**" << i << "**" << std::endl;
}
m.print();
}