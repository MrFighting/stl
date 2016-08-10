#include <iostream>
#include <vector>
#include <list>
#include "Vector.h"
#include "List.h"
#include <unordered_map>
#include <unordered_set>
#include "test.h"


using namespace std;

struct Foo {
    int i;
    int j;

    Foo(int i, int j) : i(i), j(j) { }
};


typedef std::unordered_set<char> Myset;
int main()
{
    Myset c1;
    Myset.equal_range()
    c1.insert('a');
    c1.insert('a');
    c1.insert('c');

// display contents " [c] [b] [a]"
    for (Myset::const_iterator it = c1.begin();
         it != c1.end(); ++it)
        std::cout << " [" << *it << "]";
    std::cout << std::endl;

// display results of failed search
    std::pair<Myset::iterator, Myset::iterator> pair1 =
            c1.equal_range('a');
    std::cout << "equal_range('a'):";
    for (; pair1.first != pair1.second; ++pair1.first)
        std::cout << " [" << *pair1.first << "]";
    std::cout << std::endl;

// display results of successful search
    pair1 = c1.equal_range('b');
    std::cout << "equal_range('b'):";
    for (; pair1.first != pair1.second; ++pair1.first)
        std::cout << " [" << *pair1.first << "]";
    std::cout << std::endl;

    return (0);
}