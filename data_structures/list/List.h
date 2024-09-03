#ifndef LIST_H
#define LIST_H
#include <cstddef>

#define MY_DEBUG
#include "../debug.h"

namespace MyContainers 
{
    template <typename T>
    class List
    {
    private:
        
        struct Node
        {
            T data = 0;
            Node* next;

            Node()
            {
                data = 0;
                next = nullptr;
            }
            Node(T data)
            : data(data)
            , next(nullptr)
            {}

        };
        
        Node* head = nullptr;

    public:
        List() { head = nullptr; }
        List(T data);
        ~List();

        void push_back(T data);
        void printList();
        void deleteNode(size_t NodeNumber);
    };
}

#endif