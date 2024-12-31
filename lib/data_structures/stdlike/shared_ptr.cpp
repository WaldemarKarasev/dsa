#include <iostream>
#include <memory>

namespace lib {
template <typename T>
class shared_ptr
{
private:
    T* ptr;
    BaseControlBlock* count;

    struct BaseControlBlock
    {
        size_t shared_count;
        size_t weak_count;

        virtual ~BaseControlBlock() = 0;
    };

    // make shared
    template <typename U, typename Deleter, typename Alloc>
    struct ControlBlockRegular : public BaseControlBlock
    {
        Deleter del;
        Alloc alloc;
        // getCopy
        // getMove
    };

    // no make shared
    template <typename U, typename Alloc>
    struct ControlBlockRegular : public BaseControlBlock
    {
        U value;
        Alloc alloc;
    };

    // std pointer cast???

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&...);

    shared_ptr(ControlBlock* cb)

public:
    shared_ptr(T* ptr)
            : ptr(ptr), count(new size_t(1)) 
    {
        if constexpr(std::is_base_of_v<enable_shared_from_this<T>, T>)
        {
            ptr->sptr = *this;
        }
    }

    shared_ptr(const shared_ptr& other)
            : ptr(ptr), count(count)
    {
        ++*count;        
    }

    template <typename Y, typename Deleter>
    shared_ptr(Y* ptr, Deleter del);
    {

    }

    ~shared_ptr()
    {
        if (!count)
        {
            return;
        }
        --*count;
        if (!*count)
        {
            delete count;
            delete ptr;
        }
    }
};


// fwd decl
template <typename T>
class unique_ptr;

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    auto* p = new typename shared_ptr<T>::ControlBlock{T(std::forward<Args>(args)...), 1}
    return shared_ptr<T>(p);
}

template <typename T, typename Alloc, typename... Args>
shared_ptr<T> allocate_shared(const Alloc& alloc, Args&&... args)
{
    using BlockAlloc = std::allocator_traits<Alloc>
            ::rebind_alloc<ControlBlockMakeShared<T, Alloc>>;
    
    BlockAlloc ba = alloc;
    auto* ptr = ba.allocate(1);
    ba.construct(ptr, 1, 0, std::forward(<Args>(args)..., alloc));
    //return shared_ptr(ba); // TODO
}


// weak_ptr
template <typename T>
class weak_ptr
{
    T* ptr;
    ControlBlock* block;
};

// enable_shared_from_this
// CRTP
template <typename T>
struct enable_shared_from_this
{
    weak_ptr<T> sptr;
    shared_ptr<T> shared_form_this() const
    {
        return sptr;
    }

    enable_shared_from_this()
    {

    }

    template <typename U>
    friend class shared_ptr;
};



struct S : public std::enable_shared_from_this<S>  
{
    std::shared_ptr<S> getObject()
    {
        //return shared_ptr<S>(this); // wrong
        return shared_from_this();
    }
};

}


struct Base {};

struct  Derived : Base {};

int main()
{
    {
        auto p = make_shared<Derived>();
        shared_ptr<Base> bp = p;
    }

    {
        //std::weak_ptr<int> ptr(5);

        std::shared_ptr<int> s_ptr = ptr.lock();
    }


}