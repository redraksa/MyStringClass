#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <new>
#include "MyStringErrors.h"
#include <cmath>
#include <string.h>
#include <unordered_map>
#include <functional>

#ifdef __linux__
#include "LinuxCompat.h"
#endif
class AhoCorasick;

enum class LexicographicComparisonStringsResult {
	cIsGreater = 1,
	cIsEqual = 0,
	cIsSmaller = -1
};

#define MAX_NUMBER_LENGTH 19

class MyString;



class MyString {
public:
	//1.default constructor
	MyString() : str_(nullptr), size_str_(0), capacity_str_(0) {}

	//2. copy constructor from origin string (const char*)
	MyString(const char* str) {
		MyStringErrors::check_null_pointer_string(str);

		allocate_memory(strlen(str));

		errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
		MyStringErrors::check_strncpy_s(err);
	}

	//3. copy constructor from origin string (const std::string&)
	MyString(const std::string& str) : MyString(str.c_str()) {

	}

	//4. copy constructor from other MyString
	MyString(const MyString& other) : MyString(other.c_str()) {
		/*MyStringErrors::check_null_pointer_string(other.str_);
		
		capacity_str_ = other.capacity_str_;
		size_str_ = other.size_str_;

		str_ = new (std::nothrow) char[capacity_str_];
		MyStringErrors::check_memory_allocate_exception(str_);

		errno_t err = strncpy_s(str_, capacity_str_, other.str_, size_str_);
		MyStringErrors::check_strncpy_s(err);*/	
	}  

	//5. Initializing constructor with definite number of symbols from const char*
	MyString(const char* str, const int count) {
		MyStringErrors::check_count_sumbols(count);

		MyStringErrors::check_null_pointer_string(str, count);

		MyStringErrors::check_out_of_range_count(str, count);

		/*		size_str_ = static_cast<size_t>(count);
		capacity_str_ = static_cast<size_t>(count + 1);
		str_ = new (std::nothrow) char[capacity_str_];*/
		allocate_memory(static_cast<size_t>(count));
		
		errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
		MyStringErrors::check_strncpy_s(err);
	}

	//6. Initializing constructor with definite number of symbols from std::string
	MyString(const std::string& str, const int count) : MyString(str.c_str(), count) {}

	//7. Initializing constructor with definite number of symbols from MyString
	MyString(const MyString& other, const int count) : MyString(other.c_str(), count) {
		/*		MyStringErrors::check_count_sumbols(count);

		MyStringErrors::check_null_pointer_string(other.str_, count);

		MyStringErrors::check_out_of_range_count(other.str_, count);

		size_str_ = static_cast<size_t>(count);
		capacity_str_ = static_cast<size_t>(count + 1);
		str_ = new (std::nothrow) char[count + 1];

		MyStringErrors::check_memory_allocate_exception(str_);

		errno_t err = strncpy_s(str_, capacity_str_, other.str_, size_str_);
		MyStringErrors::check_strncpy_s(err);*/
	}

	//8. Initializing constructor with definite number of same symbols
	MyString(const int count, const char c) {
		MyStringErrors::check_count_sumbols(count);

		/*		size_str_ = static_cast<size_t>(count);
		capacity_str_ = static_cast<size_t>(count + 1);
		str_ = new (std::nothrow) char[capacity_str_];

		MyStringErrors::check_memory_allocate_exception(str_);*/
		allocate_memory(static_cast<size_t>(count));

		memset(str_, c, count);
		str_[count] = '\0';
	}

	//9. Destructor
	~MyString() {
		delete[] str_;
		str_ = nullptr;
	}

	//10. Removing elements char from string
	void clear();

	//11. Reducing capacity of string to size of string
	void shrink_to_fit();

	//12. Assignment operator of string
	MyString& operator=(const char* str);
	MyString& operator=(const std::string& str);
	MyString& operator=(const MyString&);

	//13. Assignment operator of char
	MyString operator=(const char);

	//14. Get const char* ending with '\0'
	char* c_str() const {
		return str_;
	}

	//15. Get count of symbols of char in string
	size_t size() const {
		return size_str_;
	}

	//16. Get volume of allocated memory
	size_t capacity() const {
		return capacity_str_;
	}

	//17. Return true if string is empty
	bool empty() const {
		return str_ == nullptr;
	}

	//18. Insert count symbols ch by index
	void insert(int index, int count, char ch);

