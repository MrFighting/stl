#include <iostream>
#include <vector>
#include <assert.h>
#include "Vector.h"
//
// Created by Administrator on 2016/8/3.
//
void vector_test1() {
    std::vector<int> v;
    std::vector<int> v2;
    v.insert(v.begin(), 11);
    v.push_back(3);
    //v.insert(v.end(), 1);
    v.push_back(4);
    v.insert(v.begin()+2,6);
    v.insert(v.begin()+1,7);
    v.push_back(8);
    v.insert(v.end(), 1);
    v.insert(v.begin()+2, 2);
    v.push_back(9);
    v.push_back(10);
//    cout <<v.capacity() << endl;
//    v.insert(v.end(),1);
//    cout <<v.capacity() << endl;
//
//    v.insert(v.end(),2);
//    cout <<v.capacity() << endl;
//
//    v.insert(v.end(),3);
//    cout <<v.capacity() << endl;
    v.push_back(1);
    v.push_back(3);
    auto it = v.insert(v.begin()+1, 2);

    stl::Vector<int> vec;
    vec.insert(vec.begin(), 11);

    vec.push_back(3);
    //v.insert(v.end(), 1);
    vec.push_back(4);
    vec.insert(vec.begin()+2,6);
    vec.insert(vec.begin()+1,7);
    vec.push_back(8);
    vec.insert(vec.end(), 1);
    vec.insert(vec.begin()+2, 2);
    vec.push_back(9);
    vec.push_back(10);
    vec.push_back(1);
    vec.push_back(3);
    vec.insert(vec.begin()+1, 2);

    for (int j = 0; j < v.size(); ++j) {
        std::cout << v[j] << " ";
    }
    std::cout << std::endl;
    for (int j = 0; j < v.size(); ++j) {
        std::cout << vec[j] << " ";
    }

    stl::Vector<int> temp(v.begin(), v.end());
    assert(temp == vec);
}

void vector_test2() {
    int a[] = {11,23,45,82,16,7};

    vector<int> vector1;
    vector1.push_back(1);
    vector1.insert(vector1.begin(), 2);
    vector1.insert(vector1.begin(), begin(a), end(a));
    vector1.insert(vector1.end(), begin(a), end(a));
    vector1.insert(vector1.begin()+5, begin(a), begin(a) + 3);

    stl::Vector<int> vector2;
    vector2.push_back(1);
    vector2.insert(vector2.begin(), 2);
    vector2.insert(vector2.begin(), begin(a), end(a));
    vector2.insert(vector2.end(), begin(a), end(a));
    vector2.insert(vector2.begin()+5, begin(a), begin(a) + 3);

    for (int i = 0; i < vector1.size(); i++) {
        cout << vector1[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < vector2.size(); i++) {
        cout << vector2[i] << " ";
    }
    stl::Vector<int> temp(vector1.begin(), vector1.end());
    assert(temp == vector2);
}