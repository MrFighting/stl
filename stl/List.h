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

        typedef list_node<T> *link_type;
    private:
        link_type node;

        link_type creat_node(const T&);

        void destroy_node(link_type node);

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

       // ~List();

        //element access
        reference front();

        reference back();

        //iterators
        iterator begin() const { return node->next;}

        iterator end() const { return node;}

        const_iterator cbegin() const;

        const_iterator cend() const;

        const_reverse_iterator crbegin() const;

        const_reverse_iterator crend() const;

        //capacity
        bool empty() const;

        size_type size() const;

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

        void swap(List &other);//交换m_first,m_last,m_end

        iterator erase(iterator pos);//并不实际删除元素

        iterator erase(iterator first, iterator last);

        //Operations
        void merge(); //merges two sorted lists

        void splice();// moves elements from another list

        void remove();

        void remove_if();//removes elements satisfying specific criteria

        void reverse();//reverses the order of the elements

        void unique(); //removes consecutive duplicate elements

        void sort();// sorts the elements
    };

    template <typename T>
    typename List<T>::link_type List<T>::creat_node(const T& val) {
        list_node<T>* node = alloc.allocate(1);
        alloc.construct(node, val);
        return node;
    }

    template <typename T>
    void List<T>::destroy_node(List::link_type node) {
        alloc.destroy(node);
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
            List();
            return;
        }
        node = alloc.allocate(1);//哨兵节点
        link_type next = nullptr;
        link_type cur = node;
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
    List<T>::List(InputIt first, InputIt last):List(last-first) {
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

}

#endif //STL_LIST_H
