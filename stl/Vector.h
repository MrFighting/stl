//
// Created by Administrator on 2016/8/1.
//
#ifndef STL_VECTOR_H
#define STL_VECTOR_H

#include <memory>

using namespace std;
namespace stl {
    //申明
    template<typename T>
    class Vector;

    template<typename T>
    bool operator==(const Vector<T> &, const Vector<T> &);

    template<typename T>
    bool operator!=(const Vector<T> &, const Vector<T> &);

    template<typename T>
    class Vector {
        friend bool operator==<>(const Vector<T> &, const Vector<T> &);

        friend bool operator!=<>(const Vector<T> &, const Vector<T> &);

    public:
        //member type
        typedef T value_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef std::reverse_iterator<T *> reverse_iterator;
        typedef std::reverse_iterator<const T *> const_reverse_iterator;
    private:
        std::allocator<T> alloc; //分配器

        iterator m_first; //首地址

        iterator m_last;    //尾地址

        iterator m_end; //最大地址

        void check();//检查是否满了,并扩容

        void destory(iterator beg, iterator end);

        void reserve_aux(size_t newsize);//将元素拷贝至变动后的地址

        void erase_at_end(iterator pos) { m_last = pos; }//将m_last 设为 pos

    public:
        //constructor
        //explicit Vector(size_type count);

        explicit Vector(const Vector &other);

        explicit Vector(size_type count,
                        const T &value = T());

        explicit Vector() { m_last = m_first = m_end = nullptr; };

        Vector(std::initializer_list<T> init);

        template<typename InputIterator>
        explicit Vector(InputIterator first, InputIterator last);

        Vector& operator=(const Vector&);
        ~Vector() {
            clear();
            alloc.deallocate(m_first, capacity());
        }//析构

        //modifiers
        void push_back(const T &t);

        iterator insert(iterator it, const T &t);

        template<typename InputIterator>
        iterator insert(iterator it, InputIterator begin, InputIterator end);

        template<class... Args>
        void emplace(iterator pos, Args &&... args);

        void pop_back();

        void resize(size_type count, T value = T());//若当前大小小于count则追加元素，否则将大小调整为count

        void clear();//清除所有元素,但容量不变

        void swap(Vector &other);//交换m_first,m_last,m_end

        iterator erase(iterator pos);//并不实际删除元素

        iterator erase(const_iterator pos);

        iterator erase(iterator firstx, iterator last);

        iterator erase(const_iterator first, const_iterator last);

        void shrink_to_fit();//递归的缩小

        //capacity
        bool empty() const { return m_first == m_last; };

        size_type size() const { return m_last - m_first; };

        void reserve(size_t newsize);

        size_type capacity() const { return m_end - m_first; };

        //itrator
        iterator begin() const { return m_first; };

        iterator end() const { return m_last; };

        const_iterator cbegin() const { return m_first; };

        const_iterator cend() const { return m_end; };

        const_reverse_iterator crbegin() const { return std::reverse_iterator<const T *>(m_first); };


        const_reverse_iterator crend() const { return std::reverse_iterator<const T *>(m_end); };

        //element access
        reference at(size_type index);

        const_reference at(size_type index) const;

        reference front() { return *m_first; };

        const_reference front() const { return *m_first; }

        reference back() { return *(m_last - 1); }

        const_reference back() const { return *(m_last - 1); }

        const_reference operator[](size_type pos) const;

        reference operator[](size_type pos);

    };

//    template<typename T>
//    Vector<T>::Vector(size_t count) {
//        m_last = m_first = alloc.allocate(count);
//        m_end = m_first + count;
//    }

    template<typename T>
    Vector<T>::Vector(const Vector &other) {
        m_last = m_first = alloc.allocate(other.size());
        m_end = m_first + other.size();
        uninitialized_copy(other.cbegin(), other.cend(), m_first);
    }

    template<typename T>
    Vector<T>::Vector(size_type count, const T &value) {
        m_first = alloc.allocate(count);
        m_last = m_end = m_first + count;
        uninitialized_fill_n(m_first, count, value);
    }

    template<typename T>
    Vector<T>::Vector(std::initializer_list<T> init) : Vector(init.begin(), init.end()) {
    }

    template<class T>
    template<class InputIterator>
    Vector<T>::Vector(InputIterator first, InputIterator last) {
        m_first = alloc.allocate(last - first);
        m_last = m_end = m_first + (last - first);
        uninitialized_copy(first, last, m_first);
    }

    template<typename T>
    inline void Vector<T>::push_back(const T &t) {
        check();
        alloc.construct(m_last++, t);
    }

    template<typename T>
    inline void Vector<T>::check() {
        if (m_last == m_end) {//满了
            size_t new_size = size() ? size() * 2 : 1;//扩容
            reserve_aux(new_size);//实现了下面注释的功能(将原来的elements复制到新的空间)
//        iterator first = m_first;
//        iterator last = m_last;
//        m_first = alloc.allocate(new_size);
//
//        uninitialized_copy(first, last, m_first);
//
//        m_end = m_first + new_size;
//        m_last = m_first + (last - first);
//
//        destory(first, last);//摧毁原来的
//        alloc.deallocate(first, last - first);
        }
    }

    template<typename T>
    void Vector<T>::reserve(size_t newsize) {
        if (newsize > capacity()) {
            reserve_aux(newsize);
        }
    }

