#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <new>
#include "MyStringErrors.h"

class MyString {
public:
	//1.default constructor
	MyString() : str_(nullptr), size_str_(0), capacity_str_(0) {}

	//2. copy constructor from origin string (const char*)
	MyString(const char* str) : MyString(str, static_cast<int>(strlen(str))) {
		/*MyStringErrors::check_null_pointer_string(str);

		size_str_ = strlen(str);
		capacity_str_ = size_str_ + 1;
		str_ = new (std::nothrow) char[capacity_str_];
		if (str_ == nullptr) {
			throw std::bad_alloc();
		}
		errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
		MyStringErrors::check_strncpy_s(err);*/
	}

	//3. copy constructor from origin string (const std::string&)
	MyString(const std::string& str) : MyString(str.c_str()) {}

	//4. copy constructor from other MyString
	MyString(const MyString& other) : MyString(other, static_cast<int>(other.capacity_str_ - 1)){
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

		MyStringErrors::check_memory_allocate_exception(str_);
		
		errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
		MyStringErrors::check_strncpy_s(err);
	}

	//6. Initializing constructor with definite number of symbols from std::string
	MyString(const std::string& str, const int count) : MyString(str.c_str(), count) {}

	//7. Initializing constructor with definite number of symbols from MyString
	MyString(const MyString& other, const int count) {
		MyStringErrors::check_count_sumbols(count);

		MyStringErrors::check_null_pointer_string(other.str_, count);

		MyStringErrors::check_out_of_range_count(other.str_, count);

		size_str_ = static_cast<size_t>(count);
		capacity_str_ = static_cast<size_t>(count + 1);
		str_ = new (std::nothrow) char[count + 1];

		MyStringErrors::check_memory_allocate_exception(str_);

		errno_t err = strncpy_s(str_, capacity_str_, other.str_, size_str_);
		MyStringErrors::check_strncpy_s(err);
	}

	//8. Initializing constructor with definite number of same symbols
	MyString(const int count, const char c) {
		MyStringErrors::check_count_sumbols(count);

		size_str_ = static_cast<size_t>(count);
		capacity_str_ = static_cast<size_t>(count + 1);
		str_ = new (std::nothrow) char[capacity_str_];

		MyStringErrors::check_memory_allocate_exception(str_);

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
	constexpr size_t size() const {
		return size_str_;
	}

	//16. Get volume of allocated memory
	constexpr size_t capacity() const {
		return capacity_str_;
	}

	//17. Return true if string is empty
	constexpr bool empty() const {
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

	//38. Remove count symbols by index
	void erase(const int index, const int count);

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

private:
	char* str_;
	size_t size_str_; 
	size_t capacity_str_;

	void allocate_memory(size_t size) {
		str_ = new (std::nothrow) char[size + 1];
		size_str_ = size;
		capacity_str_ = size + 1;
	}

};

inline std::ostream& operator<<(std::ostream& os, const MyString& str) {
	os << (str.c_str() != nullptr ? str.c_str() : "");
	return os;
}


#endif // _MYSTRING_H_

