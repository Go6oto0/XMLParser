#pragma warning(disable:4996)
#include "String.h"
#include <iostream>
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
	if (newCapacity == 0)
	{
		delete[] str;
		capacity = 2;
		str = new char[capacity];
		str[0] = 0;
	}
	else
	{
		char* newStr = new char[newCapacity];
		strcpy(newStr, str);
		capacity = newCapacity;
		delete[] str;
		str = newStr;
	}
}
void String::moveFrom(String&& other) {
	str = other.str;
	len = other.len;
	capacity = other.capacity;
	other.str = nullptr;
	other.len = 0;
	other.capacity = 0;
}

//dyn memory
String::String() {
	capacity = 1;
	len = 0;
	str = new char[capacity];
	str[0] = '\0';
}
String::String(const String& other) {
	copy(other);
}
String::String(String&& other) {
	moveFrom(std::move(other));
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
void String::clear() {
	delete[] str;
	capacity = 1;
	len = 0;
	str = new char[capacity];
	str[0] = '\0';
}
String::operator bool() const {
	return (len != 0);
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
String& String::operator=(String&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
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
void String::append(String const& other) {
	if (len + other.getLen() + 1 >= capacity) {
		resizeTo(len + other.getLen() + 1);
	}
	strcpy(str + len, other.str);
	len += other.getLen();
}
String& String::operator+=(String const& other) {
	append(other);
	return *this;
}
bool operator<(String const& lhs, String const& rhs) {
	return strcmp(lhs.str, rhs.str) < 0;
}
String operator+(String const& lhs, String const& rhs) {
	String result(lhs);
	result += rhs;
	return result;
}
const char* String::getPtr() const {
	return str;
}
std::istream& operator>>(std::istream& is, String& str)
{
	str.clear();

	while (std::isspace(is.peek()))
		is.get();

	while (is && !std::isspace(is.peek()))
	{
		str.push_back(is.get());
	}

	return is;
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

