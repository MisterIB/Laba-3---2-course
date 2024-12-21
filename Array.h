#pragma once

#include <iostream>
#include <fstream>

template <typename T>
class Array {
private:
	T* arr;
	int32_t capacity, currentSize;
public:
	Array() {
		arr = new T[1];
		capacity = 1;
		currentSize = 0;
	}

	~Array() { delete[] arr; }

	void push_back(T value) {
		if (capacity == currentSize) {
			T* temp = new T[2 * capacity];
			for (int32_t i = 0; i < capacity; i++) temp[i] = arr[i];
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		arr[currentSize] = value;
		currentSize++;
	}

	void insert(int32_t index, T value) {
		if (index == currentSize) {
			push_back(value);
			return;
		}
		if (capacity == currentSize) {
			T* temp = new T[2 * capacity];
			for (int32_t i = 0; i < capacity; i++) temp[i] = arr[i];
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		T* tempArray = new T[capacity];
		if (index > currentSize) throw std::runtime_error("going outside the array");
		for (int32_t i = 0, j = 0; i < currentSize; i++, j++) {
			if (i == index) {
				tempArray[i] = value;
				if (index + 1 != capacity) {
					j++;
					tempArray[j] = arr[i];
				}
			}
			else tempArray[j] = arr[i];
		}
		delete[] arr;
		arr = tempArray;
		currentSize++;
	}

	void erase(int32_t index) {
		if (index >= currentSize) throw std::runtime_error("going outside the array");
		T* temp = new T[capacity];
		for (int32_t i = 0, j = 0; i < currentSize; i++, j++) {
			if (i == index) {
				i++;
			}
			temp[j] = arr[i];
		}
		delete[] arr;
		arr = temp;
		currentSize--;
	}

	int32_t size() {
		return currentSize;
	}
	
	void print() {
		for (int32_t i = 0; i < currentSize; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}

	void printInFile(std::ofstream& file) {
		for (int32_t i = 0; i < currentSize; i++) {
			file << arr[i] << " ";
		}
		file << std::endl;
	}

	T& operator[](int32_t index) {
		return arr[index];
	}
};
