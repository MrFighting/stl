//
// Created by lee on 16-8-10.
//

#ifndef STL_UNORDED_SET_H
#define STL_UNORDED_SET_H

#include "hashtable.h"
#include <functional>



template<class Key, class Hash, class KeyEqual>
class Unorded_Set;
template<class Key, class Hash, class KeyEqual>
bool operator==(const Unorded_Set <Key, Hash, KeyEqual> &lhs,
                const Unorded_Set <Key, Hash, KeyEqual> &rhs);

template<class Key, class Hash, class KeyEqual, class Allocator>

bool operator!=(const Unorded_Set <Key, Hash, KeyEqual> &lhs,
                const Unorded_Set <Key, Hash, KeyEqual> &rhs);

template<class Key,
        class Hash = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>>
class Unorded_Set {

public:
    typedef Hashtable<Key, Key, Hash, KeyEqual, std::_Identity<Key>> hashtable;

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
    typedef const typename hashtable::iterator const_iterator;
private:
    hashtable ht;

public:
    //constructor and destructor
    Unorded_Set():ht(0, KeyEqual(), Hash(), std::_Identity<Key>()){}
    template<class InputIt>
    Unorded_Set(InputIt first, InputIt last,
                size_type bucket_count = 0,
                const Hash &hash = Hash(),
                const KeyEqual &equal = KeyEqual());

    Unorded_Set(const Unorded_Set &other);

    Unorded_Set(std::initializer_list<value_type> init,

                size_type bucket_count,
                const Hash &hash = Hash(),
                const KeyEqual &equal = KeyEqual());

    ~Unorded_Set();

    Unorded_Set &operator=(const Unorded_Set &other);

    //iterators
    iterator begin() { return ht.begin();}

    iterator end() { return ht.end();}

    const_iterator cbegin();

    const_iterator cend() const;

    //capacity
    bool empty() const { return ht.size() == 0;}

    size_type size() const { return ht.size();}

    size_type max_size() const { return ht.max_size();}

    //modifiers
    void clear() {ht.clear();} //clears the contents
    std::pair<iterator, bool> insert(const value_type &value) { return ht.insert_unique(value);}

    template<class InputIt>
    void insert(InputIt first, InputIt last);

    void insert(std::initializer_list<value_type> ilist);

    template<class... Args>
    std::pair<iterator, bool> emplace(Args &... args);

    iterator erase(iterator pos);

    iterator erase(iterator first, iterator last);

    size_type erase(const key_type &key);

    void swap(Unorded_Set &other);

    //lookup

    size_type count(const Key &key);

    iterator find(const Key &key);

    const_iterator find(const Key &key) const;

    std::pair<iterator, iterator> equal_range(const Key &key);

    //hash policy
    float load_factor() const { return ht.bucket_size() / ht.size();};//Returns the average number of elements per bucket, that is, size() divided by bucket_count().

    float max_load_factor()const { } ; //1) Returns current maximum load factor.


    void max_load_factor(float ml);//2) Sets the maximum load factor to ml.


    void rehash(size_type count);  //Sets the number of buckets to count and rehashes the container


    void reserve(size_type count);//Effectively calls rehash(std::ceil(count / max_load_factor()))


    //functions

    hasher hash_function() const;//Returns the function that hashes the keys.

    key_equal key_eq() const;//Returns the function that compares keys for equality.
};

template<class Key, class Hash, class KeyEqual>
Unorded_Set<Key, Hash, KeyEqual>::~Unorded_Set() {

}

template<class Key, class Hash, class KeyEqual>
template<class InputIt>
Unorded_Set<Key, Hash, KeyEqual>::
Unorded_Set(InputIt first, InputIt last,
            size_type bucket_count,
            const Hash &hash,
            const KeyEqual &equal):ht(bucket_count = next_prime(distance(first, last)),
                                      equal, hash, std::_Identity<Key>()) {
    for_each(first, last, [this](const key_type& val){ht.insert_unique(val);});
}

template<class Key, class Hash, class KeyEqual>
Unorded_Set<Key, Hash, KeyEqual>::Unorded_Set(const Unorded_Set &other):ht(other.ht){
}

template<class Key, class Hash, class KeyEqual>
Unorded_Set<Key, Hash, KeyEqual>::
Unorded_Set(std::initializer_list<value_type> init,
            Unorded_Set::size_type bucket_count,
            const Hash &hash,
            const KeyEqual &equal)
        :Unorded_Set(init.begin(), init.end(),bucket_count,hash,equal) {
}

template<class Key, class Hash, class KeyEqual>
template<class InputIt>
void Unorded_Set<Key, Hash, KeyEqual>::insert(InputIt first, InputIt last) {
    std::for_each(first, last,
             [this](const key_type& val){ht.insert_unique(val);});
}

template<class Key, class Hash, class KeyEqual>
void Unorded_Set<Key, Hash, KeyEqual>::
insert(std::initializer_list<value_type> ilist) {
    insert(ilist.begin(), ilist.end());
}

template<class Key, class Hash, class KeyEqual>
template<class... Args>
pair<typename Unorded_Set<Key, Hash, KeyEqual>::iterator, bool>
Unorded_Set<Key, Hash, KeyEqual>::emplace(Args&... args) {
    return insert(value_type(args...));
}

template<class Key, class Hash, class KeyEqual>
typename Unorded_Set<Key, Hash, KeyEqual>::iterator
Unorded_Set<Key, Hash, KeyEqual>::erase(Unorded_Set::iterator pos) {
    return ht.erase(pos);
}

template<class Key, class Hash, class KeyEqual>
typename Unorded_Set<Key, Hash, KeyEqual>::iterator
Unorded_Set<Key, Hash, KeyEqual>::erase
        (Unorded_Set::iterator first, Unorded_Set::iterator last) {
    return ht.erase(first,last);
}

template<class Key, class Hash, class KeyEqual>
typename Unorded_Set<Key, Hash, KeyEqual>::size_type
Unorded_Set<Key, Hash, KeyEqual>::erase(const key_type &key) {
    return ht.erase(key);
}

template<class Key, class Hash, class KeyEqual>
void Unorded_Set<Key, Hash, KeyEqual>::swap(Unorded_Set &other) {
    ht.swap(other.ht);
}

template<class Key, class Hash, class KeyEqual>
typename Unorded_Set<Key, Hash, KeyEqual>::size_type
Unorded_Set<Key, Hash, KeyEqual>::count(const Key &key) {
    return ht.count(key);
}

template<class Key, class Hash, class KeyEqual>
typename Unorded_Set<Key, Hash, KeyEqual>::iterator
Unorded_Set<Key, Hash, KeyEqual>::find(const Key &key) {
    return ht.find(key);
}

template<class Key, class Hash, class KeyEqual>
pair<typename Unorded_Set<Key, Hash, KeyEqual>::iterator,typename Unorded_Set<Key, Hash, KeyEqual>::iterator>
Unorded_Set<Key, Hash, KeyEqual>::equal_range(const Key &key) {
    return ht.equal_range(key);
}


#endif //STL_UNORDED_SET_H
