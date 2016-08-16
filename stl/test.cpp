#include <iostream>
#include <algorithm>
#include <vector>
#include "hashtable.h"
#include <assert.h>
#include <list>
#include "Vector.h"
#include "List.h"

//
// Created by Administrator on 2016/8/3.
//
void vector_test1() {
    std::vector<int> v;
    v.insert(v.begin(), 11);
    v.push_back(3);
    v.pop_back();
    v.push_back(4);
    v.emplace(v.begin(),888);
    v.insert(v.begin()+2,6);
    v.insert(v.begin()+1,7);
    v.push_back(8);
    v.insert(v.end(), 1);
    v.insert(v.begin()+2, 2);
    v.pop_back();
    v.push_back(9);
    v.pop_back();
    v.push_back(10);
    v.push_back(1);
    v.push_back(3);
    v.insert(v.begin()+1, 2);
//--------------------------------------
    stl::Vector<int> vec;
    vec.insert(vec.begin(), 11);
    vec.push_back(3);
    vec.pop_back();
    vec.push_back(4);
    vec.emplace(vec.begin(),888);
    vec.insert(vec.begin()+2,6);
    vec.insert(vec.begin()+1,7);
    vec.push_back(8);
    vec.insert(vec.end(), 1);
    vec.insert(vec.begin()+2, 2);
    vec.pop_back();
    vec.push_back(9);
    vec.pop_back();
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

    cout << endl;
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
    cout << endl;
}

void vector_test3() {
    stl::Vector<int> vec;
    vec.resize(100);
    assert(vec.size() == 100);
    vec.resize(0);
    assert(vec.size() == 0);


    stl::Vector<int> v;
    std::cout << "Default-constructed capacity is " << v.capacity() << '\n';
    v.resize(100);
    assert(v.size() == 100);
    std::cout << "Capacity of a 100-element vector is " << v.capacity() << '\n';
    v.clear();
    assert(v.size() == 0);
    std::cout << "Capacity after clear() is " << v.capacity() << '\n';
    v.shrink_to_fit();
    assert(v.capacity() == 0);
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';


    stl::Vector<int> vector;
    v.push_back(1);
    stl::Vector<int>().swap(v);

    assert(vector.size() == 0 && vector.capacity() == 0);
    cout << endl;
}

