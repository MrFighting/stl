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

    _hash_node(const T &t) : val(t), next(nullptr) {}
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
        return cur != other.cur;
    }
};


static const int num_primes = 29;
extern unsigned long prime_list[num_primes];

unsigned long next_prime(unsigned long n);

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
    float mlf;//max_load_factor

    equal_key m_equals;
    hasher m_hash;
    ExtractKey m_get_key;
    stl::Vector<node *> buckets;
    size_t element_count;

    size_type bkt_num(const Value &val, size_t n) const {
        return m_hash(m_get_key(val)) % n;
    };

    size_type bkt_num(const Value &val) const {
        return m_hash(m_get_key(val)) % bucket_size();
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
            m_equals(eq), m_hash(h), m_get_key(ek), buckets(next_prime(0), nullptr), mlf(1) {

        element_count = 0;
    }

    Hashtable(const Hashtable &other) : m_equals(other.m_equals),
                                        m_hash(other.m_hash),
                                        m_get_key(other.m_get_key),
                                        mlf(1) {
        copy_from(&other);
    }

    typename vector<node *>::size_type bucket_size() const { return buckets.size(); }

    size_type size() const { return element_count; }

    size_type max_size() const { return prime_list[num_primes - 1]; }

    void resize(size_t n);//将桶数量rehash到n

    pair<iterator, bool> insert_unique(const value_type &);

    iterator insert_equal(const value_type &);

    void clear();

    iterator find(const key_type &key);

    pair<iterator, iterator> equal_range(const key_type &key);

    iterator erase(iterator pos);

    iterator erase(iterator first, iterator last);

    size_type erase(const key_type &);

    void copy_from(const Hashtable *other);

    void swap(Hashtable &other);

    size_type count(const key_type &key) const;

    iterator begin() {
        return iterator(element_begin(), this);
    }

    iterator end() {
        return iterator(nullptr, this);
    }

    //hash policy
    float load_factor() const {
        return bucket_size() / size();
    };//Returns the average number of elements per bucket, that is, size() divided by bucket_count().

    float max_load_factor() const { return mlf; }  //1) Returns current maximum load factor.


    void max_load_factor(float ml) { mlf = ml; };//2) Sets the maximum load factor to ml.


    void rehash(size_type count) {//rehashs the table and the buckets num is at least count
        if (count > bucket_size()) {
            size_type nextsize = next_prime(count);
            if (nextsize != bucket_size())
                resize(nextsize);
        }
    };  //Sets the number of buckets to count and rehashes the container


    void reserve(size_type count) {//reserve space for count elements with the bucket size count / max_load_factor
        rehash(std::ceil(count / max_load_factor()));
    };//Effectively calls rehash(std::ceil(count / max_load_factor()))

    //functions templates

    hasher hash_function() const { return m_hash; };//Returns the function that hashes the keys.

    equal_key key_eq() const { return m_equals;}//Returns the function that compares keys for equality.
};

template<typename K, typename V, typename H, typename E, typename Ex>
void Hashtable<K, V, H, E, Ex>::resize(size_t n) {
    stl::Vector<node *> temp(n, nullptr);
    for (int i = 0; i < buckets.size(); ++i) {
        node *first = buckets[i];
        while (first) {
            size_t new_bucket = bkt_num(first->val, n);//rehash
            node *next = first->next;
            first->next = temp[new_bucket];
            temp[new_bucket] = first;
            first = next;
        }
    }
    buckets.swap(temp);

}

