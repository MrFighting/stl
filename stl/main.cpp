#include <iostream>
#include <vector>
#include <list>
#include "Vector.h"
#include "test.h"

using namespace std;

struct Foo {
    int i;
    int j;

    Foo(int i, int j) : i(i), j(j) { }
};

int main() {

    vector<Foo> c;
    c.push_back(Foo(1,2));
    c.push_back(Foo(3,4));
    auto it = c.begin();
    auto end = c.end() - 1;
    c.erase(c.begin(), c.end());
    cout << it->i << " " << it->j<<endl;
    cout << end->i << " " << end->j<<endl;

//    vector_test1();
//    vector_test2();
//    vector_test3();

}