	//19, 20, 21. Insert string by index
	void insert(const int index, const char* str);
	void insert(const int index, const std::string& str);
	void insert(const int index, const MyString& other);

	//22, 23, 24. Isert count symbols of string by index
	void insert(const int index, const char* str, const int count);
	void insert(const int index, const std::string& str, const int count);
	void insert(const int index, MyString& other, const int count);

	//25, 26, 27. Insert count symbols of string from s_index by index
	void insert(const int index, const char* str, int s_index, int count);
	void insert(const int index, const std::string& str, int s_index, int count);
	void insert(const int index, MyString& other, int s_index, int count);

	//28. Append count symbols
	void append(const int count, const char ch);

	//29, 30, 31. Append string 
	void append(const char* str);
	void append(const std::string& str);
	void append(MyString& other);

	//32, 33, 34. Append count symbols of string 
	void append(const char* str, const int count);
	void append(const std::string& str, const int count);
	void append(MyString& other, const int count);

	//35, 36, 37. Append count symbols of string from s_index
	void append(const char* str, const int s_index, const int count);
	void append(const std::string& str, const int s_index, const int count);
	void append(MyString& other, const int s_index, const int count);

	//38. Remove count symbols by index
	void erase(const int index, const int count);

	//39, 40, 41. Replace count symbols on string by index
	void replace(const int index, const int count, const char* str);
	void replace(const int index, const int count, const std::string& str);
	void replace(const int index, const int count, MyString& other);

	//42, 43, 44. Replace count symbols on s_count symbols of string by index
	void replace(const int index, const int count, const char* str, const int s_count);
	void replace(const int index, const int count, const std::string& str, const int s_count);
	void replace(const int index, const int count, MyString& other, const int s_count);

	//45, 46, 47. Replace count symbols on s_count symbols of string by index from s_index
	void replace(const int index, const int count, const char* str, const int s_index, const int s_count);
	void replace(const int index, const int count, const std::string& str, const int s_index, const int s_count);
	void replace(const int index, const int count, MyString& other, const int s_index, const int s_count);

	//48. Return substring from index
	MyString substr(const int index);

	//49. Return substring with some length from index
	MyString substr(const int index, const int count);

	//50, 51, 52. Union operator of string
	MyString operator+(const char* str);
	MyString operator+(const std::string& str);
	MyString operator+(const MyString& other);

	//53, 54, 55. Adding string to current string
	MyString& operator+=(const char* str);
	MyString& operator+=(const std::string& str);
	MyString& operator+=(const MyString& other);

	//56. Operator of indexation
	char& operator[](const int index);
	char operator[](const int index) const;

	//57. Lexicographic string comparison (return -1, 0, 1)
	LexicographicComparisonStringsResult compare(const MyString& other) const;

	//58, 59, 60. Lexicographic string comparison (return bool)
	bool operator>(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator>=(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator==(const MyString& other) const;

	//61, 62, 63. Return index of first occurence of the string
	int find(const char* str) const;
	int find(const std::string& str) const;
	int find(const MyString& other) const;

	//64, 65, 66. Return index of first occurence of the string after other index
	int find(const char* str, int index) const;
	int find(const std::string& str, int index) const;
	int find(const MyString& other, int index) const;

	//Additional functional of MyString class
	MyString(MyString&& other) noexcept;
	MyString(int number);
	MyString(const long long number);
	MyString(const float number);
	MyString& operator=(MyString&& other);
	char at(const int index);
	long long to_int();
	float to_float();
	void findAll(std::unordered_map<MyString, std::vector<size_t>>& dictionary) const;
	std::vector<size_t> findAll(const MyString& other) const;
private:
	char* str_;
	size_t size_str_; 
	size_t capacity_str_;

	void allocate_memory(size_t size);
	void reallocate_memory(size_t size, bool is_equal);
};

namespace std {
	template<>
	struct hash<MyString> {
		size_t operator()(const MyString& s) const {
			// Простая хеш-функция для C-строки
			size_t result = 0;
			const size_t prime = 31;
			for (int i = 0; i < s.size(); ++i) {
				result = result * prime + s[i];
			}
			return result;
		}
	};
}

inline std::ostream& operator<<(std::ostream& os, const MyString& str) {
	os << (str.c_str() != nullptr ? str.c_str() : "");
	return os;
}

inline std::istream& operator>>(std::istream& is, MyString& str) {
	std::string temp;
	is >> temp;
	str = MyString(temp.c_str());
	return is;
}
#endif // _MYSTRING_H_

