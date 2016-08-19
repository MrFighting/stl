//
// Created by Administrator on 2016/8/19.
//

#ifndef STL_QUEUE_H
#define STL_QUEUE_H
//
// Created by Administrator on 2016/8/19.
//

#include "List.h"

#ifndef STL_STACK_H
#define STL_STACK_H
namespace stl {
    template<typename T, class Container = stl::List<T>>
    class Queue {
    public:
        typedef typename Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

    private:
        Container c;
    public:
        explicit
        Queue(const Container &_c) : c(_c) {}

        explicit
        Queue(Container &&_c = Container()) : c(std::move(_c)) {}

        Queue(const Queue &other) : c(other.c) {}

        Queue &operator=(const Queue &other) {
            c = other.c;
            return *this;
        }

        reference front() {
            return c.front();
        }

        const_reference back() const {
            return c.back();
        }

        bool empty() const {
            return c.empty;
        }

        size_type size() const {
            return c.size();
        }

        void push(const value_type &val) {
            c.push_back(val);
        }

        void pop() {
            c.pop_front();
        }

        void swap(Queue &other) {
            c.swap(other.c);
        }
    };
}
#endif //STL_STACK_H

#endif //STL_QUEUE_H