void list_test1() {
    stl::List<int> l1{1,2,3,4,5};

    for (auto i : l1) {
        cout << i << " ";
    }
    cout << endl;
    std::list<int> sl1{1,2,3,4,5};

    assert(l1 == stl::List<int>(sl1.begin(), sl1.end()));

    stl ::List<int> l2(l1);
    assert(l1 == l2);

    l1.push_back(6);
    l1.pop_back();
    assert(l1 == l2);

    l1.push_back(7);
    l1.push_back(8);
    l1.push_back(9);
    assert(l1 == stl::List<int>({1,2,3,4,5,7,8,9}));

    l1.pop_back();
    l1.pop_back();
    l1.pop_back();
    assert(l1 == l2);

    //--------------------------
    l1.push_font(6);
    l1.pop_front();
    assert(l1 == l2);

    l1.push_font(7);
    l1.push_font(8);
    l1.push_font(9);
    assert(l1 == stl::List<int>({9,8,7,1,2,3,4,5}));

    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    assert(l1 == l2);
    //------------------------------insert测试
    auto it = std::find(l1.begin(), l1.end(),3);
    l1.insert(it, 6);
    for (auto i : l1) {
        cout << i << " ";
    }
    cout << endl;
    auto it2 = std::find(l1.begin(), l1.end(), 4);
    int a[]{5,2,0,1,3,1,4};
    cout<< *l1.insert(it2, begin(a), end(a))<< endl;
    for (auto i : l1) {
        cout << i << " ";
    }
    cout << endl;
    auto it3 = std::find(l1.begin(), l1.end(), 5);
    cout<< *l1.insert(l1.end(), begin(a), end(a))<< endl;
    for (auto i : l1) {
        cout << i << " ";
    }
    cout << endl;
    //------------------resize
    stl::List<int> l3{1,2,3,4,5};
    auto sz = l1.size();
    l1.resize(3);
    for (auto i : l1) {
        cout << i << " ";
    }
    cout << endl;
    l1.resize(20);
    for (auto i : l1) {
        cout << i << " ";
    }
    cout << endl;
    //--------------swap
    stl::List<int> l4{1,2,3};
    stl::List<int> l5{4,5,6};

    auto it4 = l1.begin();
    auto it5 = l2.begin();

    l4.swap(l5);
   // cout << *it4;
    //cout << *l4.begin();

    //------------------erase
    stl::List<int> l6{1,2,3,4,5,6};
    auto iter = std::find(l6.begin(), l6.end(),3);
    l6.erase(iter);
    auto iter2 = std::find(l6.begin(), l6.end(),2);
    l6.erase(iter2, l6.end());
    for (auto i : l6) {
        cout << i << " ";
    }
    cout << endl;
    //-------------------merge
    stl::List<int> l7{1,5,8,10,12,15};
    stl::List<int> l8{2,6,7,12,14,17};
    stl::List<int> ll{1,2,3,4};
    stl::List<int> ll1{5,6,7,8};
    ll.merge(ll1);
    for (auto i : l7) {
        cout << i << " ";
    }
    cout << endl;
    //-------------------transfer
    l7.transfer(l7.end(),l8.begin(),l8.end());
    for (auto i : l7) {
        cout << i << " ";
    }
    cout << endl;
    assert(l7 == stl::List<int>({1,5,8,10,12,15,2,6,7,12,14,17}));
    assert(l8 == stl::List<int>());
    auto ite = std::find(l7.begin(), l7.end(), 15);
    l7.transfer(l7.begin(), ite, l7.end());
    assert(l7 == stl::List<int>({15,2,6,7,12,14,17,1,5,8,10,12}));
    for (auto i : l7) {
        cout << i << " ";
    }
    cout << endl;
    //-------------------spice
    ll.splice(++ll.begin(),l7);
    for (auto i : ll) {
        cout << i << " ";
    }
    cout << endl;
    //-------------------reverse
    stl::List<int> rlist{1,2,3,4,5,6};
    rlist.reverse();
    assert(rlist == stl::List<int>({6,5,4,3,2,1}));
    rlist.reverse();
    assert(rlist == stl::List<int>({1,2,3,4,5,6}));
    //-------------------unique
    stl::List<int> ulist{1, 2, 2, 3, 3, 2, 1, 1, 2};
    ulist.unique();
    assert(ulist == stl::List<int>({1, 2, 3, 2, 1, 2}));
    stl::List<int> u2list{1,1,1,1,1,1};
    u2list.unique();
    stl::List<int> u;
    u.push_back(1);
    assert(u2list ==stl::List<int>({1}) && u2list == u );
    //-------------------sort
    stl::List<int> slist{5,4,3,2,1};
    slist.sort();
    for (auto i : slist) {
        cout << i << " ";
    }
    cout << endl;
    stl::List<int> s2list{1,2,3,4,5};
    assert(slist == s2list);
    s2list.sort();
    for (auto i : s2list) {
        cout << i << " ";
    }
    cout << endl;
}
template <typename T>
struct _equal {
    bool operator()(const T& i, const T&j)const {
        return i==j;
    }
};
template <typename T>
struct ident {
    const T& operator()(const T& val) const {
        return val;
    }
};
void hashtable_test() {
    typedef Hashtable<int, int,hash<int>,_equal<int>,ident<int>> hashtable;
    Hashtable<int, int,hash<int>,_equal<int>,ident<int>> ht(0, _equal<int>(),hash<int>() ,ident<int>());
    ht.insert_unique(1);
    ht.insert_unique(1);
    ht.insert_unique(2);
    //ht.resize(50);
    ht.insert_unique(3);
    auto i1 = ht.insert_unique(4);
    auto i2 = ht.insert_unique(59);
    auto i3 = ht.insert_unique(44);
    cout << ht.size() << endl;
    auto beg = ht.begin();
    for (int i = 0; i < ht.size(); i++) {
        cout << *beg++  << " ";
    }
    ht.resize(1200);
    auto beg2 = ht.begin();
    cout << endl;
    for (int i = 0; i < ht.size(); i++) {
        cout << *beg2++  << " ";
    }
   hashtable htt(0, _equal<int>(),hash<int>() ,ident<int>());
    htt.insert_unique(5);
    htt.insert_unique(2);
    htt.insert_equal(2);
    htt.insert_unique(3);
    htt.insert_unique(111);
    htt.insert_unique(56);
    htt.insert_unique(22);
    htt.insert_equal(22);
    auto beg3 = htt.begin();
    cout << endl;
    for (int i = 0; i < htt.size(); i++) {
        cout << *beg3++  << " ";
    }
    cout<<endl;
    ht.copy_from(&htt);
    auto beg4 = ht.begin();
    for (int i = 0; i < ht.size(); i++) {
        cout << *beg4++  << " ";
    }
    cout <<endl;
    hashtable ht1(htt);
    auto beg5 = ht1.begin();
    for (int i = 0; i < ht1.size(); i++) {
        cout << *beg5++  << " ";
    }
    cout <<endl;
    //----------------erase
    auto it = find(ht1.begin(), ht1.end(), 22);
    ht1.erase(it);
    auto it1 = find(ht1.begin(), ht1.end(), 111);
    ht1.erase(it1);
    ht1.erase(find(ht1.begin(), ht1.end(), 2));
    ht1.erase(find(ht1.begin(), ht1.end(), 2));
    auto beg6 = ht1.begin();
    for (int i = 0; i < ht1.size(); i++) {
        cout << *beg6++  << " ";
    }
    cout <<endl;
    auto end = htt.begin();
    advance(end, 3);
    htt.erase(htt.begin(),end);
    auto beg7 = htt.begin();
    for (int i = 0; i < htt.size(); i++) {
        cout << *beg7++  << " ";
    }
    cout <<endl;
    //-------------------swap
    htt.swap(ht1);
    auto beg8 = htt.begin();
    for (int i = 0; i < htt.size(); i++) {
        cout << *beg8++  << " ";
    }
    cout << endl;
    //-------------count
    htt.insert_equal(3);
    htt.insert_equal(3);
    htt.insert_equal(3);
    cout << htt.count(3) << endl;
    //---------------equal_range and find
    auto pair = htt.equal_range(3);
    for (auto beg = pair.first; beg != pair.second;) {
        cout << *beg++ << " ";
    }
    auto pair1 = htt.equal_range(110);
    assert(pair1.first == htt.end() && pair1.second == htt.end());
    cout << *pair.second;
    cout << endl;
}