#pragma once


//
// Container -> Allocator traits -> Allocator -> operator new -> malloc -> OS
//


namespace lib {

template <typename Alloc>
struct allocator_traits
{
    template <typename U, typename... Args>
    static void construct(Alloc& alloc, U* ptr, const Args&... args)
    {
        if constexpr (/*Alloc has method construct*/)
        {
            alloc.construct(ptr, args...);
        }
        else
        {
            new (ptr) U(argc...);
        }
    }
};


template <typename T>
struct allocator
{
    T* allocate(size_t count)
    {
        //return reinterpret_cast<T*>(new char[count * sizeof(T)]);
        return operator new(count * sizeof(T));
    }

    void deallocate(T* ptr, size_t)
    {
        //delete[] reinterpret_cast<char*>(ptr);
        operator delete(ptr);
    }

    // template <typename U, typename... Args>
    // void construct(U* ptr, const Arg&... args)
    // {
    //     new (ptr) U(args...);
    // }

    template <typename U, typename... Args>
    void construct(U* ptr, const Arg&&... args)
    {
        // Args = int&
        //typeof(args) = int&
        new (ptr) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* ptr)
    {
        ptr->~U();
    }

    template <typename U>
    allocator(allocator<U>) {}:

    template <typename U>
    struct rebind
    {
        using other = allocator<U>;
    };  

};





}