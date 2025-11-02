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
			cout << current -> data << endl;
			if (current->next) cout << " ";
			current = current->next;
		}

		cout << endl;
	}
	void PrintReverse() const
	{
		Node* current = tail;
		while (current)
		{
			cout << current -> data << endl;
			if (current->prev) cout << " ";
			current = current->prev;
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
		Node* newNode = new Node{data, nullptr, head};
		if(head) {head -> prev = newNode;}
		else {tail = newNode;}

		head = newNode;
		count++;
	}
	void AddTail(const T& data)
	{
		Node* newNode = new Node{data, tail, nullptr};
		if (tail) {tail -> next = newNode;}
		else {head = newNode;}

		tail = newNode;
		count++;
	}

	// Removal
	bool RemoveHead()
	{
		Node* temp = head;
		head = head->next;
		if (head){head->prev = nullptr;}
		else {tail = nullptr;}
		delete temp;
		--count;
		return true;
	}
	bool RemoveTail()
	{
		Node* temp = tail;
		tail = tail->prev;
		if (tail){tail->next = nullptr;}
		else{head = nullptr;}
		delete temp;
		--count;
		return true;
	}
	void clear() 
	{
		while (head)
			RemoveHead();
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
	{
		if (this != &other) {
			clear();
			head = other.head;
			tail = other.tail;
			count = other.count;
			other.head = other.tail = nullptr;
			other.count = 0;
		}
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs)
	{
		if (this != &rhs) {
			clear();
			Node* current = rhs.head;
			while (current) {
				AddTail(current->data);
				current = current->next;
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
			current = current->next;
		}
	} 
	LinkedList(LinkedList<T>&& other) noexcept
	{
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList(){clear();}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


