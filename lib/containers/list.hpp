#pragma once

#include <cstddef>

#define MY_DEBUG
#include <lib/utility.hpp>

namespace lib::containers 
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


#if 0
#include <iostream>
#include <string>

using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();
	
	void pop_front();
	void push_back(T data);
	void clear();
	int GetSize() { return size; }
	T& operator [](const int index);

	void push_front(T data);
	void insert(T value, int index);
	void removeAt(int index);
	void pop_back();

private:

	template<typename T> 
	class Node
	{
	public:
		Node* pNext;
		T data;

		Node(T data=T(), Node* pNext = nullptr)
		{
			this->data = data;;
			this->pNext = pNext;
		}

	};

	int size;
	Node<T> *head;
};



template<typename T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
inline void List<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->pNext;

	delete temp;

	size--;
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;	
		}
		current->pNext = new Node<T>(data);
	}

	size++;
}

template<typename T>
void List<T>::clear()
{
	while (size)
	{
		pop_front();
	}
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{

	if (index==0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;

		delete toDelete;
		size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(size - 1);	
}
#endif