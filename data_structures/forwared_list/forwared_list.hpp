#pragma once

#include <type_traits>

namespace mylib {

template <typename T>
class ForwaredList
{
    static_assert(std::is_move_assignable_v<T>);

public:

    struct base_node 
    {
        base_node* next_{nullptr};
        virtual ~base_node() = default;
    };

    struct node : base_node
    {
        T data_;
    };


    ForwaredList()
        : head_{&tail_}
        , tail_{head_}
        , size_{0} 
    {

    }

    ~ForwaredList()
    {
        if (size_ != 0)
        {
            base_node* curr_node = head_;
            int step_ = 0;
            while (step_ < size_)
            {
                base_node* node_to_delete = curr_node;
                curr_node = curr_node->next_;
                delete node_to_delete;
            }
        }
    }

    void insert_first(T data)
    {
        base_node* new_node = new node();

        new_node->next_ = head_->next_;
        head_->next_ = new_node;

        new_node->data_ = std::move(data);
    }

    void insert_last(T data)
    {
        base_node* new_node = new node();

        tail_->next_ = new_node;
        tail_ = new_node;

        new_node->next_ = head_;
        new_node->data_ = std::move(data);
    }

    T get_at(size_t idx)
    {
        base_node* sought_node = list_traverse(idx);

        if (sought_node != nullptr)
        {
            return curr_node->data_; // copy or should i return reference
        }   

        return {};
    }

    void insert_at(size_t idx, T data)
    {
        base_node* sought = list_traverse(idx);

        if (sought != nullptr)
        {
            curr->data_ = std::move(data);
        }
    }

    void delete_at(size_t idx)
    {
        if (idx > size_) { return nullptr; }

        base_node* node_to_delete = head_;
        base_node* prev = head_;
        size_t step = 0;
        while (step < idx)
        {
            prev = node_to_delete;
            node_to_delete = curr->next_;
        }

        prev->next_ = node_to_delete->netx_;

        delete node_to_delete;
    }

private:
    node* list_traverse(size_t idx)
    {
        if (idx > size_) { return nullptr; }

        node* curr = head_;
        size_t step = 0;;
        while (step < idx)
        {
            curr = curr->next_;
        }

        return curr;
    }

private:
    base_node* head_{nullptr};
    base_node* tail_{nullptr};
    size_t size_{0};
};


template <typename T>
class IntrusiveForwaredList
{

};

}