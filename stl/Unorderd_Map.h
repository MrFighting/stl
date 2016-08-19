//
// Created by Administrator on 2016/8/17.
//

#ifndef STL_UNORDERD_MAP_H
#define STL_UNORDERD_MAP_H

#include <functional>
#include "hashtable.h"

namespace stl {
    using namespace std;

    template <typename first, typename second>
    struct get_key {
        typedef first first_type;
        typedef second second_type;
        first& operator()(std::pair<first,second>& p) {
            return p.first;
        }
        const first& operator()(const std::pair<first, second>& p)const {
            return p.first;
        }
    };

    template<class Key, class T, class Hash, class KeyEqual>
    class Unordered_Map;
    template<class Key,class T, class Hash, class KeyEqual>
    bool operator==(const Unordered_Map <Key,T, Hash, KeyEqual> &lhs,
                    const Unordered_Map <Key,T, Hash, KeyEqual> &rhs);

    template<class Key, class T, class Hash, class KeyEqual>

    bool operator!=(const Unordered_Map <Key,T, Hash, KeyEqual> &lhs,
                    const Unordered_Map <Key,T, Hash, KeyEqual> &rhs);

    template<class Key,
            class T,
            class Hash = std::hash<Key>,
            class KeyEqual = std::equal_to<Key>>
    class Unordered_Map {

    public:
        typedef Hashtable<Key, pair<Key, T>, Hash, KeyEqual, get_key<Key, T>> hashtable;
        typedef Key key_type;
        typedef pair<Key, T> value_type;
        typedef typename value_type::second_type mapped_type;
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
        Unordered_Map():ht(0, KeyEqual(), Hash(), get_key<Key, T>()){}
        template<class InputIt>
        Unordered_Map(InputIt first, InputIt last,
                      size_type bucket_count = 0,
                      const Hash &hash = Hash(),
                      const KeyEqual &equal = KeyEqual());

        Unordered_Map(const Unordered_Map &other);

        Unordered_Map(std::initializer_list<value_type> init,

                      size_type bucket_count,
                      const Hash &hash = Hash(),
                      const KeyEqual &equal = KeyEqual());

        ~Unordered_Map();

        Unordered_Map &operator=(const Unordered_Map &other);

        //iterators
        iterator begin() { return ht.begin();}

        iterator end() { return ht.end();}

        const_iterator cbegin();

        const_iterator cend() const;

        //capacity
        bool empty() const { return ht.size() == 0;}

        size_type size() const { return ht.size();}

        size_type max_size() const { return ht.max_size();}

        size_type bucket_size() const { return ht.bucket_size();}

        mapped_type& operator[](const key_type& key) {
            iterator insertpos = insert(std::make_pair(key, T())).first;
            mapped_type& ret = insertpos->second;
            return ret;
        }

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

        void swap(Unordered_Map &other);

        //lookup

        size_type count(const Key &key);

        iterator find(const Key &key);

        const_iterator find(const Key &key) const;

        std::pair<iterator, iterator> equal_range(const Key &key);

        //hash policy
        float load_factor() const { return ht.bucket_size() / ht.size();};//Returns the average number of elements per bucket, that is, size() divided by bucket_count().

        float max_load_factor()const { return ht.max_load_factor();} ; //1) Returns current maximum load factor.


        void max_load_factor(float ml) {ht.max_load_factor(ml);}//2) Sets the maximum load factor to ml.


        void rehash(size_type count) {ht.rehash(count);};  //Sets the number of buckets to count and rehashes the container


        void reserve(size_type count) {ht.reserve(count);};//Effectively calls rehash(std::ceil(count / max_load_factor()))


        //functions

        hasher hash_function() const;//Returns the function that hashes the keys.

        key_equal key_eq() const;//Returns the function that compares keys for equality.
    };

    template<class Key, class T, class Hash, class KeyEqual>
    Unordered_Map<Key,T, Hash, KeyEqual>::~Unordered_Map() {

    }

