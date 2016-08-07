#include <iostream>
#include <vector>
#include <list>
#include "Vector.h"
#include "test.h"
#include "List.h"

using namespace std;

struct Foo {
    int i;
    int j;

    Foo(int i, int j) : i(i), j(j) { }
};

int main() {
    std::list<int> l;
   // l.unique()
//    int a[] = {4,5,6};
//    //list_test1();
//    stl::List<int> l{1,2};
//    l.insert(l.end(), begin(a), end(a));
//    for (auto i : l) {
//        cout << i << " ";
//    }
//    cout << endl;
    list_test1();

}