template<typename K, typename V, typename H, typename E, typename Ex>
pair<typename Hashtable<K, V, H, E, Ex>::iterator, bool>
Hashtable<K, V, H, E, Ex>::insert_unique(const Hashtable::value_type &val) {
    reserve(element_count + 1);//确保hash容量

    size_type bucket = bkt_num(val);
    node *node = buckets[bucket];
    auto *n = node;
    while (n) {
        if (m_equals(m_get_key(val), m_get_key(n->val))) {
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
    reserve(element_count + 1);//确保hash容量

    size_type bucket = bkt_num(val);
    node *node = buckets[bucket];
    auto *n = node;
    while (n) {
        if (m_equals(m_get_key(val), m_get_key(n->val))) {
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
        node *first = buckets[i];
        while (first) {
            node *next = first->next;
            destroy_node(first);
            first = next;
        }
        buckets[i] = nullptr;//must
    }
    element_count = 0;
}

template<typename K, typename V, typename H, typename E, typename Ex>
void Hashtable<K, V, H, E, Ex>::copy_from(const Hashtable *other) {
    clear();
    buckets = stl::Vector<node *>(other->bucket_size(), nullptr);
    // buckets.insert(buckets.end(), )
    for (int i = 0; i < other->buckets.size(); ++i) {
        node *first = other->buckets[i];
        if (first) {
            node *temp = create_node(first->val);
            buckets[i] = temp;
            for (node *cur = first->next; cur; cur = cur->next) {
                temp->next = create_node(cur->val);
                temp = temp->next;
            }
        }
    }
    element_count = other->element_count;
}

template<typename K, typename V, typename H, typename E, typename Ex>
typename Hashtable<K, V, H, E, Ex>::iterator
Hashtable<K, V, H, E, Ex>::erase(iterator pos) {
    if (pos == end()) return end();
    if (pos.cur->next == nullptr) {//此时为该桶的最后一个元素删除之要将该桶置位nullptr
        size_type bucket = bkt_num(*pos);
        buckets[bucket] = nullptr;
        node *cur = pos.cur;
        iterator ret = ++pos;
        destroy_node(cur);
        element_count--;
        return ret;
    }
    node *save = pos.cur->next->next;
    *(pos.cur) = *(pos.cur->next);
    destroy_node(pos.cur->next);
    pos.cur->next = save;
    element_count--;
    return pos;
}

template<typename K, typename V, typename H, typename E, typename Ex>
typename Hashtable<K, V, H, E, Ex>::iterator
Hashtable<K, V, H, E, Ex>::erase
        (Hashtable::iterator first, Hashtable::iterator last) {
    auto distanc = distance(first, last);
    for (; first != last;) {
        if (first.cur->next != last.cur) {//当前删除目标的的下个位置为last，则erase后就结束（因为erase的实现方式是删除后面的迭代器而不是当前的）
            first = erase(first);
        }
        else {
            return erase(first);
        }
    }
    return first;
}

template<typename K, typename V, typename H, typename E, typename Ex>
typename Hashtable<K, V, H, E, Ex>::size_type
Hashtable<K, V, H, E, Ex>::erase(const Hashtable::key_type &key) {
    size_type count = 0;
    auto it = begin();
    auto last = end();
    while (it != last) {
        it = std::find_if(it, end(),
                          [this, &key](const value_type &val) { return m_equals(m_get_key(val), key); });//condition
        if (it == last) break;
        it = erase(it);
        count++;
    }
    return count;
}

template<typename K, typename V, typename H, typename E, typename Ex>
void Hashtable<K, V, H, E, Ex>::swap(Hashtable &other) {
    buckets.swap(other.buckets);
    std::swap(element_count, other.element_count);
}

template<typename K, typename V, typename H, typename E, typename Ex>
typename Hashtable<K, V, H, E, Ex>::size_type
Hashtable<K, V, H, E, Ex>::count(const key_type &key) const {
    size_type count = 0;
    //未优化版
//    for_each(begin(), end(), [&count,this](const value_type& val){if (m_equals(m_get_key(val), key)) count++;});
//    return count;
    //优化版
    size_type bkt = bkt_num(key);
    node *first = buckets[bkt];
    while (first != nullptr) {
        if (m_equals(m_get_key(first->val), key)) count++;
        first = first->next;
    }
    return count;
}

template<typename K, typename V, typename H, typename E, typename Ex>
typename Hashtable<K, V, H, E, Ex>::iterator
Hashtable<K, V, H, E, Ex>::find(const key_type &key) {
    size_type bkt = bkt_num(key);
    node *first = buckets[bkt];
    while (first != nullptr) {
        if (m_equals(m_get_key(first->val), key))
            return iterator(first, this);
        first = first->next;
    }
    return end();
}

template<typename K, typename V, typename H, typename E, typename Ex>
pair<typename Hashtable<K, V, H, E, Ex>::iterator, typename Hashtable<K, V, H, E, Ex>::iterator>
Hashtable<K, V, H, E, Ex>::equal_range(const key_type &key) {
    auto first = this->find(key);
    if (first == end()) {
        return {end(), end()};
    }
    node *cur = first.cur;
    while (cur && cur->next && m_equals(m_get_key(cur->next->val), key)) {
        cur = cur->next;
    }
    return {first, iterator(cur, this)};
}


#endif //STL_HASHTABLE_H
