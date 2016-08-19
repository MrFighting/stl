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
#include "Stack.h"
using namespace std;

struct Foo {
    int i;
    int j;

    Foo(int i, int j) : i(i), j(j) { }
};

int main()
{
    std::unordered_set<int> set;
    std::unordered_set<int> st;
    set == st;
    //set.insert()
   //hashtable_test();
   // unordered_map_test();
    priority_queue_test();
}