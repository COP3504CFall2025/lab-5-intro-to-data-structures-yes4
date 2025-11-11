#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
        Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
	};

	// Behaviors
	void printForward() const {
		Node* current = head;
        while (current) {
        	std::cout << current->data << " ";
            current = current->next;
		}
        std::cout << std::endl;
	}
	void printReverse() const {
		Node* current = tail;
        while (current) {
			std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node* getHead() { return head; }
	const Node* getHead() const { return head; }
	Node* getTail() { return tail; }
	const Node* getTail() const { return tail; }

	// Insertion
	void addHead(const T& data) {
		Node* newNode = new Node(data);
        newNode->next = head;
        if (head != nullptr) {
			head->prev = newNode;
		}
		else {
			tail = newNode;
        }
        head = newNode;
        count++;
	}


	void addTail(const T& data) {
		Node* newNode = new Node(data);
        newNode->prev = tail;

        if (tail != nullptr) {
			tail->next = newNode;
        }
        else {
			head = newNode;
        }

        tail = newNode;
        count++;
    }

	// Removal
	bool removeHead() {
		if (head == nullptr) { return false; }
        Node* tempNode = head;
        head = head->next;

		if (head != nullptr) {
			head->prev = nullptr;
        }
		else {
			tail = nullptr;
        }
        delete tempNode;
        count--;
        return true;
    }
	bool removeTail() {
		if (tail == nullptr) { return false; }
		Node* tempNode = tail;
		tail = tail->prev;

		if (tail != nullptr) {
			tail->next = nullptr;
		}
		else {
			head = nullptr;
		}
		delete tempNode;
		count--;
		return true;
    }
	void clear() {
		Node* current = head;
        while (current != nullptr) {
   			Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this != &other) {
			head = other.head;
			other.head = nullptr;
			tail = other.tail;
			other.tail = nullptr;
			count = other.count;
			other.count = 0;
		}
		return *this;
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this != &rhs) {
 			clear();
            Node* current = rhs.head;
            while (current != nullptr) {
				addTail(current->data);
                current = current->next;
            }
        }
        return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {};
	LinkedList(const LinkedList<T>& list) : head(list.head), tail(list.tail), count(list.count) {
		Node* current = other.head;
		while (current != nullptr) {
			addTail(current->data);
			current = current->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
	}

	~LinkedList() { clear(); }

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


