#include <iostream>

namespace lib {

    template <typename T, typename Alloc = std::allocator<T>>
    class list
    {
    public:
        struct base_node
        {
            base_node* prev;
            base_node* next;
        }

        struct node : base_node
        {
            T value;
        }

        list()
            : m_base{&m_base, &m_base} {}

        explicit list(const Alloc& alloc) 
            : m_base{&m_base, &m_base}, m_allocator(alloc) {}

    private:
        base_node m_base;
        size_t m_count;
        typename Alloc::template rebind<Node>::other m_allocator;
    };

}