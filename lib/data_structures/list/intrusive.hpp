#pragma once

namespace lib::containes {

template <typename T>
struct IntrusiveForwardListNode
{
    using Node = IntrusiveForwardListNode;

    // Interface
    Node* Next() { return next_; }
    T* AsItem()  { return static_cast<T*>(this); }
    
    IntrusiveForwardListNode* next_;
};


template <typename T>
class IntrusiceForwardList
{
    using Node = IntrusiveForwardListNode<T>;


};

} // namespace lib::containers