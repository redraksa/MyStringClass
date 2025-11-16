#ifndef _MYSTRINGEXPORT_H_
#define _MYSTRINGEXPORT_H_
#include "..\MyString\MyString.h"
#include <iostream>

#ifdef _WIN32
#ifdef MYSTRINGEXPORT
#define MYSTRING_API __declspec(dllexport)
#else
#define MYSTRING_API __declspec(dllimport)
#endif
#else
#define MYSTRING_API
#endif

class MYSTRING_API MyStringExported {
public:
	MyStringExported();
	MyStringExported(const char* str);
	MyStringExported(const std::string& str);
	MyStringExported(const MyStringExported& other);
	MyStringExported(const char* str, const int count);
	MyStringExported(const std::string& str, const int count);
	MyStringExported(const MyStringExported& other, const int count);
	MyStringExported(const int count, const char c);
	~MyStringExported();
	void clear();
	void shrink_to_fit();
	MyStringExported& operator=(const char* str);
	MyStringExported& operator=(const std::string& str);
	MyStringExported& operator=(const MyStringExported&);
	MyStringExported& operator=(const char);
	char* c_str() const;
	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	void insert(int index, int count, char ch);
	void insert(const int index, const char* str);
	void insert(const int index, const std::string& str);
	void insert(const int index, const MyStringExported& other);
	void insert(const int index, const char* str, const int count);
	void insert(const int index, const std::string& str, const int count);
	void insert(const int index, const MyStringExported& other, const int count);
	void insert(const int index, const char* str, int s_index, int count);
	void insert(const int index, const std::string& str, int s_index, int count);
	void insert(const int index, const MyStringExported& other, int s_index, int count);
	void append(const int count, const char ch);
	void append(const char* str);
	void append(const std::string& str);
	void append(const MyStringExported& other);
	void append(const char* str, const int count);
	void append(const std::string& str, const int count);
	void append(const MyStringExported& other, const int count);
	void append(const char* str, const int s_index, const int count);
	void append(const std::string& str, const int s_index, const int count);
	void append(const MyStringExported& other, const int s_index, const int count);
	void erase(const int index, const int count);
	void replace(const int index, const int count, const char* str);
	void replace(const int index, const int count, const std::string& str);
	void replace(const int index, const int count, const MyStringExported& other);
	void replace(const int index, const int count, const char* str, const int s_count);
	void replace(const int index, const int count, const std::string& str, const int s_count);
	void replace(const int index, const int count, const MyStringExported& other, const int s_count);
	void replace(const int index, const int count, const char* str, const int s_index, const int s_count);
	void replace(const int index, const int count, const std::string& str, const int s_index, const int s_count);
	void replace(const int index, const int count, const MyStringExported& other, const int s_index, const int s_count);
	MyStringExported substr(const int index) const;
	MyStringExported substr(const int index, const int count) const;
	MyStringExported operator+(const char* str) const;
	MyStringExported operator+(const std::string& str) const;
	MyStringExported operator+(const MyStringExported& other) const;
	MyStringExported& operator+=(const char* str);
	MyStringExported& operator+=(const std::string& str);
	MyStringExported& operator+=(const MyStringExported& other);
	char& operator[](const int index);
	char operator[](const int index) const;
	LexicographicComparisonStringsResult compare(const MyStringExported& other) const;
	bool operator>(const MyStringExported& other) const;
	bool operator<(const MyStringExported& other) const;
	bool operator>=(const MyStringExported& other) const;
	bool operator<=(const MyStringExported& other) const;
	bool operator!=(const MyStringExported& other) const;
	bool operator==(const MyStringExported& other) const;
	int find(const char* str) const;
	int find(const std::string& str) const;
	int find(const MyStringExported& other) const;
	int find(const char* str, int index) const;
	int find(const std::string& str, int index) const;
	int find(const MyStringExported& other, int index) const;
private:
	MyString* m_original;
};

inline std::ostream& operator<<(std::ostream& os, const MyStringExported& str) {
	const char* cstr = str.c_str();
	os << (cstr != nullptr ? cstr : "");
	return os;
}

inline std::istream& operator>>(std::istream& is, MyStringExported& str) {
	std::string temp;
	is >> temp;
	str = temp.c_str();
	return is;
}

#endif // !_MYSTRINGEXPORT_H_


