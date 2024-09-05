#pragma once

#include <type_traits>

namespace lib::containers {

template <typename T>
class ForwaredList
{
    static_assert(std::is_move_assignable_v<T>);

public:
    using size_type = std::size_t;

public:

    struct base_node 
    {
        base_node* next_{nullptr};
        virtual ~base_node() = default;


        void hook(base_node* node)
        {
            this->next_ = node->next_;
            node->next_ = this;
        }

    };

    struct node : base_node
    {
        T data_;
    };


    ForwaredList()
        : top_node_{top_node_->next_}
        , size_{0} 
    {

    }

    ~ForwaredList()
    {
        if (size_ != 0)
        {
            base_node* node = top_->next_;

            if (node != top_)
            {
                size_type step_ = 0;
                while (step_ < size_)
                {
                    base_node* node_to_delete = node;
                    node = node->next_;
                    delete node_to_delete;
                }
            }
        }
    }


    void push_front(T value)
    {

    }

    template <typename... Args>
    void emplace_front(Args&&... args)
    {

    }

    T get_at(size_type idx)
    {
        return get_at_impl(idx);
    }

private:
    void insert_first(T data)
    {
        node* new_node = create_node(std::move(data));
        new_node->hook(top_->next_);
    }

    void insert_last(T data)
    {
        base_node* new_node = new node();

        tail_->next_ = new_node;
        tail_ = new_node;

        new_node->next_ = head_;
        new_node->data_ = std::move(data);
    }

    T get_at_impl(size_type idx)
    {
        base_node* sought_node = list_traverse(idx);

        if (sought_node != nullptr)
        {
            return curr_node->data_; // copy or should i return reference
        }   

        return {};
    }

    void insert_at(size_type idx, T data)
    {
        base_node* sought = list_traverse(idx);

        if (sought != nullptr)
        {
            curr->data_ = std::move(data);
        }
    }

    void delete_at(size_type idx)
    {
        if (idx > size_) { return nullptr; }

        base_node* node_to_delete = head_;
        base_node* prev = head_;
        size_type step = 0;
        while (step < idx)
        {
            prev = node_to_delete;
            node_to_delete = curr->next_;
        }

        prev->next_ = node_to_delete->netx_;

        delete node_to_delete;
    }

private:

    node* create_node(T data)
    {
        node* created_node = new node();
        create_node->data = std::move(data);
        return create_node;
    }


    node* list_traverse(size_type idx)
    {
        if (idx > size_) { return nullptr; }

        node* curr = head_;
        size_type step = 0;;
        while (step < idx)
        {
            curr = curr->next_;
        }

        return curr;
    }

private:
    base_node* top_{nullptr};
    size_type size_{0};
};

}