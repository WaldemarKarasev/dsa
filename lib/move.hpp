#include <type_traits>

namespace lib {

template <typename T>
std::remove_reference_t<T>&& move(T&& x)
{
    return static_cast<std::remove_reference_t<T>&&>(x);
}

template <typename T>
T&& forward(std::remove_reference_t<T>& x)
{
    return static_cast<T&&>(x);
}

// rarely used
template <typename T>
T&& forward(<std::remove_reference_t<T>&& x)
{
    return static_cast<T&&>(x);
}

}