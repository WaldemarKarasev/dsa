#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <type_traits>
#include <initializer_list>
#include <exception>

//#define MY_DEBUG
#include <lib/utility.hpp>

namespace lib::containers
{
    template <typename T> void construct(T* p, const T& rhs) { new (p) T(rhs); }   
    template <typename T> void destroy(T* p) noexcept { p->~T(); }
    template <typename FwdIter> void destroy(FwdIter first, FwdIter last) noexcept 
    {
        while (first != last)
        {
            destroy(&*first++);
        }
    }

    template <typename T>
    class vector_basis
    {

    protected:
        using size_type = size_t;
        size_type m_allocated_ = 0;
        size_type m_size_ = 0;
        T* m_data_ = nullptr;

        //vector_basis() = default;
        vector_basis(size_type allocSize = 0)
        : m_allocated_(allocSize), 
          m_data_( (allocSize == 0) ? nullptr
                                    : static_cast<T*>( ::operator new(sizeof(T) * m_allocated_))) 
        { DEBUG_PRINT("vector_basis(allocSize)"); }

        vector_basis(const vector_basis&) = delete;
        vector_basis& operator=(const vector_basis&) = delete;

        vector_basis(vector_basis&& moveFrom) noexcept
        {
            DEBUG_PRINT("vector_basis::move_ctor()");
            std::swap(m_allocated_, moveFrom.m_allocated_);
            std::swap(m_size_, moveFrom.m_size_);
            std::swap(m_data_, moveFrom.m_data_);
        }

        vector_basis& operator=(vector_basis&& moveFrom)
        {
            DEBUG_PRINT("vector_basis::move_assingment()");
            std::swap(m_allocated_, moveFrom.m_allocated_);
            std::swap(m_size_, moveFrom.m_size_);
            std::swap(m_data_, moveFrom.m_data_);
            return *this;
        }

        ~vector_basis()
        {
            DEBUG_PRINT("vector_basis()::dtor()");
            destroy(m_data_, m_data_ + m_size_);
            ::operator delete(m_data_);
        }
    };

    
    template <typename T>
    class vector final : private vector_basis<T>
    {
        static_assert(std::is_nothrow_move_constructible<T>::value ||
                      std::is_copy_constructible<T>::value, 
                      "T should be copy constructible or nothrow moveble.");
        
        using vector_basis<T>::m_allocated_;
        using vector_basis<T>::m_size_;
        using vector_basis<T>::m_data_;
    public:
        using size_type = size_t;

        vector() = default;
        vector(vector&&) = default;
        vector& operator=(vector&&) = default;
    
    private:
        // will be used in few places
        class dummy final {};

        using CopyArg = std::conditional_t<std::is_copy_constructible_v<T>,
                                            const vector&, dummy>;
        template <typename Arg>
        using TCopyCtorEnabled = std::void_t<decltype(Arg(std::declval<Arg &>()))>;
        
        template <typename Arg> 
        using TDefaultCtorEnabled = std::void_t<decltype(Arg())>;
    
    public:
        vector(CopyArg copyFrom) : vector_basis<T>{copyFrom.m_size_}
        {
            DEBUG_PRINT("vector::copy_ctor()");
            while (m_size_ < copyFrom.m_size_)
            {
                construct(m_data_ + m_size_, copyFrom[m_size_]);
                m_size_ += 1;
            }
            
            #if 0
            for(; m_size_ < copyFrom.m_size_; m_size_++)
            {
                new(m_data_ + m_size_) T(copyFrom.m_data_[m_size_]);
            }
            #endif
        }

        vector& operator=(CopyArg copyFrom)
        {
            DEBUG_PRINT("vector::copy_assignment()");
            vector tmp(copyFrom);
            swap(*this, tmp);
            return *this; //= std::move(copyFrom);
        }

        template <typename Arg = T, typename = TCopyCtorEnabled<Arg>>
        vector(std::initializer_list<T> list) : vector_basis<T>(list.size())
        {
            static_assert(std::is_same_v<Arg, T>, "Arg should be default type (T).");
            DEBUG_PRINT("vector(initializer_list)");
            for(auto it = list.begin(), end = list.end(); it != end; ++it, ++m_size_)
                //new(m_data_ + m_size_) T(*it);
                construct(m_data_ + m_size_, *it);
        }

        template <typename Arg = T, typename = TCopyCtorEnabled<Arg>>
        vector(size_type size, const T& copyVal) : vector_basis<T>{size}
        {
            static_assert(std::is_same_v<Arg, T>, "Arg should be dafault type (T).");
            DEBUG_PRINT("vector(size, copyVal)");
            for(; m_size_ < size; ++m_size_)
                //new (m_data_ + m_size_) T(copyVal);
                construct(m_data_ + m_size_, copyVal);
        }

        template <typename Arg = T, typename = TDefaultCtorEnabled<Arg>>
        explicit vector(size_type size = 0) : vector_basis<T>{size}
        {
            static_assert(std::is_same_v<Arg, T>, "Arg should be default type (T).");
            DEBUG_PRINT("vector(size)");
            for(; m_size_ < size; ++m_size_)
            {
                construct(m_data_ + m_size_, T()); // zero initialization
                //new (m_data_ + m_size_) T{};
            }
        }

        ~vector() = default;
        static void swap(vector& a, vector& b) noexcept
        {
            DEBUG_PRINT("vector::swap()");
            std::swap(a.m_allocated_, b.m_allocated_);
            std::swap(a.m_size_, b.m_size_);
            std::swap(a.m_data_, b.m_data_);
        }

