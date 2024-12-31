#include <iostream>

namespace lib {
template <typename T>
class optional
{
private:
    char m_value[sizeof(T)];
    bool m_initialized = false;
public:
    optional(const T& newval) : m_initialized(true)
    {
        new (m_value) T(newval);
    }

    optional() = default;
    ~optional()
    {
        if (m_initialized)
        {
            reinterpret_cast<T*>(val)->~T();
        }
    }

    bool has_value() const
    {
        return m_initialized;
    }

    operator bool() const 
    {
        return m_initialized;
    }

    T& opearator*() & 
    {
        return reinterpret_cast<T&>(*m_value);
    }

    const T& operator*() const &
    {
        return reinterpret_cast<const T&>(*m_value);
    }

    T&& opearator*() && 
    {
        return reinterpret_cast<T&&>(*m_value);
    }

    const T&& operator*() const &&
    {
        return reinterpret_cast<const T&&>(*m_value);
    }

    // since c++23
    decltype(auto) value(this auto&& self)
    {
        if (!m_initialized)
        {
            throw std::bad_optional_access();
        }
        using DesiredType = decltype(std::forward_like<decltype(self)>(std::declval<T>()));
        return reinterpret_cast<DesiredType>(*self.m_value);
    }

};
} // namespace lib