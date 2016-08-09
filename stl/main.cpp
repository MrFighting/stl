#include <iostream>
#include <vector>
#include <list>
#include "Vector.h"
#include "List.h"
#include <unordered_map>
#include "test.h"


using namespace std;

struct Foo {
    int i;
    int j;

    Foo(int i, int j) : i(i), j(j) { }
};


int main() {
    //unordered_map
//    std::vector<int> s;
//    s.push_back(1);
//    s.push_back(2);
//    cout << s.capacity() << endl;
//    s = std::vector<int>();
//    cout << s.capacity() << endl;
//
//
//    stl::Vector<int> s1;
//    s1.push_back(1);
//    s1.push_back(2);
//    cout << s1.capacity() << endl;
//    s1 = stl::Vector<int>();
//    cout << s1.capacity() << endl;
//    return 0;
    hashtable_test();
}