    private:
        template <typename Arg>
        using ChooseCopy = 
                //std::enable_if_t<!std::is_nothrow_move_constructible_v<Arg>, int>;
                std::enable_if_t<std::is_copy_constructible_v<Arg> && !std::is_nothrow_move_constructible_v<Arg>, int>;
        
        template <typename Arg>
        using ChooseMove = 
                std::enable_if_t<std::is_nothrow_move_constructible_v<Arg>, int>;

        // Sub function for realloc.
        template <typename Arg = T, ChooseMove<Arg> = 0>
        void moveOrCopyT(T* dest, T& src)
        {
            DEBUG_PRINT("vector::moveOrCopyT(T* dest, T& src)_ChooseMove");
            new(dest) T(std::move(src));
        }

        // Sub function for realloc.
        template <typename Arg = T, ChooseCopy<Arg> = 0>
        void moveOrCopyT(T* dest, T& src)
        {
            DEBUG_PRINT("vector::moveOrCopyT(T* dest, T& src)_ChooseCopy");
            new(dest) T(src);
        }

        // Ctor for reallocation impl.
        vector(size_type allocated, dummy) : vector_basis<T>{allocated} { DEBUG_PRINT("vector(size_type allocated, dummy)"); }

        void realloc(size_type newAllocated)
        {
            size_type newSize = std::min(newAllocated, m_size_);
            vector newVector(newAllocated, dummy{});
            
            for(; newVector.m_size_ < newSize; ++newVector.m_size_)
            {
                moveOrCopyT(newVector.m_data_ + newVector.m_size_, m_data_[newVector.m_size_]);
            }

            *this = std::move(newVector);
        }

    public:
        template <typename Arg>
        void push(Arg&& value)
        {
            DEBUG_PRINT("vector::push(Arg&& value)");
            if(m_size_ == m_allocated_)
                realloc(2*m_allocated_ + 1);
            
            construct(m_data_ + m_size_, T{std::forward<Arg>(value)});
            //new (m_data_ + m_size_) T{std::forward<Arg>(value)};
            ++m_size_;
        }

        T top() const
        {
            if(m_size_ < 1)
                throw std::invalid_argument("trying top from empty vector");
            return m_data_[m_size_ - 1];
        }

        void pop()
        {
            DEBUG_PRINT("vector::pop()");
            if(m_size_ < 1)
                throw std::invalid_argument("trying pop from empty vector");
            m_data_[m_size_ - 1].~T();
            --m_size_;
        }

        T& back() noexcept { return m_data_[m_size_ - 1]; }
        const T& back() const noexcept { return m_data_[m_size_ - 1]; }

        T& front() noexcept { return *m_data_;}
        const T& front() const noexcept { return *m_data_; }

        class iterator final
        {
            friend vector;
            T* m_ptr_;

            iterator(T* ptr) noexcept : m_ptr_(ptr) {}

        public:
            using difference_type = ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            iterator(const iterator&) = default;
            iterator& operator=(const iterator&) = default;
            T& operator*() const noexcept { return *m_ptr_; }
            iterator& operator++() noexcept
            {
                ++m_ptr_;
                return *this;
            }
            iterator operator++(int) noexcept
            {
                iterator copy{*this};
                ++m_ptr_;
                return copy;
            }
            iterator &operator--() noexcept {
            --m_ptr_;
            return *this;
            }
            iterator operator--(int) noexcept {
            iterator copy{*this};
            --m_ptr_;
            return copy;
            }
            bool operator==(const iterator &second) const noexcept = default;
            bool operator!=(const iterator &second) const noexcept = default;
        };

        class const_iterator final
        {
            iterator m_it_;

        public:
            using difference_type = ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;
            const_iterator(const iterator& it) noexcept : m_it_(it) {}
            const_iterator(const const_iterator&) = default;
            const_iterator& operator=(const const_iterator&) = default;

            const T& operator*() const noexcept { return *m_it_; }

            const_iterator &operator++() {
                ++m_it_;
                return *this;
            }
            const_iterator operator++(int) { return m_it_++; }
            const_iterator &operator--() {
                --m_it_;
                return *this;
            }
            const_iterator operator--(int) { return m_it_--; }

            bool operator==(const const_iterator &second) const noexcept = default;
            bool operator!=(const const_iterator &second) const noexcept = default;

        };

        T& operator[](size_type idx) noexcept { return m_data_[idx];}
        const T& operator[](size_type idx) const noexcept { return m_data_[idx]; }

        T* data() const noexcept { return m_data_;}
        size_type allocated() const noexcept { return m_allocated_; }
        size_type size() const noexcept { return m_size_;}

        bool operator==(const vector<T>& vec) const noexcept
        {
            DEBUG_PRINT("vector::operator==()");
            if(m_size_ != vec.m_size_)
            {
                return false;
            }
            if(this == &vec)
            {
                return true;
            }

            for (size_type i = 0; i < m_size_; ++i)
            {
                if(m_data_[i] != vec.m_data_[i])
                    return false;
            }

            return true;
        }

        void dump(std::ostream& os) const // ???
        {
            os << "{ ";
            for (size_type i = 0; i < m_size_; ++i)
            {
                os << m_data_[i];
                if(i != m_size_ - 1) os << ", ";
                else os << " ";
            }
            os << "}\n";
        }

    };
}

template <typename T>
std::ostream& operator<<(std::ostream& os, containers::vector<T>& vec)
{
    vec.dump(os);
    return os;
}

#endif