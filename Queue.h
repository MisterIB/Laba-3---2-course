#pragma once

#include <iostream>
#include <fstream>

template <typename T>
class Queue {
private:
	template <typename U>
	class Node {
    public:
		U value;
		Node<U>* next;

		Node(U value): value(value), next(nullptr) {}
	};

	Node<T>* head;
	Node<T>* tail;

public:
	Queue(): head(nullptr), tail(nullptr) {}

	bool is_empty() {
		return head == nullptr;
	}

	void push(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (is_empty()) {
			head = newNode;
			tail = newNode;
			return;
		}
		tail->next = newNode;
		tail = newNode;
	}

	T pop() {
		if (is_empty()) throw std::runtime_error("Queue is empty");
		Node<T>* temp = head;
		if (head->next != nullptr) head = head->next;
		T value = temp->value;
		delete temp;
		return value;
	}

	int32_t size() {
		int32_t size = 0;
		Node<T>* tempNode = head;
		while (tempNode) {
			tempNode = tempNode->next;
			size++;
		}
		return size;
	}

	void print() {
		Node<T>* tempNode = head;
		while (tempNode) {
			std::cout << tempNode->value << " ";
			tempNode = tempNode->next;
		}
		std::cout << std::endl;
	}

	void printInFile(std::ofstream& file) {
		Node<T>* tempNode = head;
		while (tempNode) {
			file << tempNode->value << " ";
			tempNode = tempNode->next;
		}
		file << std::endl;
	}
};
