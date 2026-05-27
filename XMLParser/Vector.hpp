#pragma once
#include <iostream>
template<typename T>
class Vector {
private:
	class Iterator {
	private:
		T* curr;
	public:
		Iterator(T* curr) : curr(curr) {}
		Iterator& operator++() {
			curr++;
			return *this;
		}
		bool operator!=(const Iterator& other) const {
			return curr != other.curr;
		}
		T& operator*() {
			return *curr;
		}
		const T& operator*() const {
			return *curr;
		}
	};
public:
	Iterator begin() {
		return Iterator(arr);
	}
	Iterator end() {
		return Iterator(arr + size);
	}
	Iterator begin() const {
		return Iterator(arr);
	}
	Iterator end() const {
		return Iterator(arr + size);
	}

public:
	bool empty() const {
		return size == 0;
	}
	operator bool() const {
		return !empty();
	}
	size_t getSize() const {
		return size;
	}
	void print(std::ostream& os = std::cout) const {
		for (size_t i = 0; i < size; i++)
		{
			os << arr[i] << ' ';
		}
	}

	void push_back(const T& el) {
		if (size >= capacity)
		{
			resize();
		}
		arr[size] = el;
		size++;
	}
	T pop_back() {
		size--;
		return arr[size];
	}
	T& operator[](size_t ind) {
		return arr[ind];
	}
	const T& operator[](size_t ind) const {
		return arr[ind];
	}
	void clear() {
		size = 0;
	}

private:
	T* arr;
	size_t size;
	size_t capacity;

private:
	void copy(const Vector& other) {
		size = other.size;
		capacity = other.capacity;
		arr = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	void resize() {
		if (capacity > 0)
		{
			capacity = capacity * 2;
		}
		else
		{
			capacity = 1;
		}
		T* newArr = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
	}
	void free() {
		delete[] arr;
		arr = nullptr;
		size = 0;
		capacity = 0;
	}
public:
	Vector() : arr(nullptr), size(0), capacity(0) {}
	Vector(const Vector& other) {
		copy(other);
	}
	Vector& operator=(const Vector& other) {
		if (&other != this)
		{
			free();
			copy(other);
		}
		return *this;
	}
	~Vector() {
		free();
	}
};
template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
	v.print(os);
	return os;
}