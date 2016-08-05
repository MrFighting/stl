//
// Created by Administrator on 2016/8/4.
//

#ifndef STL_LIST_H
#define STL_LIST_H

#include <memory.h>
#include <iterator>

using namespace std;

namespace stl {


    template<typename T>
    struct list_node {
        //链表节点
        T val;

        list_node<T> *next;
        //后一个节点
        list_node<T> *prev;//前一个节点

        list_node(int val):val(val){}
    };

    //template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
    // typename _Pointer = _Tp*, typename _Reference = _Tp&>
    template<typename T>
    struct _list_iterator : public iterator<bidirectional_iterator_tag, T> {
        typedef list_node<T> *link_type;
        typedef _list_iterator<T> self;
        link_type node;

        _list_iterator(link_type list_node) : node(list_node){}

        self operator++() {
            node = node->next;
            return *this;
        }

        self operator++(int) {
            _list_iterator<T> tem = *this;
            ++(*this);
            return tem;
        }

        self operator--() {
            node = node->prev;
            return *this;
        }

        self operator--(int) {
            _list_iterator<T> tem = *this;
            --(*this);
            return tem;
        }
        typename std::iterator<std::bidirectional_iterator_tag, T>::reference operator*() {
            return node->val;
        }
        typename std::iterator<std::bidirectional_iterator_tag, T>::pointer operator->(){
            return &(operator*());
        }
        bool operator==(const _list_iterator& other) {
            return this->node == other.node;
        }
        bool operator!=(const _list_iterator& other) {
            return this->node != other.node;
        }
    };

    template <typename T>
    class List;

    template <typename T>
    bool operator==(const List<T>& lhs, const List<T>&rhs);

    template <typename T>
    bool operator!=(const List<T>& lhs, const List<T>&rhs);

    template<typename T>
    class List {
        friend bool operator==<>(const List<T>& lhs, const List<T>&rhs);
        friend bool operator!=<>(const List<T>& lhs, const List<T>&rhs);

    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef _list_iterator<T> iterator;
        typedef const _list_iterator<T> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef list_node<T>* node_type;
    private:
        node_type node;

        node_type creat_node(const T&);

        node_type destroy_node(node_type node);

        node_type destroy_node(node_type start, node_type end);
        allocator<list_node<T>> alloc;

    public:
        //constructor
        List();

        explicit List(size_type count, const T &value = T());

        //explicit List(size_type count);

        template<class InputIt>
        List(InputIt first, InputIt last);

        List(const List &other);

        List(std::initializer_list<T> init):List(init.begin(), init.end()){}

        reference operator=(const List &other);

        ~List(){clear();};

        //element access
        reference front() { return node->next->val;}

        reference back() { return node->prev->val;};

        //iterators
        iterator begin() const { return node->next;}

        iterator end() const { return node;}

        const_iterator cbegin() const;

        const_iterator cend() const;

        const_reverse_iterator crbegin() const;

        const_reverse_iterator crend() const;

        //capacity
        bool empty() const { return node->next == node;};

        size_type size() const { return distance(begin(), end());};

        //modifiers
        void push_back(const T &t);

        void push_font(const T &);

        iterator insert(iterator it, const T &t);

        template<typename InputIterator>
        iterator insert(iterator it, InputIterator begin, InputIterator end);

        template<class... Args>
        void emplace(iterator pos, Args &&... args);

        void pop_back();

        void pop_front();

        void resize(size_type count, T value = T());//若当前大小小于count则追加元素，否则将大小调整为count

        void clear();//清除所有元素,但容量不变

        void swap(List &other);//交换两个哨兵节点

        iterator erase(iterator pos);

        iterator erase(iterator first, iterator last);

        //Operations
        void merge(const List&); //merges two sorted lists

        void splice();// moves elements from another list

        void remove();

        void remove_if();//removes elements satisfying specific criteria

        void reverse();//reverses the order of the elements

        void unique(); //removes consecutive duplicate elements

        void sort();// sorts the elements
    };

    template <typename T>
    typename List<T>::node_type List<T>::creat_node(const T& val) {
        list_node<T>* node = alloc.allocate(1);
        alloc.construct(node, val);
        return node;
    }

    template <typename T>
    inline typename List<T>::node_type List<T>::destroy_node(List::node_type node) {
        node_type next = node->next;
        alloc.destroy(node);
        alloc.deallocate(node,1);
        return next;
    }

    template <typename T>
    List<T>::List() {
        node = alloc.allocate(1);//配置一个节点空间,令首位指向自己
        node->next = node;
        node->prev = node;
    }

    template <typename T>
    List<T>::List(List::size_type count, const T &value) {
        if (count == 0) {
            __throw_range_error("list construct fail,size can not be 0");
        }
        node = alloc.allocate(1);//哨兵节点
        node_type next = nullptr;
        node_type cur = node;
        for (int i = 0; i < count; ++i) {
            next = creat_node(value);
            cur->next = next;
            next->prev = cur;

            cur = next;
        }
        cur->next = node;//将cur与哨兵节点相连
        node->prev = cur;
    }

