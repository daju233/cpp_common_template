#include <atomic>
#include <bits/stdc++.h>
#include <cstddef>
#include <iostream>
#include <ostream>

class sharedCount{
    public:
    std::atomic<int> sharednum;
    sharedCount(){
        sharednum.store(0);
        sharednum.fetch_add(1);
    }
};

template <typename T>
class sharedptr{
    private:
    T* _ptr;
    sharedCount* share_count;

    public:
    explicit sharedptr(T*ptr = nullptr):_ptr(ptr){
        if (ptr){
            share_count = new sharedCount();
        }
    }

    sharedptr(const sharedptr& other){
        _ptr = other._ptr;
        if(_ptr){
            other.share_count->sharednum.fetch_add(1);
            share_count = other.share_count;
        }
    }

    sharedptr(sharedptr&& other){
        _ptr = other._ptr;
        if(_ptr){
            share_count = other.share_count;
            other._ptr = nullptr;
        }
    }

    int usecount(){
            return share_count->sharednum.load();
    }

    ~sharedptr(){
        share_count->sharednum.fetch_sub(1);
        if( share_count->sharednum==0){
            delete share_count;
            delete _ptr;
        }
}

    T& operator*() const{return *_ptr;}
    T* operator->() const{return _ptr;}

    //sharedptr& operator=(const sharedptr& rhs)
    sharedptr& operator=(const sharedptr rhs){
        std::swap(rhs._ptr,this->_ptr);
        return *this;
    }//注意rhs是值 swap and copy是最佳实践？

};

int main(){
    int* a = new int(114514);
    sharedptr<int> ptr1(a); 
    sharedptr<int> ptr2(std::move(ptr1));
    sharedptr<int> ptr3 = ptr2;
    std::cout<<*ptr2<<std::endl<<ptr2.usecount();
    return 0;
}


//隐式转换
        // template<typename U>
    // sharedptr(sharedptr<U>& other){
    //     _ptr = other._ptr;
    //     if(_ptr){
    //         other.share_count->sharednum.fetch_add(1);
    //         share_count = other.share_count;
    //     }
    // }
    // template<typename U>
    // sharedptr(sharedptr<U>&& other){
    //     _ptr = other._ptr;
    //     if(_ptr){
    //         share_count = other.share_count;
    //         other._ptr = nullptr;
    //     }
    // }