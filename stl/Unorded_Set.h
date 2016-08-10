//
// Created by lee on 16-8-10.
//

#ifndef STL_UNORDED_SET_H
#define STL_UNORDED_SET_H

#include "hashtable.h"
#include <functional>

template<class Key,
        class Hash = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>>
class Unorded_Set;

template<class Key, class Hash, class KeyEqual, class Allocator>

bool operator==(const Unorded_Set <Key, Hash, KeyEqual> &lhs,
                const Unorded_Set <Key, Hash, KeyEqual> &rhs);

template<class Key, class Hash, class KeyEqual, class Allocator>

bool operator!=(const Unorded_Set <Key, Hash, KeyEqual> &lhs,
                const Unorded_Set <Key, Hash, KeyEqual> &rhs);

template<class Key,
        class Hash = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>>
class Unorded_Set {
    typedef typedef Hashtable<Key, Key, Hash, KeyEqual, std::_Identity> hashtable;

public:
    typedef Key key_type;
    typedef Key value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Hash hasher;
    typedef KeyEqual key_equal;
    typedef std::allocator<key_type> allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef typename hashtable::iterator iterator;
    typedef typename const hashtable::iterator const_iterator;

public:
    //constructor and destructor
    template<class InputIt>
    Unorded_Set(InputIt first, InputIt last,
                size_type bucket_count = _stl_next_prime(last - first),
                const Hash &hash = Hash(),
                const KeyEqual &equal = KeyEqual());

    Unorded_Set(const Unorded_Set &other);

    Unorded_Set(std::initializer_list<value_type> init,

                size_type bucket_count = _stl_next_prime(init.size()),
                const Hash &hash = Hash(),
                const KeyEqual &equal = KeyEqual());

    ~Unorded_Set();

    Unorded_Set &operator=(const Unorded_Set &other);

    //iterators
    iterator begin();

    iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;

    //capacity
    bool empty() const;

    size_type size() const;

    size_type max_size() const;

    //modifiers
    void clear(); //clears the contents
    std::pair<iterator, bool> insert(const value_type &value);

    template<class InputIt>
    void insert(InputIt first, InputIt last);

    void insert(std::initializer_list<value_type> ilist);

    template<class... Args>
    std::pair<iterator, bool> emplace(Args &... args);

    iterator erase(const_iterator pos);

    iterator erase(const_iterator first, const_iterator last);

    size_type erase(const key_type &key);

    void swap(Unorded_Set &other);

    //lookup

    size_type count(const Key &key) const;

    iterator find(const Key &key);

    const_iterator find(const Key &key) const;

    std::pair<iterator, iterator> equal_range(const Key &key);

    //hash policy
    float load_factor() const;//Returns the average number of elements per bucket, that is, size() divided by bucket_count().

    float max_load_factor() const; //1) Returns current maximum load factor.


    void max_load_factor(float ml);//2) Sets the maximum load factor to ml.


    void rehash(size_type count);  //Sets the number of buckets to count and rehashes the container


    void reserve(size_type count);//Effectively calls rehash(std::ceil(count / max_load_factor()))


    //functions

    hasher hash_function() const;//Returns the function that hashes the keys.

    key_equal key_eq() const;//Returns the function that compares keys for equality.
};

#endif //STL_UNORDED_SET_H
