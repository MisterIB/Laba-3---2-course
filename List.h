#pragma once

#include <iostream>
#include <fstream>

template <typename T>
class List {
private:
	template <typename U>
	class Node {
    public:
		U value;
		Node<U>* next;
		Node<U>* prev;

		Node(U value) : value(value), next(nullptr), prev(nullptr) {}
	};

	Node<T>* head;
	Node<T>* tail;

public:
	List() : head(nullptr), tail(nullptr) {}

	bool is_empty() {
		return head == nullptr;
	}

	Node<T>* find(T value) {
		Node<T>* tempNode = head;
		while (tempNode and tempNode->value != value) tempNode = tempNode->next;
		if (tempNode and tempNode->value == value) return tempNode;
		else throw std::runtime_error("The item is missing from the list");
	}

	void push(int32_t index, T value) {
		if (is_empty()) throw std::runtime_error("List is empty");
		Node<T>* curNode = head;
		Node<T>* prevNode = NULL;
		for (int32_t i = 1; curNode; i++) {
			if (index == 0) {
				push_front(value);
				return;
			}
			prevNode = curNode;
			curNode = curNode->next;
			if (i == index) {
				Node<T>* newNode = new Node<T>(value);
				prevNode->next = newNode;
				newNode->next = curNode;
				return;
			}
			if (curNode->next == nullptr) {
				push_back(value);
				return;
			}
		}

	}

	void push_front(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (is_empty()) {
			head = newNode;
			tail = newNode;
			return;
		}
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	void push_back(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (is_empty()) {
			head = newNode;
			tail = newNode;
			return;
		}
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}

	void remove_front() {
		if (is_empty()) throw std::runtime_error("List is empty");
		Node<T>* tempNode = head;
		head = head->next;
		head->prev = nullptr;
		delete tempNode;
	}

	void remove_back() {
		if (is_empty()) throw std::runtime_error("List is empty");
		Node<T>* tempNode = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete tempNode;
	}

	void print() {
		if (is_empty()) throw std::runtime_error("List is empty");
		Node<T>* printNode = head;
		while (printNode) {
			std::cout << printNode->value << " ";
			printNode = printNode->next;
		}
		std::cout << std::endl;
	}

	void printInFile(std::ofstream& file) {
		if (is_empty()) throw std::runtime_error("List is empty");
		Node<T>* printNode = head;
		while (printNode) {
			file << printNode->value << " ";
			printNode = printNode->next;
		}
		file << std::endl;
	}

};
