#include "ft_main.hpp"

int main()
{
    //insert 
    vector<int> s2(4, 2);

    // insert value 1x value 0 at position iterator
    vector<int>::iterator it = s2.begin() + 1;
    s2.insert(it, 1, 0);
    print_vec(s2);

    std::cout << std::endl;

    // insert value 9 at position iterator
    vector<int> s3(5,2);
    vector<int>::iterator it2 = s3.begin() + 1;
    s3.insert(it2, 9);
    print_vec(s3);

    std::cout << std::endl;

    // using insert(iterator, first, last)
    vector<int> s4(5,2);
    vector<int>::iterator it3 = s4.begin() + 1;
    s4.insert(it3, s3.begin(), s3.end());
    print_vec(s4);

    std::cout << std::endl;

    // test insert with all possible positions
    s2.insert(s2.begin(), 1);
    s2.insert(s2.begin() + 1, 2);
    s2.insert(s2.begin() + 2, 212121);
    s2.insert(s2.begin(), s2.begin(), s2.end());
    
    print_vec(s2);

    // erase
    s2.erase(s2.begin() + 1);
    print_vec(s2);


    // map insert & erase
    map<int, int> m;
    m.insert(pair<int, int>(1, 1));

    m.insert(pair<int, int>(2, 2));
    map<int, int>::iterator it4 = m.begin();
    // m.erase(it4);
    for (it4 = m.begin(); it4 != m.end(); it4++)
        std::cout << it4->first << " " << it4->second << std::endl;

    std::cout << std::endl;
    m.insert(pair<int, int>(3, 3));
    m.erase(m.begin());
    for (it4 = m.begin(); it4 != m.end(); it4++)
        std::cout << it4->first << " " << it4->second << std::endl;


    // stack test insert & erase
    stack<int> s;
    s.push(1);
    s.push(2);

    s.push(3);
    s.pop();
    // for (it4 = s.begin(); it4 != s.end(); it4++)
    //     std::cout << it4->first << " " << it4->second << std::endl; // non iterable
    std::cout << s.top() << std::endl;   
    
    return(0);
}