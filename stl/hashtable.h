//
// Created by Administrator on 2016/8/8.
//

#ifndef STL_HASHTABLE_H
#define STL_HASHTABLE_H

#include <iterator>
#include <memory.h>
#include <algorithm>
#include "Vector.h"
using namespace std;
template<typename T>
struct _hash_node {
    _hash_node *next;
    T val;

    _hash_node(const T &t) : val(t),next(nullptr){}
};

template<typename Key, typename Value, typename Hash_Fun, typename EqK, typename ExtractKey>
class Hashtable;//decl

template<typename Key, typename Value, typename Hash_Fun, typename EqK, typename ExtractKey>
struct _hash_iterator : public iterator<std::forward_iterator_tag, Value> {

    typedef _hash_node<Value> node;
    typedef Hashtable<Key, Value, Hash_Fun, EqK, ExtractKey> hashtable;
    typedef _hash_iterator<Key, Value, Hash_Fun, EqK, ExtractKey> iterator;

    _hash_node<Value> *cur;
    hashtable *ht;

    _hash_iterator(node *n, hashtable *h) : cur(n), ht(h) {}

    iterator &operator++() {
        node *n = cur;
        cur = cur->next;
        if (!cur) {
            size_t bucket = ht->bkt_num(n->val);
            while (!cur && ++bucket < ht->bucket_size()) {
                cur = ht->buckets[bucket];
            }
        }
        return *this;
    }

    iterator operator++(int) {
        iterator tem = *this;
        ++(*this);
        return tem;
    }

    Value &operator*() {
        return cur->val;
    }

    Value *operator->() {
        return &(operator*());
    }

    bool operator==(const iterator &other) {
        return cur == other.cur;
    }

    bool operator!=(const iterator &other) {
        return !cur == other.cur;
    }
};


static const int _S_num_primes = 29;
unsigned long __stl_prime_list[_S_num_primes] =
        {
                5ul, 53ul, 97ul, 193ul, 389ul,
                769ul, 1543ul, 3079ul, 6151ul, 12289ul,
                24593ul, 49157ul, 98317ul, 196613ul, 393241ul,
                786433ul, 1572869ul, 3145739ul, 6291469ul, 12582917ul,
                25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul,
                805306457ul, 1610612741ul, 3221225473ul, 4294967291ul
        };

unsigned long _stl_next_prime(unsigned long n) {
    auto pos = lower_bound(begin(__stl_prime_list), end(__stl_prime_list), n);
    return pos == end(__stl_prime_list) ?
           __stl_prime_list[_S_num_primes - 1] : *pos;
}

template<typename Key, typename Value, typename Hash_Fun, typename EqK, typename ExtractKey>
class Hashtable {
    friend class _hash_iterator<Key, Value, Hash_Fun, EqK, ExtractKey>;

public:
    typedef Value value_type;
    typedef Key key_type;
    typedef EqK equal_key;
    typedef Hash_Fun hasher;
    typedef size_t size_type;
    typedef _hash_node<Value> node;
    typedef _hash_iterator<Key, Value, Hash_Fun, EqK, ExtractKey> iterator;

private:
    allocator<node> alloc;//为节点分配的分配器

    equal_key equals;
    hasher m_hash;
    ExtractKey get_key;
    stl::Vector<node *> buckets;
    size_t element_count;

    size_type bkt_num(const Value &val, size_t n) const {
        return m_hash(val) % n;
    };

    size_type bkt_num(const Value &val) const {
        return m_hash(val) % bucket_size();
    };

    node *create_node(const value_type &val) {
        node *ret = alloc.allocate(1);
        alloc.construct(ret, val);
        return ret;
    }

    void destroy_node(node *n) {
        alloc.destroy(n);
        alloc.deallocate(n, 1);
    }

    node *element_begin() const {//元素起始位置
        for (int i = 0; i < bucket_size(); ++i) {
            node *first = buckets[i];
            if (first != nullptr) {
                return first;
            }
        }
    }

public:
    //constructor
    Hashtable(size_t n, equal_key eq, hasher h, ExtractKey ek) :
            equals(eq), m_hash(h), get_key(ek), buckets(_stl_next_prime(0), nullptr) {

        element_count = 0;
    }

