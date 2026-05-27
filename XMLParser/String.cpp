#pragma warning(disable:4996)
#include "String.h"
#include <ostream>
//helper
void String::copy(const String& other) {
	len = other.len;
	capacity = other.capacity;
	str = new char[capacity];
	strcpy(str, other.str);
}
void String::free() {
	delete[] str;
	str = nullptr;
	len = 0;
	capacity = 0;
}
void String::resizeTo(size_t newCapacity) {
	char* newStr = new char[newCapacity];
	strcpy(newStr, str);
	capacity = newCapacity;
	delete[] str;
	str = newStr;
}


//dyn memory
String::String() {
	str = nullptr;
	capacity = 0;
	len = 0;
}
String::String(const String& other) {
	copy(other);
}
String::String(const char* str) {
	if (!str)
	{
		capacity = 1;
		len = 0;
		this->str = new char[capacity];
		this->str[0] = 0;
	}
	else
	{
		len = strlen(str);
		capacity = len + 1;
		this->str = new char[capacity];
		strcpy(this->str, str);
	}
}

String& String::operator=(const String& other) {
	if (this == &other)
	{
		return *this;
	}
	free();
	copy(other);
	return *this;
}
String::~String() {
	free();
}

//other fs
char& String::operator[](size_t ind) {
	return str[ind];
}

const char& String::operator[](size_t ind) const {
	return str[ind];
}

bool operator==(String const& lhs, String const& rhs) {
	if (lhs.len != rhs.len)
	{
		return false;
	}
	for (size_t i = 0; i < lhs.len; i++)
	{
		if (lhs.str[i] != rhs.str[i])
		{
			return false;
		}
	}
	return true;
}


std::ostream& operator<<(std::ostream& os, const String& str) {
	os << str.str;
	return os;
}

void String::push_back(char c) {
	if (len + 1 >= capacity)
	{
		resizeTo(capacity * 2);
	}
	str[len] = c;
	len++;
	str[len] = '\0';
}
size_t String::getLen() const {
	return len;
}

