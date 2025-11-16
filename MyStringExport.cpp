#include "MyStringExport.h"

MyStringExported::MyStringExported() : m_original(new MyString()) {}
MyStringExported::MyStringExported(const char* str) : m_original(new MyString(str)) {}
MyStringExported::MyStringExported(const std::string& str) : m_original(new MyString(str)) {}
MyStringExported::MyStringExported(const MyStringExported& other) : m_original(new MyString(*other.m_original)) {}
MyStringExported::MyStringExported(const char* str, const int count) : m_original(new MyString(str, count)) {}
MyStringExported::MyStringExported(const std::string& str, const int count) : m_original(new MyString(str, count)) {}
MyStringExported::MyStringExported(const MyStringExported& other, const int count) : m_original(new MyString(*other.m_original, count)) {}
MyStringExported::MyStringExported(const int count, const char c) : m_original(new MyString(count, c)) {}
MyStringExported::~MyStringExported() { delete m_original; }


void MyStringExported::clear() {
	m_original->clear();
}
void MyStringExported::shrink_to_fit() {
	m_original->shrink_to_fit();
}
MyStringExported& MyStringExported::operator=(const char* str) {
	m_original->operator=(str);
	return *this;
}
MyStringExported& MyStringExported::operator=(const std::string& str) {
	m_original->operator=(str);
	return *this;
}
MyStringExported& MyStringExported::operator=(const MyStringExported& other) {
	if (this == &other) {
		return *this;
	}
	*m_original = *other.m_original;
	return *this;
}
MyStringExported& MyStringExported::operator=(const char ch) {
	m_original->operator=(ch);
	return *this;
}
char* MyStringExported::c_str() const {
	return m_original->c_str();
}
size_t MyStringExported::size() const {
	return m_original->size();
}
size_t MyStringExported::capacity() const {
	return m_original->capacity();
}
bool MyStringExported::empty() const {
	return m_original->empty();
}
void MyStringExported::insert(int index, int count, char ch) {
	m_original->insert(index, count, ch);
}
void MyStringExported::insert(const int index, const char* str) {
	m_original->insert(index, str);
}
void MyStringExported::insert(const int index, const std::string& str) {
	m_original->insert(index, str);
}
void MyStringExported::insert(const int index, const MyStringExported& other) {
	m_original->insert(index, *other.m_original);
}
void MyStringExported::insert(const int index, const char* str, const int count) {
	m_original->insert(index, str, count);
}
void MyStringExported::insert(const int index, const std::string& str, const int count) {
	m_original->insert(index, str, count);
}
void MyStringExported::insert(const int index, const MyStringExported& other, const int count) {
	m_original->insert(index, *other.m_original, count);
}
void MyStringExported::insert(const int index, const char* str, int s_index, int count) {
	m_original->insert(index, str, s_index, count);
}
void MyStringExported::insert(const int index, const std::string& str, int s_index, int count) {
	m_original->insert(index, str, s_index, count);
}
void MyStringExported::insert(const int index, const MyStringExported& other, int s_index, int count) {
	m_original->insert(index, *other.m_original, s_index, count);
}
void MyStringExported::append(const int count, const char ch) {
	m_original->append(count, ch);
}
void MyStringExported::append(const char* str) {
	m_original->append(str);
}
void MyStringExported::append(const std::string& str) {
	m_original->append(str);
}
void MyStringExported::append(const MyStringExported& other) {
	m_original->append(*other.m_original);
}
void MyStringExported::append(const char* str, const int count) {
	m_original->append(str, count);
}
void MyStringExported::append(const std::string& str, const int count) {
	m_original->append(str, count);
}
void MyStringExported::append(const MyStringExported& other, const int count) {
	m_original->append(*other.m_original, count);
}
void MyStringExported::append(const char* str, const int s_index, const int count) {
	m_original->append(str, s_index, count);
}
void MyStringExported::append(const std::string& str, const int s_index, const int count) {
	m_original->append(str, s_index, count);
}
void MyStringExported::append(const MyStringExported& other, const int s_index, const int count) {
	m_original->append(*other.m_original, s_index, count);
}
void MyStringExported::erase(const int index, const int count) {
	m_original->erase(index, count);
}
void MyStringExported::replace(const int index, const int count, const char* str) {
	m_original->replace(index, count, str);
}
void MyStringExported::replace(const int index, const int count, const std::string& str) {
	m_original->replace(index, count, str);
}
void MyStringExported::replace(const int index, const int count, const MyStringExported& other) {
	m_original->replace(index, count, *other.m_original);
}
void MyStringExported::replace(const int index, const int count, const char* str, const int s_count) {
	m_original->replace(index, count, str, s_count);
}
void MyStringExported::replace(const int index, const int count, const std::string& str, const int s_count) {
	m_original->replace(index, count, str, s_count);
}
void MyStringExported::replace(const int index, const int count, const MyStringExported& other, const int s_count) {
	m_original->replace(index, count, *other.m_original, s_count);
}
void MyStringExported::replace(const int index, const int count, const char* str, const int s_index, const int s_count) {
	m_original->replace(index, count, str, s_index, s_count);
}
void MyStringExported::replace(const int index, const int count, const std::string& str, const int s_index, const int s_count) {
	m_original->replace(index, count, str, s_index, s_count);
}
void MyStringExported::replace(const int index, const int count, const MyStringExported& other, const int s_index, const int s_count) {
	m_original->replace(index, count, *other.m_original, s_index, s_count);
}
MyStringExported MyStringExported::substr(const int index) const {
	::MyString result = m_original->substr(index);
	return MyStringExported(result.c_str());
}
MyStringExported MyStringExported::substr(const int index, const int count) const {
	::MyString result = m_original->substr(index, count);
	return MyStringExported(result.c_str());
}
MyStringExported MyStringExported::operator+(const char* str) const {
	::MyString result = *m_original + str;
	return MyStringExported(result.c_str());
}
MyStringExported MyStringExported::operator+(const std::string& str) const {
	::MyString result = *m_original + str;
	return MyStringExported(result.c_str());
}
MyStringExported MyStringExported::operator+(const MyStringExported& other) const {
	::MyString result = *m_original + *other.m_original;
	return MyStringExported(result.c_str());
}
MyStringExported& MyStringExported::operator+=(const char* str) {
	m_original->operator+=(str);
	return *this;
}
MyStringExported& MyStringExported::operator+=(const std::string& str) {
	m_original->operator+=(str);
	return *this;
}
MyStringExported& MyStringExported::operator+=(const MyStringExported& other) {
	m_original->operator+=(*other.m_original);
	return *this;
}
char& MyStringExported::operator[](const int index) {
	return (*m_original)[index];
}
char MyStringExported::operator[](const int index) const {
	return (*m_original)[index];
}
LexicographicComparisonStringsResult MyStringExported::compare(const MyStringExported& other) const {
	return m_original->compare(*other.m_original);
}
bool MyStringExported::operator>(const MyStringExported& other) const {
	return (*m_original) > *other.m_original;
}
bool MyStringExported::operator<(const MyStringExported& other) const {
	return (*m_original) < *other.m_original;
}
bool MyStringExported::operator>=(const MyStringExported& other) const {
	return (*m_original) >= *other.m_original;
}
bool MyStringExported::operator<=(const MyStringExported& other) const {
	return (*m_original) <= *other.m_original;
}
bool MyStringExported::operator!=(const MyStringExported& other) const {
	return (*m_original) != *other.m_original;
}
bool MyStringExported::operator==(const MyStringExported& other) const {
	return (*m_original) == *other.m_original;
}
int MyStringExported::find(const char* str) const {
	return m_original->find(str);
}
int MyStringExported::find(const std::string& str) const {
	return m_original->find(str);
}
int MyStringExported::find(const MyStringExported& other) const {
	return m_original->find(*other.m_original);
}
int MyStringExported::find(const char* str, int index) const {
	return m_original->find(str, index);
}
int MyStringExported::find(const std::string& str, int index) const {
	return m_original->find(str, index);
}
int MyStringExported::find(const MyStringExported& other, int index) const {
	return m_original->find(*other.m_original, index);
}