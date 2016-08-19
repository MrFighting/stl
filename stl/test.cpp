
//
// Created by Administrator on 2016/8/3.
//
#include "test.h"
#include <iostream>
#include <algorithm>
#include "hashtable.h"
#include <assert.h>
#include <list>
#include <queue>
#include "Vector.h"
#include "List.h"
#include "Unorded_Set.h"
#include "Unorderd_Map.h"
#include "Priority_Queue.h"

using  namespace std;
using namespace stl;
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
void vector_test() {
    vector_test1();
    vector_test2();
    vector_test3();
}
void list_test() {
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
    //----------------rehash policy
    cout << "rehash policy--------------------------------------"<<endl;
    hashtable htab(0, _equal<int>(),hash<int>() ,ident<int>());
    for (int j = 0; j < 50000; ++j) {
        if (j % 2) {//奇数
            htab.insert_unique(j);
        }
        else
            htab.insert_equal(j);
    }
//    for (int i : htab) {
//        cout << i << " ";
//    }
    cout << endl;
    cout << "bucket size:" << htab.bucket_size() << " default max_load_fac is 1.0";
    cout << endl;
    htab.clear();
//    for (int i : htab) {
//        cout << i << " ";
//    }
    htab.max_load_factor(0.1);//set max_load_factor to 0.1
    for (int j = 0; j < 50000; ++j) {
        if (j % 2) {//奇数
            htab.insert_unique(j);
        }
        else
            htab.insert_equal(j);
    }
//    for (int i : htab) {
//        cout << i << " ";
//    }
    cout << endl;
    cout << "after bucket size:" << htab.bucket_size() << " about ten times larger";
    cout << endl;
    //------------------------
    int arr[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Unorded_Set<int> ust1(std::begin(arr), std::end(arr));
    Unorded_Set<int> ust2(std::begin(arr), std::end(arr));

    ust1.erase(9);
    auto n = ust2.erase(9);
    assert(n == 1);
    ust1.erase(7);
    auto ite = ust2.find(7);
    ite = ust2.erase(ite);
    assert(ite != ust2.end());
    assert(std::equal(ust1.begin(),ust1.end(), ust2.begin()));
}

void unordered_set_test() {
    typedef Unorded_Set<int> set;
    set s1;
    s1.insert(1);
    s1.insert(1);
    s1.insert(2);
    //ht.resize(50);
    s1.insert(3);
    auto i1 = s1.insert(4);
    auto i2 = s1.insert(59);
    auto i3 = s1.insert(44);
    cout << s1.size() << endl;
    auto beg = s1.begin();
    for (int i = 0; i < s1.size(); i++) {
        cout << *beg++  << " ";
    }
    s1.rehash(1200);
    auto beg2 = s1.begin();
    cout << endl;
    for (int i = 0; i < s1.size(); i++) {
        cout << *beg2++  << " ";
    }
    cout << endl;
    set set2;
    set2.insert(5);
    set2.insert(2);
    set2.insert(2);
    set2.insert(3);
    set2.insert(111);
    set2.insert(56);
    set2.insert(22);
    set2.insert(22);
    auto beg3 = set2.begin();
    cout << endl;
    for (int i = 0; i < set2.size(); i++) {
        cout << *beg3++  << " ";
    }
    cout<<endl;
    //----------------erase
    auto it = find(s1.begin(), s1.end(), 22);
    s1.erase(it);
    auto it1 = find(s1.begin(), s1.end(), 111);
    s1.erase(it1);
    s1.erase(find(s1.begin(), s1.end(), 2));
    s1.erase(find(s1.begin(), s1.end(), 2));
    auto beg6 = s1.begin();
    for (int i = 0; i < s1.size(); i++) {
        cout << *beg6++  << " ";
    }
    cout <<endl;
    auto end = set2.begin();
    advance(end, 3);
    set2.erase(set2.begin(),end);
    auto beg7 = set2.begin();
    for (int i = 0; i < set2.size(); i++) {
        cout << *beg7++  << " ";
    }
    cout <<endl;
    //-------------------swap
    set2.swap(s1);
    auto beg8 = set2.begin();
    for (int i = 0; i < set2.size(); i++) {
        cout << *beg8++  << " ";
    }
    cout << endl;
    //-------------count
    set2.insert(3);
    set2.insert(3);
    set2.insert(3);
    cout << set2.count(3) << endl;
    //---------------equal_range and find
    auto pair = set2.equal_range(3);
    for (auto beg = pair.first; beg != pair.second;) {
        cout << *beg++ << " ";
    }
    auto pair1 = set2.equal_range(110);
    assert(pair1.first == set2.end() && pair1.second == set2.end());
    cout << *pair.second;
    cout << endl;
    //----------------rehash policy
    cout << "rehash policy--------------------------------------"<<endl;
    set set3;
    for (int j = 0; j < 50000; ++j) {
        if (j % 2) {//奇数
            set3.insert(j);
        }
        else
            set3.insert(j);
    }
//    for (int i : htab) {
//        cout << i << " ";
//    }
    cout << endl;
    cout << "bucket size:" << set3.bucket_size() << " default max_load_fac is 1.0";
    cout << endl;
    set3.clear();
//    for (int i : htab) {
//        cout << i << " ";
//    }
    set3.max_load_factor(0.1);//set max_load_factor to 0.1
    for (int j = 0; j < 50000; ++j) {
        if (j % 2) {//奇数
            set3.insert(j);
        }
        else
            set3.insert(j);
    }
//    for (int i : htab) {
//        cout << i << " ";
//    }
    cout << endl;
    cout << "after bucket size:" << set3.bucket_size() << " about ten times larger";
    cout << endl;
}

struct eqstr {
    bool operator()(const char* lhs, const char* rhs) {
        return strcmp(lhs,rhs) == 0;
    }
};
void unordered_map_test() {

    typedef Unordered_Map<const char*, int, hash<const char*>, eqstr> map;
    map days;
    days["jan"] = 31;
    days["feb"] = 28;
    days["mar"] = 31;
    days["apr"] = 30;
    days["may"] = 31;
    days["jun"] = 30;
    days["jul"] = 31;
    days["aug"] = 31;
    days["sep"] = 30;
    days["oct"] = 31;
    days["nov"] = 30;
    days["dec"] = 31;

    cout << "september->" << days["sep"] << endl;
    cout << "june     ->" << days["jun"] << endl;
    cout << "februrary->" << days["feb"] << endl;
    cout << "december ->" << days["dec"] << endl;
    for (auto pair : days) {
        cout << pair.first << endl;
    }
}
void priority_queue_test() {
    Priority_Queue<int> pq{1,2,3,4,5};
    Priority_Queue<int> pq1;
    priority_queue<int> spq;
    int loop = 200;
    for (int i = 0; i < loop; i++) {
        pq1.push(i);
    }
    cout << endl;
    for (int j = 0; j < loop; j++) {
        assert(pq1.top() == loop - j - 1);
        pq1.pop();
    }
    cout << endl;
    //-------------make_heap
    const int arr_size = 100000;
    int arr[arr_size];
    for (int i = 0; i < arr_size; i++) {
        arr[i] = i;
    }
    Priority_Queue<int> pqx(begin(arr), end(arr));
//    for(int i : pqx) {
//        cout << i << " ";
//    }
    cout << endl;
    for (int j = 0; j < arr_size; j++) {
        assert(pqx.top() == arr_size - j - 1);
        //cout << pqx.top() << " ";
        pqx.pop();
    }
}