    template<typename T>
    void Vector<T>::reserve_aux(size_t newsize) {
        iterator first = m_first;
        iterator last = m_last;
        m_first = alloc.allocate(newsize);

        uninitialized_copy(first, last, m_first);

        m_end = m_first + newsize;
        m_last = m_first + (last - first);

        destory(first, last);//摧毁原来的
        alloc.deallocate(first, last - first);
    }

    template<typename T>
    void Vector<T>::destory(iterator beg, iterator end) {
        for (iterator it = beg; it != end; it++) {
            alloc.destroy(beg);
        }
    }

    template<typename T>
    typename Vector<T>::iterator Vector<T>::insert(iterator it, const T &t) {//O(n)
//    copy_backward(it - 1, m_last, m_last + 1);//向后移动一个
//    alloc.construct(--it, t);
//    m_last++;
        /*上面做法是错误的,最后面必须要是construct造出来的*/

        if (it == end()) {//若是在末尾插入，则下面算法会失效。直接用push_back即可
            push_back(t);
            return end() - 1;
        }
        iterator first = m_first;
        check();
        it = m_first + (it - first);//必须加上这一句，因为重新分配了空间
        alloc.construct(m_last, *(m_last - 1));//拷贝最后一个元素到下一个位置
        std::copy_backward(it, m_last - 1, m_last);//移动
        m_last++;
        T temp = t;
        *(it) = temp;//往前复制t
        return it;
    }

    template<typename T>
    template<typename InputIterator>
    typename Vector<T>::iterator Vector<T>::insert(iterator it, InputIterator begin, InputIterator end) {
        iterator first = m_first;
        ptrdiff_t diff = end - begin;
        size_t reserved_size = size() + diff;
        reserve(reserved_size);

        it = m_first + (it - first);//同上

        size_t inserted_size = end - begin;//插入元素个数
        size_t elem_after = m_last - it;//it之后的元素个数

        if (inserted_size <= elem_after) {//插入元素个数不大于该迭代器后面的元素个数

            std::uninitialized_copy(m_last - diff, m_last, m_last);
            auto sz = capacity();
            std::copy_backward(it, m_last - diff, m_last);
            std::copy(begin, end, it);
        }
        else {
            uninitialized_copy(it, m_last, m_end - elem_after);//将it之后的元素拷贝到vector的末尾

            uninitialized_fill(m_last, m_end - elem_after, T());//填充没有初始化的区域
            copy(begin, end, it);

        }
        m_last += diff;
        return it;
    }

    //comparator == and !=

    template<typename T>
    inline bool operator==(const Vector<T> &lhs, const Vector<T> &rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<typename T>
    inline bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs) {
        return !std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    //reference access

    template<typename T>
    inline typename Vector<T>::reference Vector<T>::operator[](size_type index) {
        return *(m_first + index);
    }

    template<typename T>
    inline typename Vector<T>::const_reference Vector<T>::operator[](size_type index) const {
        return *(m_first + index);
    }

    template<typename T>
    template<class... Args>
    inline void Vector<T>::emplace(iterator pos, Args &&... args) {
        insert(pos, T(args...));
    }


    template<typename T>
    inline void Vector<T>::pop_back() {
        alloc.destroy(--m_last);//销毁最后一个元素
        //shrink_to_fit();
    }

    template<typename T>
    void Vector<T>::resize(size_type count, T value) {
        int diff = count - size();//若为size_t就会出错,diff永远不会小于0
        if (diff < 0) {
            destory(m_last + diff, m_last);
            m_last = m_last + diff;//相加即是相减

            shrink_to_fit();
        }
        else {
            reserve(count);//预留count个大小
            uninitialized_fill_n(m_last, diff, value);
            m_last += count;
        }
    }

    template<typename T>
    inline void Vector<T>::shrink_to_fit() {
        if (capacity() && size() < 0.5 * capacity()) {
            size_t newsize = size() / 2;
            reserve_aux(newsize);

            shrink_to_fit();//递归的进行
        }
    }

    template<typename T>
    inline void Vector<T>::clear() {
        destory(m_first, m_last);
        m_last = m_first;
    }

    template<typename T>
    inline void Vector<T>::swap(Vector &other) {
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        std::swap(m_end, other.m_end);
    }

    template<typename T>
    inline typename Vector<T>::iterator Vector<T>::erase(iterator pos) {
        //iterator ret = ++pos;//返回后一个元素
        copy(pos + 1, m_last, pos);//后面的元素往前移动一个
        erase_at_end(m_last - 1);
        return pos;
    }

    template<typename T>
    inline typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last) {
        copy(last, m_last, first);
        erase_at_end(m_last - (last - first));
        return first;
    }

    template<typename T>
    inline typename Vector<T>::const_reference Vector<T>::at(size_type index) const {
        if (index >= size()) {
            __throw_out_of_range(__N("vector::_M_range_check"));
        }
        return (*this)[index];
    }

    template<typename T>
    inline typename Vector<T>::reference Vector<T>::at(size_type index) {
        if (index >= size()) {
            __throw_out_of_range(__N("vector::_M_range_check"));
        }
        return (*this)[index];
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(const Vector &other) {
        if (this == &other)
            return *this;
        clear();
        alloc.deallocate(m_first, capacity());
        m_first = alloc.allocate(other.capacity());
        m_end = m_first + other.capacity();
        uninitialized_copy(other.begin(), other.end(), m_first);
        m_last = m_first + other.size();
    }

}


#endif //STL_VECTOR_H
