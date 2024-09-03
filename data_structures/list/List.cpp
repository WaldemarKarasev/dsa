#include <iostream>
#include "List.h"


namespace MyContainers
{
    template <typename T>
    List<T>::List(T data)
    {
        DEBUG_PRINT("List::default_ctor()")
        head = new Node(0);
        Node* node = new Node(data);
        this->head->next = node;
    }

    template <typename T>
    List<T>::~List()
    {
        DEBUG_PRINT("List::dtor()")
    }

    template <typename T>
    void List<T>::push_back(T data)
    {
        DEBUG_PRINT("List::push_back()")
        Node* tmp = head;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }

        Node* newNode = new Node(data);
        tmp->next = newNode;

    }

    template <typename T>
    void List<T>::printList()
    {
        DEBUG_PRINT("List::printList()")
        Node* current = this->head;
        std::cout << "head->";
        while (current != nullptr)
        {
            if (current->next == nullptr)
            {
                std::cout << current->data << " ";
            }
            else
            {
                std::cout << current->data << "->";
            }

            current = current->next;
        }

        std::cout << "\n";
    }

    template <typename T>
    void List<T>::deleteNode(size_t NodeNumber)
    {
        DEBUG_PRINT("List::deleteNode()")
        Node* curr = nullptr;
        Node* prev = nullptr;

        curr = head;

        while (NodeNumber != 0)
        {
            prev = curr;
            curr = curr->next;

            NodeNumber--;
        }
        prev->next = curr->next;
        delete curr;
    }
}