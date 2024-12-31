#include "stddef.h"
#include <stdint.h>
#include <type_traits>
#include <iterator>


#include "allocator.hpp"

namespace lib
{
    template <typename T, typename Alloc = std::allocator<T>>
    class vector
    {
    public:
        using value_type = T;
        using size_type = size_t;

    private:
        template <bool IsConst>
        class base_iterator
        {
        public:
            using pointer_type = std::conditional_t<IsConst, const T*, T*>;
            using reference_type = std::conditional_t<IsConst, const T&, T&>;
            using value_type = T;
            using AllocatorTraits = std::allocator_traits<Alloc>;

        private:
            pointer_type m_ptr;
            base_iterator(T* ptr) : m_ptr(ptr) {} 

            friend class vector<T>;
        public:
            base_iterator(const base_iterator&) = default;
            base_iterator& operator=(const base_iterator&) = default; 

            reference_type operator*() const { return *m_ptr; }
            pointer_type operator->() const { return m_ptr; }
            
            base_iterator& operator++() 
            { 
                ++m_ptr;
                return *this;    
            }
            base_iterator operator+(int)
            {
                iterator copy = *this;
                ++m_ptr;
                return copy;
            }

            operator base_iterator<true>() const
            {
                return {m_ptr};
            }
        };


    public:

        using iterator = base_iterator<false>;
        using const_iterator = base_iterator<true>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        vector& operator=(const vector& other)
        {
            Alloc newalloc = AllocTraits::propagate_on_container_copy_assignment::value ?
                other.allocator : allocator;

            T* newarr = AllocTraits::allocate(newalloc, other.m_cap);
            size_t i = 0;
            try
            {
                for (; i < other.m_size; ++i)
                {
                    AllocTraits::construct(newalloc, newarr + i, other[i]);
                }
            }
            catch(...)
            {
                for (size_t j = 0; j < i; ++j)
                {
                    AllocTraits::destroy(newalloc, newarr + j);
                }
                AllocTraits::deallocate(newalloc, m_data, m_cap);
                throw;                
            }

            for (size_t i = 0; i < m_size; ++i)
            {
                AllocTraits::destroy(newalloc, m_data + i);
            }
            AllocTraits::deallocate(newalloc, m_data, m_cap);
           
           
            m_data = newarr;
            m_size = other.m_size;
            m_cap = other.m_cap;
            allocator = newalloc;
        }

        iterator begin()
        {
            return base_iterator{m_data};
        }
        
        iterator end()
        {
            return base_iterator(m_data + m_size);
        }

        const_iterator begin() const
        {
            return base_iterator{m_data};
        }
        
        const_iterator end() const
        {
            return base_iterator(m_data + m_size);
        }

        const_iterator cbegin() const
        {
            return base_iterator{m_data};
        }
        
        const_iterator cend() const
        {
            return base_iterator(m_data + m_size);
        }


        void reserve(size_t newcap)
        {
            if (newcap <= m_cap)
            {
                return;
            }

            //T* newarr = reinterpret_cast<T*>(new char[newcap]);
            // T* newarr = allocator.allocate(newcap);
            T* newarr = AllocTraits::allocate(allocator, newcap);

            size_t index = 0;
            try {
                for (; index < m_size; ++index)
                {
                    //newarr[index] = arr_[index]; // ub
                    //new(newarr + index) T(newarr [index]); // placement new
                    //allocator.construct(newarr + index, m_data[index]);
                    AllocTraits::construct(allocator, newarr + index, std::move_if_noexcept(m_data[index]));
                }
            } catch (...) {
                for (size_t newindex = 0; newindex < m_size; ++index)
                {
                    //newarr[index] = arr_[index]; // ub
                    //new(newarr + newindex)->~T(); // destruct all already created elements
                    //allocator.destroy(newarr + newindex);
                    AlocaTraits::destroy(allocator, newarr + newindex);
                }
                //delete[] reinterpret_cast<char*>(newarr); // delete allocated memory
                //allocator.deallocate(newarr, newcap);
                AllocTraits::deallocate(allocator, newarr, newcap);
                throw;
            }

            for (size_t index = 0; index < m_size; ++index)
            {
                //(m_data + index)->~T();
                //allocator.destroy(m_data + index);
                AllocTraits::destroy(allocator, m_data + index);
            }
            //delete reinterpret_cast<char*>(m_data);
            //allocator.deallocate(m_data, m_cap);
            AllocTraits::deallocate(m_data, m_cap);

            m_data = newarr;
            m_cap = newcap; 
        }
        
        void push_back(const T& value)
        {
            emplace_back(value);
        }

        void push_back(T&& value)
        {
            emplace_back(std::move(value));
        }

        template <typename... Args>
        void emplace_back(Args&&... args)
        {
            if (m_size == m_cap)
            {
                reserve(m_size == m_cap)
                {
                    reserve(m_cap > 0 : m_cap * 2 ? 1);
                }
                AllocTraits::construct(allocator, m_data + m_size,
                        std::forward<Args>(args)...);
                ++m_size;
            }
        }


    private:
        T* m_data;
        size_type m_size;
        size_type m_cap;
        Alloc allocator;
    };


    template <>
    class vector<bool>
    {
        char* m_data;
        size_t m_size;
        size_t m_cap;

        struct BitReference
        {
            char* cell;
            uint8_t index;

            BitReference(char* cell, uint8_t index)
                    : cell(cell), index(index) {}

            void operator=(bool b)
            {
                if (b)
                {
                    *cell |= (1 << index);                    
                }
                else
                {
                    *cell &= ~(1 << index);
                }
            }

            operator bool() const
            {
                return *cell & (1 << index);
            }
        };
        

    public:
        BitReference operator[](size_t index)
        {
            return BitReference{m_data + index / 8, index & 8};
        }

    };

}

#include <vector>
#include <iostream>
int main()
{
    std::vector<int> v(10);
    std::vector<int>::iterator x = v.begin() + 5;
    v.push_back(1);
    std::cout << *x << std::endl;
}
