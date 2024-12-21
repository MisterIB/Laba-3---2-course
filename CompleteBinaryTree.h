#pragma once

#include <iostream>
#include <cmath>
#include <fstream>

template <typename T>
class CompleteBinaryTree {
private:
	template <typename U>
	struct CBTList {
	private:
		template <typename D>
		struct Node {
			D value;
			Node<D>* next;
			Node<D>* prev;
			Node<D>* left;
			Node<D>* right;

			Node(D value) : value(value), next(nullptr), left(nullptr), right(nullptr) {}
		};

		Node<U>* head;
		Node<U>* tail;
		int32_t currentSize = 0;
		int32_t LeftOrRight = 0;
		int32_t depth = 1;

	public:
		CBTList() : head(nullptr), tail(nullptr) {}

		bool is_empty() {
			return head == nullptr;
		}

		void push(U value) {
			Node<U>* newNode = new Node<T>(value);
			if (is_empty()) {
				head = newNode;
				tail = newNode;
				return;
			}
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			currentSize++;
			depth = 1 + floor(log2(currentSize));
			Node<U>* tempNode = tail;
			for (int32_t i = 0; i < currentSize - depth; i++){
				tempNode = tempNode->prev;
			}
			if (LeftOrRight == 0) tempNode->left = newNode;
			if (LeftOrRight == 1) tempNode->right = newNode;
		}

		void pop() {
			if (is_empty()) throw std::runtime_error("Tree is empty");
			Node<T>* tempNode = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete tempNode;
		}

		int32_t size() {
			int32_t size = 0;
			Node<U>* tempNode = head;
			while (tempNode) {
				tempNode = tempNode->next;
				size++;
			}
			return size;
		}

		U find(U value) {
			Node<U>* tempNode = head;
			while (tempNode) {
				if (tempNode->value == value) return value;
				tempNode = tempNode->next;
			}
			throw std::runtime_error("The element is missing in the tree");
		}

		bool chek() {
			Node<U>* tempNode = head;
			depth = floor(log2(currentSize));
			int32_t sizeCurrentDepth = pow(2, depth);
			for (int32_t i = 0; i < pow(2, depth - 1); i++) tempNode = tempNode->next;
			for (int32_t i = 0; i < sizeCurrentDepth; i++) {
				if (tempNode-> left == nullptr and tempNode->right != nullptr) return false;
			}
			return true;
		}

		void print() {
			Node<U>* tempNode = head;
			Node<U>* sizeNode = head;
			int32_t size = 0;
			while (sizeNode) {
				sizeNode = sizeNode->next;
				size++;
			}
			int32_t depth = 1 + floor(log2(size));
			int32_t space = 15 * (depth - 2);
			for (int32_t currentDepth = 0, y = pow(2, depth); currentDepth < depth; currentDepth++, y = y / 2, space = floor(space / 2)) {
				int32_t amountOfItemsPerLevel = pow(2, currentDepth);
				for (int32_t i = 0; tempNode and i < amountOfItemsPerLevel; i++) {
					if (i == 0) for (int32_t j = 0; j < y; j++) std::cout << " ";
					std::cout << tempNode->value;
					for (int32_t j = 0; j < space; j++) std::cout << " ";
					tempNode = tempNode->next;
				}
				std::cout << std::endl;
			}
		}

		void printInFile(std::ofstream& file){
			if (is_empty()) return;
			Node<T>* printNode = head;
			while (printNode) {
				file << printNode->value << " ";
				printNode = printNode->next;
			}
			file << std::endl;
		}

	};

	CBTList<T> BinaryTree;
public:

	void TINSERT(T value) {
		BinaryTree.push(value);
	}

	void TDEL() {
		BinaryTree.pop();
	}

	T TGET(T value) {
		return BinaryTree.find(value);
	}

	bool TCHEK(){
		return BinaryTree.chek();
	}

	void print() {
		BinaryTree.print();
	}

	void printInFile(std::ofstream& file){
		BinaryTree.printInFile(file);
	}
};
