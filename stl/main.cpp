#include <iostream>
#include <vector>
#include <list>
#include "Vector.h"
#include "List.h"
#include <unordered_map>
#include <unordered_set>
#include "Unorded_Set.h"
#include "test.h"
#include "Unorderd_Map.h"
#include <stack>
#include <complex>
#include <atomic>
#include <cassert>
#include "Stack.h"
#include "Memory.h"
using namespace std;

struct Foo {
    int i;
    int j;

    Foo(int i, int j) : i(i), j(j) { }
};

int main() {
//    std::unordered_set<int> set;
//    std::unordered_set<int> st;
//    set == st;
//    //set.insert()
//    //hashtable_test();
//    // unordered_map_test();
//    unique_ptr_test();
//    shared_ptr
    shared_ptr_test();
}