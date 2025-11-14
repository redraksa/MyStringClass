#ifndef _MYSTRINGERRORS_H_
#define _MYSTRINGERRORS_H_

#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>
#include <sstream>

#ifdef __linux__
#include "LinuxCompat.h"
#endif

class MyString;

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

	static void check_index(const int& index) {
		if (index < 0) {
			throw std::out_of_range("index can't be negative");
		}
	}

	static void check_out_of_range_count(const char* str, const int& count) {
		if (count > static_cast<int>(strlen(str)) && str != nullptr) {
			throw std::out_of_range("count of copy symbols can't be greater than length of origing string");
		}
	}

	static void check_out_of_range_count(const int& length, const int& count) {
		if (count > length) {
			throw std::out_of_range("count of copy symbols (" + std::to_string(count) + ") can't be greater than length (" + std::to_string(length) + ") of origing string");
		}
	}

	static void check_out_of_range_index(const int size_str, const int index) {
		if ((index >= size_str && index + size_str != 0) || index < 0) {
			throw std::out_of_range("Index " + std::to_string(index) +
				" is out of range [0, " + std::to_string(size_str) + "]");
		}
	}

	static void check_out_of_range_iterator(const int size_str, const int index) {
		if (index > size_str || index < -1) {
			throw std::out_of_range("Index " + std::to_string(index) +
				" is out of range [0, " + std::to_string(size_str) + "]");
		}
	}

	static void check_out_of_range_index(const char* str, const int index) {
		if (index >= static_cast<int>(strlen(str)) && strlen(str) != 0 || index < 0) {
			throw std::out_of_range("index of string must be lesser than length of string and positive");
		}
	}

	static void check_out_of_range_index(const char* begin, const char* end, const char* current) {
		if (current >= end || current <= begin) {
			std::ostringstream oss;
			oss << "Current iterator of collection (" << static_cast<const void*>(current)
				<< ") is beyond from boundaries of collection: begin (" << static_cast<const void*>(begin)
				<< "), end (" << static_cast<const void*>(end) << ")!";
			throw std::out_of_range(oss.str());
		}
	}

	static void check_memmove_s(errno_t err) {
		if (err != 0) {
			throw std::runtime_error("memory move exception!");
		}
	}

	static void check_strncpy_s(errno_t err) {
		if (err != 0) {
			throw std::runtime_error("memory copy exception");
		}
	}

	static void check_memcpy_s(errno_t err) {
		if (err != 0) {
			throw std::runtime_error("memory copy exception");
		}
	}

	static void check_boundary_number(long long& number) {
		if (!(number >= LLONG_MIN + 1 && number <= LLONG_MAX)) {
			throw std::runtime_error("number is out from allowed range");
		}
	}

	static void check_invalid_symbol_integer(const char* str) {
		int i = 0;
		if (str[0] == '-') {
			i = 1;
		}
		for (i; i < strlen(str); ++i) {
			if (!(str[i] >= '0' && str[i] <= '9')) {
				throw std::runtime_error("string has unresolved character to convert to integer number");
			}
		}
	}

	static void check_invalid_symbol_float(const char* str) {
		int i = 0;
		if (str[0] == '-') {
			i = 1;
		}
		bool flag_dot = false;
		for (i; i < strlen(str); ++i) {
			if (!(str[i] >= '0' && str[i] <= '9' || str[i] == '.' && i != 0 && i != strlen(str) - 1 && !flag_dot)) {
				throw std::runtime_error("string has unresolved character to convert to integer number");
			}
			if (str[i] == '.') {
				flag_dot = true;
			}
		}
	}

	static void check_iterators(const MyString* str1, const MyString* str2) {
		if (str1 != str2) {
			throw std::invalid_argument("Iterators do not belong to same string");
		}
	}

	static void check_iterator(const char* str1, const char* str2) {
		if (str1 != str2) {
			throw std::runtime_error("Iterator does not bolong to this string");
		}
	}

	static void check_iterator_validity(const MyString* str1, const MyString* str2) {
		if (str1 != str2) {
			throw std::invalid_argument("Iterator does not belong to this MyString");
		}
	}

};

#endif // !_MYSTRINGERRORS_
