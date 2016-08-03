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

    vector<int> c;
    vector_test1();
    vector_test2();
    vector_test3();

}