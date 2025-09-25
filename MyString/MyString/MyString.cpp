#include "MyString.h"

void MyString::clear() {
	memset(str_, '\0', capacity_str_);
	size_str_ = 0;
}

void MyString::shrink_to_fit() {
	capacity_str_ = size_str_ + 1;
	char* new_str = new (std::nothrow) char[capacity_str_];
	MyStringErrors::check_memory_allocate_exception(str_);

	errno_t err = strncpy_s(new_str, capacity_str_, str_, size_str_);
	MyStringErrors::check_strncpy_s(err);

	delete[] str_;
	str_ = new_str;
}

MyString& MyString::operator=(const char* str) {
	size_str_ = strlen(str);
	capacity_str_ = size_str_ + 1;
	delete[] str_;

	str_ = new (std::nothrow) char[capacity_str_];
	MyStringErrors::check_memory_allocate_exception(str_);

	errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
	MyStringErrors::check_strncpy_s(err);
	return *this;
}
MyString& MyString::operator=(const std::string& str) {
	return this->operator=(str.c_str());
}
MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		size_str_ = other.size_str_;
		capacity_str_ = other.capacity_str_;
		delete[] str_;

		str_ = new (std::nothrow) char[capacity_str_];
		MyStringErrors::check_memory_allocate_exception(str_);

		errno_t err = strncpy_s(str_, capacity_str_, other.str_, size_str_);
		MyStringErrors::check_strncpy_s(err);
	}
	return *this;
}

MyString MyString::operator=(const char ch) {
	size_str_ = 1;
	capacity_str_ = size_str_ + 1;

	str_ = new (std::nothrow) char[capacity_str_];
	MyStringErrors::check_memory_allocate_exception(str_);

	errno_t err = strncpy_s(str_, capacity_str_, &ch, size_str_);
	MyStringErrors::check_strncpy_s(err);
	return *this;
}
// подумать над вставкой
void MyString::insert(const int index, const int count, char ch) {
	MyStringErrors::check_count_sumbols(count);

	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), count);

	MyStringErrors::check_out_of_range_count(static_cast<int>(capacity_str_ - index - 1), count);

	MyString char_str(count, ch), left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + char_str + right_part;
}

void MyString::insert(const int index, const char* str) {
	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), index);

	MyString char_str(str), left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + char_str + right_part;
}
void MyString::insert(const int index, const std::string& str) {
	this->insert(index, str.c_str());
}
void MyString::insert(const int index, const MyString& other) {
	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), index);

	MyString left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + other + right_part;
}

void MyString::insert(const int index, const char* str, const int count) {
	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), index);

	MyString char_str(str, count), left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + char_str + right_part;
}
void MyString::insert(const int index, const std::string& str, const int count) {
	this->insert(index, str.c_str(), count);
}
void MyString::insert(const int index, MyString& other, const int count) {
	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), index);

	MyString left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + other.substr(0, count) + right_part;
}


void MyString::erase(const int index, const int count) {
	MyStringErrors::check_count_sumbols(count);

	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), count);

	MyStringErrors::check_out_of_range_count(static_cast<int>(capacity_str_ - index - 1), count);

	errno_t err = memmove_s(str_ + index, capacity_str_ - 1 - index, str_ + index + count, capacity_str_ - 1 - index - count);
	MyStringErrors::check_memmove_s(err);

	memset(str_ + capacity_str_ - 1 - count, '\0', count);
	size_str_ -= count;
}

MyString MyString::substr(const int index) {
	MyStringErrors::check_out_of_range_index(static_cast<int>(size_str_), index);

	MyString other;
	other.size_str_ = this->size_str_ - index;
	other.capacity_str_ = this->capacity_str_ - index;

	other.str_ = new (std::nothrow) char[other.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(other.str_);

	errno_t err = strncpy_s(other.str_, other.capacity_str_, this->str_ + index, this->size_str_);
	MyStringErrors::check_strncpy_s(err);

	return other;
}

MyString MyString::substr(const int index, const int count) {
	MyStringErrors::check_count_sumbols(count);

	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), count);

	MyStringErrors::check_out_of_range_count(static_cast<int>(capacity_str_ - index - 1), count);
	
	MyString other;
	other.size_str_ = count;
	other.capacity_str_ = count + 1;

	other.str_ = new (std::nothrow) char[other.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(other.str_);

	errno_t err = strncpy_s(other.str_, other.capacity_str_, this->str_ + index, other.size_str_);
	MyStringErrors::check_strncpy_s(err);

	return other;
}

MyString MyString::operator+(const char* str) {
	if (str == nullptr) {
		return *this;
	}
	
	MyString my_str;
	my_str.size_str_ = this->size_str_ + strlen(str);
	my_str.capacity_str_ = this->capacity_str_ + strlen(str);

	my_str.str_ = new (std::nothrow) char[my_str.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(my_str.str_);

	errno_t err = strncpy_s(my_str.str_, my_str.capacity_str_, this->str_, this->size_str_);
	MyStringErrors::check_strncpy_s(err);

	err = strncpy_s(my_str.str_ + this->size_str_, my_str.capacity_str_ - this->size_str_, str, strlen(str));
	MyStringErrors::check_strncpy_s(err);

	return my_str;
}

MyString MyString::operator+(const std::string& str) {
	return this->operator+(str.c_str());
}

MyString MyString::operator+(const MyString& other) {
	if (other.str_ == nullptr) {
		return *this;
	}

	MyString my_str;
	my_str.size_str_ = this->size_str_ + other.size_str_;
	my_str.capacity_str_ = this->capacity_str_ + other.capacity_str_ - 1;

	my_str.str_ = new (std::nothrow) char[my_str.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(my_str.str_);

	errno_t err = strncpy_s(my_str.str_, my_str.capacity_str_, this->str_, this->size_str_);
	MyStringErrors::check_strncpy_s(err);

	err = strncpy_s(my_str.str_ + this->size_str_, my_str.capacity_str_ - this->size_str_, other.str_, other.size_str_);
	MyStringErrors::check_strncpy_s(err);

	return my_str;
}

/*MyString& MyString::operator+=(const char* str) {
	if (str == nullptr) {
		return *this;
	}

	size_t size_str = this->size_str_ + strlen(str);
	size_t capacity_str = this->capacity_str_ + strlen(str);
	//this->size_str_ += strlen(str);
	//this->capacity_str_ += strlen(str);

	char* new_str = new (std::nothrow) char[capacity_str];
	MyStringErrors::check_memory_allocate_exception(new_str);

	errno_t err = strncpy_s(new_str, capacity_str, this->str_, this->size_str_);
	MyStringErrors::check_strncpy_s(err);

	err = strncpy_s(new_str + this->size_str_, this->size_str_, str, strlen(str));
	MyStringErrors::check_strncpy_s(err);

	return my_str;
}
MyString& MyString::operator+=(const std::string& str) {

}
MyString& MyString::operator+=(const MyString& other) {

}*/