    template<class Key, class T, class Hash, class KeyEqual>
    template<class InputIt>
    Unordered_Map<Key,T, Hash, KeyEqual>::
    Unordered_Map(InputIt first, InputIt last,
                  size_type bucket_count,
                  const Hash &hash,
                  const KeyEqual &equal):ht(bucket_count = next_prime(distance(first, last)),
                                            equal, hash, get_key<Key,T>()) {
        for_each(first, last, [this](const key_type& val){ht.insert_unique(val);});
    }

    template<class Key, class T, class Hash, class KeyEqual>
    Unordered_Map<Key,T, Hash, KeyEqual>::Unordered_Map(const Unordered_Map &other):ht(other.ht){
    }

    template<class Key, class T, class Hash, class KeyEqual>
    Unordered_Map<Key,T, Hash, KeyEqual>::
    Unordered_Map(std::initializer_list<value_type> init,
                  Unordered_Map::size_type bucket_count,
                  const Hash &hash,
                  const KeyEqual &equal)
            :Unordered_Map(init.begin(), init.end(),bucket_count,hash,equal) {
    }

    template<class Key, class T, class Hash, class KeyEqual>
    template<class InputIt>
    void Unordered_Map<Key,T, Hash, KeyEqual>::insert(InputIt first, InputIt last) {
        std::for_each(first, last,
                      [this](const key_type& val){ht.insert_unique(val);});
    }

    template<class Key, class T, class Hash, class KeyEqual>
    void Unordered_Map<Key,T, Hash, KeyEqual>::
    insert(std::initializer_list<value_type> ilist) {
        insert(ilist.begin(), ilist.end());
    }

    template<class Key, class T, class Hash, class KeyEqual>
    template<class... Args>
    pair<typename Unordered_Map<Key,T, Hash, KeyEqual>::iterator, bool>
    Unordered_Map<Key,T, Hash, KeyEqual>::emplace(Args&... args) {
        return insert(value_type(args...));
    }

    template<class Key, class T, class Hash, class KeyEqual>
    typename Unordered_Map<Key,T, Hash, KeyEqual>::iterator
    Unordered_Map<Key,T, Hash, KeyEqual>::erase(Unordered_Map::iterator pos) {
        return ht.erase(pos);
    }

    template<class Key, class T, class Hash, class KeyEqual>
    typename Unordered_Map<Key,T, Hash, KeyEqual>::iterator
    Unordered_Map<Key,T, Hash, KeyEqual>::erase
            (Unordered_Map::iterator first, Unordered_Map::iterator last) {
        return ht.erase(first,last);
    }

    template<class Key, class T, class Hash, class KeyEqual>
    typename Unordered_Map<Key,T, Hash, KeyEqual>::size_type
    Unordered_Map<Key,T, Hash, KeyEqual>::erase(const key_type &key) {
        return ht.erase(key);
    }

    template<class Key, class T, class Hash, class KeyEqual>
    void Unordered_Map<Key,T, Hash, KeyEqual>::swap(Unordered_Map &other) {
        ht.swap(other.ht);
    }

    template<class Key, class T, class Hash, class KeyEqual>
    typename Unordered_Map<Key,T, Hash, KeyEqual>::size_type
    Unordered_Map<Key,T, Hash, KeyEqual>::count(const Key &key) {
        return ht.count(key);
    }

    template<class Key, class T, class Hash, class KeyEqual>
    typename Unordered_Map<Key,T, Hash, KeyEqual>::iterator
    Unordered_Map<Key,T, Hash, KeyEqual>::find(const Key &key) {
        return ht.find(key);
    }

    template<class Key, class T, class Hash, class KeyEqual>
    pair<typename Unordered_Map<Key,T, Hash, KeyEqual>::iterator,
            typename Unordered_Map<Key,T, Hash, KeyEqual>::iterator>
    Unordered_Map<Key,T, Hash, KeyEqual>::equal_range(const Key &key) {
        return ht.equal_range(key);
    }

}

#endif //STL_UNORDERD_MAP_H