    typename vector<node *>::size_type bucket_size() const { return buckets.size(); }

    size_type size() const { return element_count; }

    size_type max_size()const { return __stl_prime_list[_S_num_primes-1];}

    void resize(size_t n);

    pair<iterator, bool> insert_unique(const value_type &);

    iterator insert_equal(const value_type &);

    void clear();

    void copy_from(Hashtable *other);

    iterator begin() {
        return iterator(element_begin(), this);
    }

    iterator end() {
        return iterator(nullptr, this);
    }
};

template<typename K, typename V, typename H, typename E, typename Ex>
void Hashtable<K, V, H, E, Ex>::resize(size_t n) {
    if (n > bucket_size()) {
        size_t new_size = _stl_next_prime(n);
        if (new_size > bucket_size()) {//此时再rehash
            stl::Vector<node *> temp(new_size, nullptr);
            for (int i = 0; i < buckets.size(); ++i) {
                node *first = buckets[i];
                while (first) {
                    size_t new_bucket = bkt_num(first->val, new_size);//rehash
                    node *next = first->next;
                    first->next = temp[new_bucket];
                    temp[new_bucket] = first;
                    first = next;
                }
            }
            buckets.swap(temp);
        }
    }
}

template<typename K, typename V, typename H, typename E, typename Ex>
pair<typename Hashtable<K, V, H, E, Ex>::iterator, bool>
Hashtable<K, V, H, E, Ex>::insert_unique(const Hashtable::value_type &val) {
    resize(element_count + 1);//确保hash容量

    size_type bucket = bkt_num(val);
    node *node = buckets[bucket];
    auto *n = node;
    while (n) {
        if (n->val == val) {
            return {iterator(n, this), false};
        }
        n = n->next;
    }
    Hashtable::node *tem = create_node(val);
    tem->next = node;
    buckets[bucket] = tem;
    ++element_count;
    return {iterator(tem, this), true};
}

template<typename K, typename V, typename H, typename E, typename Ex>
typename Hashtable<K, V, H, E, Ex>::iterator
Hashtable<K, V, H, E, Ex>::insert_equal(const Hashtable::value_type &val) {
    resize(element_count + 1);//确保hash容量

    size_type bucket = bkt_num(val);
    node *node = buckets[bucket];
    auto *n = node;
    while (n) {
        if (n->val == val) {
            Hashtable::node *tem = create_node(val);
            tem->next = n->next;
            n->next = tem;
            ++element_count;
            return iterator(tem, this);
        }
        n = n->next;
    }
    Hashtable::node *tem = create_node(val);
    tem->next = node;
    buckets[bucket] = tem;
    ++element_count;
    return iterator(tem, this);
}

template<typename K, typename V, typename H, typename E, typename Ex>
void Hashtable<K, V, H, E, Ex>::clear() {
    size_type bksz = bucket_size();
    for (int i = 0; i < bksz; ++i) {
        node* first = buckets[i];
        while (first) {
            node* next = first->next;
            destroy_node(first);
            first = next;
        }
        buckets[i] = nullptr;
    }
    element_count = 0;
}

template<typename K, typename V, typename H, typename E, typename Ex>
void Hashtable<K, V, H, E, Ex>::copy_from(Hashtable *other) {
    clear();
    buckets = stl::Vector<node*>(other->bucket_size(), nullptr);
   // buckets.insert(buckets.end(), )
    for (int i = 0; i < other->buckets.size(); ++i) {
        node* first = other->buckets[i];
        if (first) {
            node* temp = create_node(first->val);
            buckets[i] = temp;
            for(node* cur = first->next; cur; cur = cur->next) {
                temp->next = create_node(cur->val);
                temp = temp->next;
            }
        }
    }
    element_count = other->element_count;
}

#endif //STL_HASHTABLE_H
