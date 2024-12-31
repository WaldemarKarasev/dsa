#include <iostream>
#include <type_traits>

namespace lib {

template <typename T>
class function;

template <typename Ret, typename... Args>
class function<Ret(Args...)>
{
private:
    struct Base {
        virtual ~Base() = default;
        virtual Ret call(Args...) = 0;
    };

    template <typename F>
    struct Derived : Base
    {
        F f;
        ~Derived() override = default;
        Derived(const F& f) : f(f) {}
        Derivede(F&& f) : f(std::move(f)) {}

        Ret call(Args... args) override {
            if constexpr (std::is_member_function_pointer_v<F>) {
                return //head.f(tail); TODO
            } else if (std::is_member_object_pointer_v<F>) {
                return ; // TODO: return pointer to member pointer
            } else{
                return f(std::forward<Args>(args)...);
            }
        }         
    }


    
    
private:
    // Small Object Optimization
    void* fptr;
    static constexpr size_t BUFFER_SIZE = 16;
    alignas(max_align_t) char buffer[BUFFER_SIZE];

    using invoke_ptr_t = Ret(*)(void*, Args...);
    using destroy_ptr_t = void(*)(void*); 

    invoke_ptr_t invoke_ptr;
    destroy_ptr_t destroy_ptr;


public:

    static Ret invoker(void* fptr, Args... args)
    {
        return (*fptr)(std::forward<Args>(args)...);
    }
    template <typename F>
    static void destroyer(F* fptr)
    {
        if constexpr (sizeof(F) > BUFFER_SIZE)
        {
            delete fptr;
        } else
        {
            fptr->~F();
        }
    }

    template <typename F>
    function(auto&& func)
        : invoke_ptr(reinterpret_cast<invoke_ptr_t>(&invoker<F>))
        , destroy_ptr(reinterpret_cast<destroy_ptr_t>(&destroyer<F>))
    {
        if constexpr (sizeof(F) > BUFFER_SIZE) {
            fptr = new F(func);
        } else {
            new (buffer) F(func);
            fptr = buffer;
        }
    }

    function(auto&& func)
        : fptr<new Derived<
            std::remove_reference_t<decltype(func)>>((func)) {} // TODO: what if decltype(func) == const T&

    ~function()
    {
        destroyer(fptr);
    }

    Ret operator()(Args... args) const
    {
        return invoke_ptr(fptr, std::forward<Args>(args)...);
        //return fptr->call(std::forward<Args>(args)...);
    }
};

}   