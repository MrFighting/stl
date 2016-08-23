//
// Created by Administrator on 2016/8/23.
//

#ifndef STL_MEMORY_H
#define STL_MEMORY_H

#include <cstddef>
#include <algorithm>
#include <atomic>

namespace stl {
    template<typename T>
    struct Defaut_Deleter {
        void operator()(T *pt) {
            if (pt) {
                delete pt;
            }
        }
    };

    template<typename T>
    struct Defaut_Deleter<T[]> {
        void operator()(T tarry[]) {
            if (tarry) {
                delete[] tarry;
            }
        }
    };

    template<typename T, typename D = Defaut_Deleter<T>>
    class Unique_Ptr {
    public:
        typedef T element_type;
        typedef D deleter_type;
        typedef T *pointer;

    private:
        pointer m_data;
        deleter_type deleter;

    public:
        //constructor
        //Unique_Ptr():m_data(nullptr),deleter(Defaut_Deleter<T>()){}

        explicit Unique_Ptr(pointer p = nullptr, deleter_type del = deleter_type()):m_data(p), deleter(del){}

        //Unique_Ptr(pointer p = nullptr):m_data(p){}

        Unique_Ptr(Unique_Ptr&& up):m_data(up.release()),deleter (up.get_deleter()){}

        //Copy Asign
        Unique_Ptr& operator=(const Unique_Ptr& up) = delete;//不允许左值赋值

        Unique_Ptr& operator=(Unique_Ptr&& up) {
            if (this == &up)return *this;
            deleter(m_data);
            m_data = up.release();
        }
        //destructor
        ~Unique_Ptr(){
            if (m_data){
                deleter(m_data);
                m_data = nullptr;
            }
        }

    public:
        pointer release() {
            pointer ret = m_data;
            m_data = nullptr;//重要,避免提前释放了资源
            return ret;
        }

        void reset(pointer p = nullptr) {
            if (m_data) {
                deleter(m_data);
            }
            m_data = p;
        }
        void swap(Unique_Ptr& up){ std::swap(m_data, up.m_data); }

        pointer get() const { return m_data;}

        deleter_type get_deleter()const { return deleter;}

        element_type& operator*()const {
            return *m_data;
        }
        element_type& operator*() {
            return *m_data;
        }
        pointer operator->() {
            return &(this->operator*());
        }
        const pointer operator->()const {
            return &(this->operator*());
        }

        operator bool() const{ return get() != nullptr; }
    };

    template <class T, class D>
    void swap(Unique_Ptr<T, D>& x, Unique_Ptr<T, D>& y){
        x.swap(y);
    }
    template <class T1, class D1, class T2, class D2>
    bool operator == (const Unique_Ptr<T1, D1>& lhs, const Unique_Ptr<T2, D2>& rhs){
        return lhs.get() == rhs.get();
    }
    template <class T, class D>
    bool operator == (const Unique_Ptr<T, D>& up, nullptr_t p){
        return up.get() == p;
    }
    template <class T, class D>
    bool operator == (nullptr_t p, const Unique_Ptr<T, D>& up){
        return up.get() == p;
    }
    template <class T1, class D1, class T2, class D2>
    bool operator != (const Unique_Ptr<T1, D1>& lhs, const Unique_Ptr<T2, D2>& rhs){
        return !(lhs == rhs);
    }
    template <class T, class D>
    bool operator != (const Unique_Ptr<T, D>& up, nullptr_t p){
        return up.get() != p;
    }
    template <class T, class D>
    bool operator != (nullptr_t p, const Unique_Ptr<T, D>& up){
        return up.get() != p;
    }

    template <class T, class... Args>
    Unique_Ptr<T> make_unique(Args&&... args){
        return Unique_Ptr<T>(new T(std::forward<Args>(args)...));
    };

}

//shared_ptr写不安全

template <typename T>
class Shared_Ptr {
public:
    typedef T element_type;
    typedef T* pointer;
private:
    std::atomic<size_t >* ref_count;
    pointer ptr;

    void increase_count() {
        (*ref_count)++;
    }

    void decrease_count() {
        if (ref_count != nullptr) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ref_count;
                ref_count = nullptr;
                delete ptr;
                ptr = nullptr;
            }
        }
    }
public:
    Shared_Ptr(pointer p = nullptr) :ptr(p),ref_count(new std::atomic<size_t>(1)){}

    Shared_Ptr(const Shared_Ptr& spt) {
        ptr = spt.ptr;
        ref_count = spt.ref_count;
        increase_count();
    }

    Shared_Ptr& operator=(const Shared_Ptr& spt) {
        if (this != &spt) {
            decrease_count();
            ptr = spt.ptr;
            ref_count = spt.ref_count;
            increase_count();
        }
        return *this;
    }

    ~Shared_Ptr(){ decrease_count(); }


    const element_type& operator *()const{ return *(get()); }
    const element_type *operator ->()const{ return get(); }
    element_type& operator *(){ return *(get()); }
    element_type *operator ->(){ return get(); }

    const element_type* get() const{ return ptr; }
    element_type* get(){ return ptr; }
    size_t use_count() const{ return *ref_count; }

    operator bool() const{ return get() != nullptr; }
};

template<class T1, class T2>
bool operator == (const Shared_Ptr<T1>& lhs, const Shared_Ptr<T2>& rhs){
    return lhs.get() == rhs.get();
}
template<class T>
bool operator == (const Shared_Ptr<T>& sp, nullptr_t p){
    return sp.get() == p;
}
template<class T>
bool operator == (nullptr_t p, const Shared_Ptr<T>& sp){
    return sp == p;
}
template<class T1, class T2>
bool operator != (const Shared_Ptr<T1>& lhs, const Shared_Ptr<T2>& rhs){
    return !(lhs == rhs);
}
template<class T>
bool operator != (const Shared_Ptr<T>& sp, nullptr_t p){
    return !(sp == p);
}
template<class T>
bool operator != (nullptr_t p, const Shared_Ptr<T>& sp){
    return !(sp == p);
}

template<class T, class...Args>
Shared_Ptr<T> make_shared(Args... args){
    return Shared_Ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //STL_MEMORY_H