    template <typename T>
    template<class InputIt>
    List<T>::List(InputIt first, InputIt last):List(distance(first,last)) {
//List(last-first)不能写这儿,不知道为什么

        copy(first, last, begin());//利用iterator的操作符重载递增和解引用
    }

    template <typename T>
    List<T>::List(const List &other):List(other.size()) {
        copy(other.begin(), other.end(), begin());
    }

    template <typename T>
    inline bool operator==(const List<T>& lhs, const List<T>& rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <typename T>
    inline bool operator!=(const List<T>& lhs, const List<T>& rhs) {
        return !std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename T>
    inline void List<T>::push_back(const T &t) {
        node_type newnode = creat_node(t);
        node_type end = node->prev;

        node->prev = newnode;
        newnode->next = node;

        end->next = newnode;
        newnode->prev = end;
    }

    template <typename T>
    inline void List<T>::pop_back() {
        node_type end = node->prev;

        end->prev->next = node;
        node->prev = end->prev;
        destroy_node(end);
    }

    template <typename T>
    inline void List<T>::push_font(const T &t) {
        node_type newnode = creat_node(t);
        node_type begin = node->next;

        node->next = newnode;
        newnode->prev = node;

        newnode->next = begin;
        begin->prev = newnode;
    }
    template <typename T>
    inline void List<T>::pop_front() {
        node_type begin = node->next;

        node->next = begin->next;
        begin->next->prev = node;
        destroy_node(begin);
    }

    template <typename T>
    inline typename List<T>::iterator List<T>::insert(List<T>::iterator it, const T &t) {
        node_type newnode = creat_node(t);
        node_type cur = it.node;

        cur->prev->next = newnode;
        newnode->prev = cur->prev;

        newnode->next = cur;
        cur->prev = newnode;
        return newnode;
    }

    template <typename T>
    template<typename InputIterator>
    typename List<T>::iterator List<T>::insert(List::iterator it, InputIterator begin, InputIterator end) {
        //create list from begin to end
        node_type head = creat_node(*begin);
        node_type pre = head;
        for (auto iter = ++begin; iter != end; iter++) {
            node_type cur = creat_node(*iter);
            pre->next = cur;
            cur->prev = pre;
            pre = cur;
        }        //now pre become the end of the list created above
        node_type tail = pre;
        //concatenate
        node_type node = it.node;
        node_type prev = node->prev;
        prev->next = head;
        head->prev = prev;

        tail->next = node;
        node->prev = tail;
        return head;
    }

    template <typename T>
    template<class... Args>
    inline void List<T>::emplace(List::iterator pos, Args &&... args) {
        insert(pos, T(args...));
    }

    template <typename T>
    void List<T>::resize(List::size_type count, T value) {
        int diff = count - size();

        if (diff > 0) {
//            node_type head = creat_node(value);
//            node_type pre = head;
//            for (int i = 0; i < diff - 1; ++i) {
//                node_type cur = creat_node(value);
//                pre->next = cur;
//                cur->prev = pre;
//                pre = cur;
//            }
//
//            node_type tail = pre;
//            node->prev->next = head;
//            head->prev = node->prev;
//
//            tail->next = node;
//            node->prev = tail;
            //可以直接调用inser即可,算法都一样
            stl::List<T>  tem((unsigned int) diff, value);
            insert(end(), tem.begin(), tem.end());//其实用move更好
        }
        else {
            node_type cur = node->prev;
            for (int i = 0; i < -diff; ++i) {
                node_type next_to_delete = cur->prev;
                destroy_node(cur);
                cur = next_to_delete;
            }
            cur->next = node;
            node->prev = cur;
        }
    }
    template <typename T>
    inline void List<T>::clear() {
        destroy_node(node->next, node);
        node->next = node;
        node->prev = node;
    }
    template <typename T>
    inline typename List<T>::node_type
    List<T>::destroy_node(List::node_type start, List::node_type end) {
        while (start != end) {
            start = destroy_node(start);
        }
        return start;
    }

    template <typename T>
    inline void List<T>::swap(List &other) {
        std::swap(node, other.node);
    }

    template <typename T>
    inline typename List<T>::iterator List<T>::erase(List::iterator pos) {
        node_type next = pos.node->next;
        node_type pre = pos.node->prev;
        pre->next = next;
        next->prev = pre;
        destroy_node(pos.node);
        return next;
    }

    template <typename T>
    inline typename List<T>::iterator List<T>::erase(List::iterator first, List::iterator last) {
        node_type pre = first.node->prev;
        node_type next = last.node;
        destroy_node(first.node, last.node);
        pre->next = next;
        next->prev = pre;
        return last;
    }

    template <typename T>
    void List<T>::merge(const List<T>& other) {
        iterator begin1 = begin();
        iterator begin2 = other.begin();
        while (begin1 != end() && begin2 != other.end()) {
            if (*begin1 < *begin2) {
                begin1++;
            }
            else {
                insert(begin1, *begin2);
                begin2++;
            }
        }
        if (begin1 == end()) {//把other剩余的元素插入this的末尾
            while (begin2 != other.end()) {
                insert(end(), *begin2++);//或者push_back
            }
        }
    }

}

#endif //STL_LIST_H
