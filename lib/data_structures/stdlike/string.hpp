#include <stddef.h>

namespace lib
{
    class String
    {
        char* m_data = nullptr;
        size_t m_size = 0;
        size_t m_cap = 0;
    };
}