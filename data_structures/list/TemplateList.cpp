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