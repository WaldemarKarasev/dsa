#include <iostream>
#include <memory>

namespace lib {
    template <typename T, typename Deleter = std::default_delete<T>>
    class unique_ptr
    {
    private:
        T* ptr;
        Deleter del;   
    public:
        unique_ptr(T* ptr) : ptr(ptr) {}
        ~unique_ptr()
        {
            del(ptr);
        }

        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        unique_ptr(unique_ptr&& other)
            : ptr(other.ptr)
        {
            other.ptr = nullptr;            
        }

        unique_ptr& operator=(unique_ptr&& other)
        {
            if (this != &other)
            {
                del(ptr);
                ptr = other.ptr;
                del = std::move(other.ptr);
                other.ptr = nullptr;
            }
            return this;
        }

        T& operator*() const 
        {
            return *ptr;
        }

        T* operator->() const
        {
            return ptr;
        }

        T* get() const
        {
            return ptr;
        }

    };
    
}
