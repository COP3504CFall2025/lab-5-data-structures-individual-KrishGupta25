#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
	};
public:

	// Behaviors
	void printForward() const
	{
		Node* current = head;
		while (current)
		{
			cout << current -> data;
			if (current -> next) cout << " ";
			current = current -> next;
		}

		cout << endl;
	}

	void PrintReverse() const
	{
		Node* current = tail;
		while (current)
		{
			cout << current -> data;
			if (current -> prev) cout << " ";
			current = current -> prev;
		}

		cout << endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node* getHead() { return head; }
	const Node* getHead() const { return head; }
	Node* getTail() { return tail; }
	const Node* getTail() const { return tail; }

	// Insertion
	void AddHead(const T& data)
	{
		Node* current = new Node(data);
		current -> next = head;
		current -> prev = nullptr;

		if(head) //if there exists a head then do this
		{
			head -> prev = current;
		}
		else //there is no head then that means the list is empty so set this new node to be the tail
		{
			tail = current;
		}

		head = current;
		count++;
	}

	void AddTail(const T& data)
	{
		Node* current = new Node(data);
		current -> next = nullptr;
		current -> prev = tail;

		if(tail) //if tail exists then do this
		{
			tail -> next = current;
		}
		else //this is the only node which means its both the head and tail
		{
			head = current;
		}

		tail = current;
		count++;
	}

	// Removal
	bool RemoveHead()
	{
		if(!head)
		{
			return false;
		}

		Node* temp = head;
		if(head -> next != nullptr) 
		{
			head = head -> next;
			head -> prev = nullptr;
		}
		else
		{
			head = nullptr;
			tail = nullptr;
		}

		delete temp;
		count--;
		return true;
	}

	bool RemoveTail()
	{
		if(!tail)
		{
			return false;
		}

		Node* temp = tail;

		if(tail -> prev != nullptr)
		{
			tail = tail -> prev;
			tail -> next = nullptr;
		}
		else
		{
			tail = nullptr;
			head = nullptr;
		}

		delete temp;
		count--;
		return true;
	}

	void Clear() 
	{
		while(head) { RemoveHead(); }
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
	{
		if(this != &other)
		{
			Clear();
			head = other.head;
			tail = other.tail;
			count = other.count;
			other.head = nullptr;
			other.tail = nullptr;
			other.count = 0;
		}
		return *this;
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs)
	{
		if(this != &rhs)
		{
			Clear();
			Node* current = rhs.head;
			while (current)
			{
				AddTail(current -> data);
				current = current ->next;
			}
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0)
	{
		Node* current = list.head;
		while (current)
		{
			AddTail(current -> data);
			current = current -> next;
		}
	} 

	LinkedList(LinkedList<T>&& other) noexcept
	{
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList(){Clear();}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


