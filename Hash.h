#pragma once

#include <iostream>
#include <fstream>

template <typename T>
class HList {
private:
	template <typename U>
	class Node {
    public:
		U value;
		std::string key;
		Node<U>* next;

		Node(std::string key, U value) : key(key), value(value), next(nullptr) {}
	};
public:

	Node<T>* head;
	Node<T>* tail;

public:
	HList() : head(nullptr), tail(nullptr) {}

	bool is_empty() {
		return head == nullptr;
	}

	T get(std::string key) {
		Node<T>* tempNode = head;
		while (tempNode and tempNode->key != key) tempNode = tempNode->next;
		if (tempNode and tempNode->key == key) return tempNode->value;
		throw std::runtime_error("The element is missing in the hash table");
	}

	void push_back(std::string key, T value) {
		Node<T>* tempNode = head;
		while (tempNode and tempNode->key != key) tempNode = tempNode->next;
		if (tempNode and tempNode->key == key) {
			tempNode->value = value;
			return;
		}
		Node<T>* newNode = new Node<T>(key, value);
		if (is_empty()) {
			head = newNode;
			tail = newNode;
			return;
		}
		tail->next = newNode;
		tail = newNode;
	}

	void remove(std::string key) {
		if (is_empty()) throw std::runtime_error("Hash table is empty");
		Node<T>* prevNode = NULL;
		Node<T>* curNode = head;
		while (curNode) {
			if (curNode->key == key) {
				if (curNode == head) {
					head = curNode->next;
				}
				else prevNode->next = curNode->next;
				delete curNode;
				return;
			}
			prevNode = curNode;
			curNode = curNode->next;
			return;
		}
		if (curNode->key == key) {
			if (prevNode) prevNode->next = nullptr;
			tail = prevNode;
			delete curNode;
		}
	}

	void print() {
		if (is_empty()) throw std::runtime_error("Hash table is empty");
		Node<T>* printNode = head;
		while (printNode) {
			std::cout << "<" << printNode->key << ", " << printNode->value << "> ";
			printNode = printNode->next;
		}
		std::cout << std::endl;
	}

	void printInFile(std::ofstream& file) {
		if (is_empty()) throw std::runtime_error("Hash table is empty");
		Node<T>* printNode = head;
		while (printNode) {
			file << printNode->key << " " << printNode->value << " ";
			printNode = printNode->next;
		}
	}

};

template <typename T>
struct Hash {
private:
	HList<T>* arr;
	int32_t amountOfItems, capacity;

	int32_t hashFunction(std::string key) {
		const int32_t k = 41, mod = 1e9 + 9;
		int64_t h = 0, m = 1;
		for (unsigned char character : key) {
			int32_t x = character - 'a' + 1;
			h = (h + m * x) % mod;
			m = (m * k) % mod;
		}
		return h % capacity;
	}
public:
	Hash() {
		capacity = 100;
		amountOfItems = 0;
		arr = new HList<T>[capacity];
	}
	void HSET(std::string key, T value) {//Проверка на 2 одинаковых
		int32_t index = hashFunction(key);
		HList<T> tempList = arr[index];
		tempList.push_back(key, value);
		arr[index] = tempList;
		amountOfItems++;
	}

	void HDEL(std::string key) {
		int32_t index = hashFunction(key);
		HList<T> tempList = arr[index];
		tempList.remove(key);
		arr[index] = tempList;
		amountOfItems--;
	}

	T HGET(std::string key) {
		int32_t index = hashFunction(key);
		HList<T> tempList = arr[index];
		return tempList.get(key);
	}
	void print() {
		for (int32_t i = 0; i < capacity; i++) {
			if (!arr[i].is_empty()) arr[i].print();
		}
		std::cout << std::endl;
	}

	void printInFile(std::ofstream& file) {
		for (int32_t i = 0; i < capacity; i++) {
			if (!arr[i].is_empty()) arr[i].printInFile(file);
		}
		file << std::endl;
	}
};
