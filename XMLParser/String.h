#pragma once
#include <ostream>
#include <cstddef>
class String {
	char* str;
	size_t len;
	size_t capacity;

private:
	void copy(const String& other);
	void free();
	void moveFrom(String&& other);
	void resizeTo(size_t newCapacity);
public:
	String();
	String(const String& other);
	String(String&& other);
	String(const char* str);
	String& operator=(const String& other);
	String& operator=(String&& other);
	~String();

	friend std::ostream& operator<<(std::ostream& os, const String& other);
	char& operator[](size_t ind);
	void clear();
	const char& operator[](size_t index) const;
	operator bool() const;
	friend bool operator==(String const& lhs, String const& rhs);

	void push_back(char c);
	size_t getLen() const;

};
