#pragma once

#include <type_traits>

namespace lib::containers {

template <typename T>
class ForwaredList
{
    static_assert(std::is_move_assignable_v<T> && std::is_move_constructible_v<T>);
    static_assert(std::is_copy_assignable_v<T> && std::is_copy_constructible_v<T>);

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
        : top_{top_->next_}
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
        return get_at_(idx);
    }

private:
    void insert_first(T data)
    {
        node* new_node = create_node(std::move(data));
        new_node->hook(top_->next_);
        ++size_;
    }

    T get_at_(size_type idx)
    {
        base_node* last = list_traverse(idx);

        if (last != nullptr)
        {
            return static_cast<node*>(last)->data_; // copy or should i return reference
        }   

        return {};
    }

    void insert_at(size_type idx, T data)
    {
        base_node* nd_to_hook = list_traverse(idx);

        if (nd_to_hook != nullptr)
        {
            node* new_node = create_node(std::move(data));
            new_node->hook(nd_to_hook);
            ++size_;
        }
    }

    void delete_at(size_type idx)
    {
        if (idx > size_) { return; }

        base_node* before_node_to_delete = list_traverse(idx);
        base_node* node_to_delete = before_node_to_delete->next_;
        
        node_to_delete->next_->hook(before_node_to_delete);

        delete node_to_delete;
        --size_;
    }

private:

    node* create_node(T data)
    {
        node* created_node = new node();
        created_node->data = std::move(data);
        return created_node;
    }


    base_node* list_traverse(size_type idx)
    {
        if (idx > size_) { return nullptr; }

        base_node* trav_node = top_->next_;
        size_type step = 0;;
        while (step < idx)
        {
            trav_node = trav_node->next_;
            ++step;
        }

        return trav_node;
    }

private:
    base_node* top_{nullptr};
    size_type size_{0};
};

}