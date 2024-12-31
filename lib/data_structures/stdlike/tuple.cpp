#include <iostream>
#include <tuple>

template <typename... Types>
struct tuple;


template <typename Head, typename... Tail>
struct tuple<Head, Tail...>
{
private:
    Head head;
    tuple<Tail...> tail;

    template <size_t N, typename... Types>
    friend decltype(auto) get(tuple<Types...>&);
public:

    tuple(Head head, Tail args...) 
            : head(head), tail(std::forward<Tail>(args)...) 
    {}
};

// implement: tuple.size tuple.element
template <>
struct tuple<> {};

struct tuple_cat_tag {};

template <typename... Us>
auto tuple_cat(tuple<> t, tuple<Us...>& u)
{
    return u;
}

template <typename... Ts, typename... Us>
auto tuple_cat(tuple<Ts...>& t, tuple<Us...> u)
{
    return tuple(tuple_cat_tag(), t.head, tuple_cat(t.tail, u));
}


template <size_t N, typename... Types>
decltype(auto) get(tuple<Types...>& t)
{
    if constexpr (N == 0)
    {
        return t.head;
    }
    else{
        return get<N-1>(t.tail);
    }
}


template <typename... Types>
void f()
{
    std::tuple<Types...> t;

    t.template get<1>(); // if get was a memver function of tuple class
}

int main()
{

    {
    
    }


    //std::tuple<int, double, char>

    std::tuple t{1, 2.0, 'c'};

    //auto d = std::get<1>(std::move(t)); // moved value
    //auto d = std::get<1>(t);
    auto& d = std::get<1>(t);
    //auto&& d = std::get<1>(std::move(t));

    // Structured bindings since c++17
    // auto [x, y, z] = t;
    // auto& [x, y, z] = t;
    auto&& [x, y, z] = t;

    
}