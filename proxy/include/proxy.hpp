/* Proxy object.
 * @file
 * @date 2019-12-06
 * @author Serega
 */

#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>

template<class T>
class ptr_holder
{
public:
    ptr_holder(T* ptr): ptr_(ptr) {}
    ~ptr_holder(){};
    
    class proxy: private std::lock_guard<std::mutex> 
    {
    public:

        proxy(T * ptr, std::mutex& mtx): std::lock_guard<std::mutex> (mtx), ptr_proxy(ptr) {}
        T* operator -> () const {return ptr_proxy;}
        ~proxy(){};
    private:
        T* ptr_proxy;
    };

    proxy operator -> () const
    {
        return proxy( ptr_, mutex_);
    }
    
private:
    T* ptr_;
    mutable std::mutex mutex_;
};

#endif // __PROXY_HPP__

