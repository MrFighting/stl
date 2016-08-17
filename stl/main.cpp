#include <iostream>
#include <vector>
#include <list>
#include "Vector.h"
#include "List.h"
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include "Unorded_Set.h"
#include <Hashtable.h>
#include "test.h"
using namespace std;

struct Foo {
    int i;
    int j;

    Foo(int i, int j) : i(i), j(j) { }
};

int main()
{
    std::unordered_set<int> set;
    //set.insert()
   //hashtable_test();
    unordered_set_test();
}