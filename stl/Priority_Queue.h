//
// Created by Administrator on 2016/8/19.
//

#include <functional>
#include "Vector.h"

#ifndef STL_PRIORITY_QUEUE_H
#define STL_PRIORITY_QUEUE_H
namespace stl {

    template <typename T, typename Comparator >
    void percolate_up(size_t index, Vector<T>& vec, Comparator comparator ) {//上升
        if (index >= vec.size()) {__throw_out_of_range("out of range");}
        size_t parent = (index - 1) / 2;
        while (parent >= 0 && comparator(vec[parent], vec[index])) {
            std::swap(vec[parent], vec[index]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    template <typename T , typename Comparator >
    void percolate_down(size_t index, Vector<T>& vec, Comparator comparator) {//下沉
        //if (index >= vec.size()) {__throw_out_of_range("out of range");}
        size_t secondChild = index * 2 + 2;//右子节点
        size_t len = vec.size();
        while (secondChild < len) {
            if (comparator(vec[secondChild], vec[secondChild - 1])) {//右节点小于左子节点
                secondChild--;//secondchile代表较大的节点
            }
            if (comparator(vec[index], vec[secondChild])) {//index的元素小于较大的子节点
                std::swap(vec[index], vec[secondChild]);//交换
            }
            else {
                break;
            }
            index = secondChild;
            secondChild = index * 2 + 2;
        }
        if (secondChild == len) {//没有右子节点的情况
            if (comparator(vec[index], vec[secondChild - 1])) {
                std::swap(vec[index], vec[secondChild - 1]);
            }
        }
    }

    template <typename T,typename Comparator>
    void make_heap( Vector<T>& vec,Comparator comparator) {
        int index = (vec.size() - 1 - 1)/2;
        while (index >= 0) {
            percolate_down(index,vec, comparator);
            index--;
        }
    }
    /*
     * pq
     */
    template <typename T , typename Compare = std::less<T>>
    class Priority_Queue {

        template<typename _Tp1, typename _Seq1>
        friend bool
        operator==(const Priority_Queue<_Tp1, _Seq1>&rhs, const Priority_Queue<_Tp1, _Seq1>& lhs) {
            return lhs.vec == rhs.vec;
        }
    public:
        typedef Vector<T> Container;
        typedef Compare value_compare;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        typedef typename Container::iterator iterator;
    private:

        Vector<T> vec;
        value_compare comparator;

    public:
        explicit Priority_Queue( const Compare& compare = Compare()):comparator(compare), vec(){}

        Priority_Queue( const Priority_Queue& other ):vec(other.vec) {
        }

        template< class InputIt >
        Priority_Queue(InputIt first, InputIt last,
                       const Compare& compare = Compare()):comparator(compare),vec(first,last) {
            make_heap(vec,comparator);
        }

        Priority_Queue(initializer_list<T> init, const Compare& compare = Compare()):
                Priority_Queue(init.begin(),init.end(),compare){}
        const_reference top() const { return vec[0];};

        bool empty() const { return vec.empty();};

        size_type size() const { return vec.size();}

        iterator begin() {
            return vec.begin();
        }

        iterator end() {
            return vec.end();
        }

        void push( const value_type& value );

        void pop();

        void swap( Priority_Queue& other ) {vec.swap(other.vec);};
    };


    template <typename T , typename Compare>
    void Priority_Queue<T,Compare>::push(const value_type &value) {
        vec.push_back(value);
        percolate_up(size() - 1, vec,comparator);
    }

    template <typename T , typename Compare>
    void Priority_Queue<T,Compare>::pop() {
        std::swap(vec[size()-1], vec[0]);//首尾元素交换
        vec.pop_back();
        percolate_down(0,vec,comparator);//首元素下降
    }


}

#endif //STL_PRIORITY_QUEUE_H
