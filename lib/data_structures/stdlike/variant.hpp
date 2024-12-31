#include <iostream>
#include <type_traits>
#include <vector>
#include <string>


// Implement std::visit

namespace lib {
    
template <typename... Types>
class Variant;

// template <typename T, typename... Types>
// struct get_index_by_type
// {
    
// };

template <typename... Types>
const size_t get_index_by_type = 0;

template <typename T, typename... Types>
struct VariantAlternative
{
    static const size_t index = get_index_by_type<T, Types...>;

    VariantAlternative() {}
    ~VariantAlternative() {}

    VariantAlternative(const T& value)
    {
        auto* this_variant = static_cast<Variant<Tytpes...>*>(this);
        new (this_variant->buffer) T(value);
        this_variant->active_index = index;
    }

    VariantAlternative(T&& value)
    {
        auto* this_variant = static_cast<Variant<Tytpes...>*>(this);
        new (this_variant->buffer) T(std::move(value));
        this_variant->active_index = index;
    }

    void destroy()
    {
        auto* this_variant = static_cast<Variant<Types...>*>(this);
        if (this_variant->active_index == index)
        {
            reinterpret_cast<T*>(this_variant->buffer)->~T();
        }
    }

};

template <typename... Types>
union VariadicUnion;

template <typename Head, typename... Tail>
union VariadicUnion<Head, Tail...>
{
    Head head;
    VariadicUnion<Tail...> tail;

};

template <typename Head>
union VariadicUnion<Head>
{
    Head head;
};

template <typename... Tail>
struct max_sizeof;

template <typename Head, typename... Tail>
struct max_sizeof<Head, Tail...> {
    static constexpr size_t value = 
    std::max(sizeof(Head), max_sizeof<Tail...>::value);
};

template <typename T>
struct max_sizeof<T> {
    static const size_t value = sizeof(T);
};

template <typename... Types>
const size_t max_sizeof_v = max_sizeof<Types...>::value;

/*
    Variant<int, double, char> : VariantAlternatives<int, int, double, char>
                                 VariantAlternatives<double, int, double, char>
                                 VariantAlternatives<char, int, double, char>
*/

template <typename... Types>
class Variant : private VariantStorage, private VariantAlternative<Types, Types...>... 
{
private:
    //VariadicUnion<Types...> var_un;
    char buffer[max_sizeof_v<Types...>];
    size_t active_index;

    template <typename T, typename... Ts>
    friend struct VaraintAlternative;

public:
    using VariantAlternative<Types, Types...>::VariantAlternative...;


    ~Variant()
    {
        (VariantAlternative<Types, Types...>::destroy(), ...);
    }
};

}

int main()
{
    lib::Variant<int, double, std::string> v(5);
}