#ifndef _MYSTRINGERRORS_
#define _MYSTRINGERRORS_

#include <iostream>
#include <exception>

class MyStringErrors {
public:
	static void check_memory_allocate_exception(char* str) {
		if (str == nullptr) {
			throw std::bad_alloc();
		}
	}

	static void check_null_pointer_string(const char* str) {
		if (str == nullptr) {
			throw std::invalid_argument("string pointer can't be null\n");
		}
	}

	static void check_null_pointer_string(const char* str, const int& count) {
		if (count > 0 && str == nullptr) {
			throw std::invalid_argument("string pointer can't be null if count is positive");
		}
	}

	static void check_count_sumbols(const int& count) {
		if (count < 0) {
			throw std::out_of_range("count can't be negative");
		}
	}

	static void check_out_of_range_count(const char* str, const int& count) {
		if (count > static_cast<int>(strlen(str)) && str != nullptr) {
			throw std::out_of_range("count of copy symbols can't be greater than length of origing string");
		}
	}

	static void check_out_of_range_count(const int& length, const int& count) {
		if (count > length) {
			throw std::out_of_range("count of copy symbols can't be greater than length of origing string");
		}
	}

	static void check_out_of_range_index(int size_str, const int index) {
		if (index >= size_str && index >= 0) {
			throw std::out_of_range("index of string must be lesser than length of string and positive");
		}
	}

	static void check_memmove_s(errno_t err) {
		if (err != 0) {
			throw std::runtime_error("memory move exception");
		}
	}

	static void check_strncpy_s(errno_t err) {
		if (err != 0) {
			throw std::runtime_error("memory copy exception");
		}
	}

};

#endif // !_MYSTRINGERRORS_
