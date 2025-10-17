#include "MyString.h"
#include "AhoCorasick.h"

void MyString::allocate_memory(size_t size) {
	str_ = new (std::nothrow) char[size + 1];
	MyStringErrors::check_memory_allocate_exception(str_);

	size_str_ = size;
	capacity_str_ = size + 1;
	str_[size] = '\0';
}

void MyString::reallocate_memory(size_t size, bool is_equal) {
	if (str_ != nullptr) {

		size_t new_size = std::max(size, size_str_);

		//char* new_str = new (std::nothrow) char[size + 1];
		char* new_str = new (std::nothrow) char[new_size + 1];
		MyStringErrors::check_memory_allocate_exception(new_str);

		//errno_t err = memcpy_s(new_str, size + 1, str_, new_size);
		size_t max_copy_size = std::min(size, size_str_);
		errno_t err = memcpy_s(new_str, max_copy_size + 1, str_, max_copy_size);
		MyStringErrors::check_strncpy_s(err);

		if (size > size_str_) {
			memset(new_str + size_str_, '\0', size - size_str_ + 1);
		}


		if (!is_equal) {
			delete[] str_;
		}
		str_ = new_str;

	}
	else {
		str_ = new (std::nothrow) char[size + 1];
		MyStringErrors::check_memory_allocate_exception(str_);
		memset(str_, '\0', size + 1);
	}

	size_str_ = size;
	capacity_str_ = size + 1;
}

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
	/*	size_t new_size_str_ = strlen(str);
	size_t new_capacity_str_ = std::max(new_size_str_ + 1, capacity_str_);
	delete[] str_;

	str_ = new (std::nothrow) char[capacity_str_];
	MyStringErrors::check_memory_allocate_exception(str_);

	errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
	MyStringErrors::check_strncpy_s(err);
	return *this;*/
	this->replace(0, static_cast<int>(size_str_), str);
	return *this;
}
MyString& MyString::operator=(const std::string& str) {
	return this->operator=(str.c_str());
}
MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		/*		size_str_ = other.size_str_;
		capacity_str_ = other.capacity_str_;
		delete[] str_;

		str_ = new (std::nothrow) char[capacity_str_];
		MyStringErrors::check_memory_allocate_exception(str_);

		errno_t err = strncpy_s(str_, capacity_str_, other.str_, size_str_);
		MyStringErrors::check_strncpy_s(err);*/
		return this->operator=(other.c_str());
	}
	return *this;
}

MyString MyString::operator=(const char ch) {
	if (str_ != nullptr) {
		delete[] str_;
	}
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
	/*	MyString char_str(count, ch), left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + char_str + right_part;*/
	MyStringErrors::check_count_sumbols(count);

	//MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), count);

	if (count + size_str_ >= capacity_str_) {
		reallocate_memory(count + size_str_, false);
	}
	else {
		size_str_ += count;
	}

	//MyStringErrors::check_out_of_range_count(static_cast<int>(capacity_str_ - index - 1), count);
	errno_t err = memmove_s(str_ + index + count, capacity_str_ - index - count, str_ + index, size_str_ - index - count);
	MyStringErrors::check_memmove_s(err);
	str_[size_str_] = '\0';

	memset(str_ + index, ch, count);
	
}

void MyString::insert(const int index, const char* str) {
	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ + 1), index);
	/*	MyString char_str(str), left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + char_str + right_part;*/
	//MyStringErrors::check_index(index);

	bool is_equal = false;

	if (str == str_) {
		is_equal = true;
	}

	if (strlen(str) + size_str_ >= capacity_str_) {
		reallocate_memory(strlen(str) + size_str_, is_equal);
	}
	else {
		size_str_ += strlen(str);
	}

	errno_t err = memmove_s(str_ + index + strlen(str), capacity_str_ - index - strlen(str), str_ + index, size_str_ - index - strlen(str));
	MyStringErrors::check_memmove_s(err);

	err = memcpy_s(str_ + index, capacity_str_ - index, str, strlen(str));
	MyStringErrors::check_memcpy_s(err);

	if (is_equal) {
		delete[] str;
	}

}
void MyString::insert(const int index, const std::string& str) {
	this->insert(index, str.c_str());
}
void MyString::insert(const int index, const MyString& other) {
	/*	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), index);

	MyString left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + other + right_part;*/
	this->insert(index, other.c_str());
}

void MyString::insert(const int index, const char* str, const int count) {
	MyStringErrors::check_count_sumbols(count);

	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ + 1), index);

	MyStringErrors::check_out_of_range_count(static_cast<int>(strlen(str)), count);

	bool is_equal = false;

	if (str == str_) {
		is_equal = true;
	}

	if (count + size_str_ >= capacity_str_) {
		reallocate_memory(count + size_str_, is_equal);
	}
	else {
		size_str_ += count;
	}

	errno_t err = memmove_s(str_ + index + count, capacity_str_ - index - count, str_ + index, size_str_ - count - index);
	MyStringErrors::check_memmove_s(err);

	err = memcpy_s(str_ + index, capacity_str_ - index, str, count);
	MyStringErrors::check_memcpy_s(err);

}
void MyString::insert(const int index, const std::string& str, const int count) {
	this->insert(index, str.c_str(), count);
}
void MyString::insert(const int index, MyString& other, const int count) {
	this->insert(index, other.c_str(), count);
	/*	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), index);

	MyString left_part = this->substr(0, index),
		right_part = this->substr(index);

	*this = left_part + other.substr(0, count) + right_part;*/
}

void MyString::insert(const int index, const char* str, int s_index, int count) {
	MyStringErrors::check_count_sumbols(count);

	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ + 1), index);

	MyStringErrors::check_out_of_range_index(str, s_index);

	MyStringErrors::check_out_of_range_count(str + s_index, count);

	bool is_equal = false;

	if (str == str_) {
		is_equal = true;
	}

	if (count + size_str_ >= capacity_str_) {
		reallocate_memory(count + size_str_, is_equal);
	}
	else {
		size_str_ += count;
	}

	errno_t err = memmove_s(str_ + index + count, capacity_str_ - index - count, str_ + index, size_str_ - index - count);
	MyStringErrors::check_memmove_s(err);

	err = memmove_s(str_ + index, capacity_str_ - index, str + s_index, count);
	MyStringErrors::check_memcpy_s(err);
}
void MyString::insert(const int index, const std::string& str, int s_index, int count) {
	this->insert(index, str.c_str(), s_index, count);
}
void MyString::insert(const int index, MyString& other, int s_index, int count) {
	this->insert(index, other.c_str(), s_index, count);
}

void MyString::append(const int count, const char ch) {
	this->insert(static_cast<int>(size_str_), count, ch);
}

void MyString::append(const char* str) {
	this->insert(static_cast<int>(size_str_), str);
}
void MyString::append(const std::string& str) {
	this->insert(static_cast<int>(size_str_), str.c_str());
}
void MyString::append(MyString& other) {
	this->insert(static_cast<int>(size_str_), other.c_str());
}

void MyString::append(const char* str, const int count) {
	this->insert(static_cast<int>(size_str_), str, count);
}
void MyString::append(const std::string& str, const int count) {
	this->insert(static_cast<int>(size_str_), str.c_str(), count);
}
void MyString::append(MyString& other, const int count) {
	this->insert(static_cast<int>(size_str_), other.c_str(), count);
}

void MyString::append(const char* str, const int s_index, const int count) {
	this->insert(static_cast<int>(size_str_), str, s_index, count);
}
void MyString::append(const std::string& str, const int s_index, const int count) {
	this->insert(static_cast<int>(size_str_), str.c_str(), s_index, count);
}
void MyString::append(MyString& other, const int s_index, const int count) {
	this->insert(static_cast<int>(size_str_), other.c_str(), s_index, count);
}

void MyString::erase(const int index, const int count) {
	MyStringErrors::check_count_sumbols(count);

	//std::cout << "capacity_str_ = " << capacity_str_ << "\nsize_str_ = " << size_str_ << "\n";
	//std::cout << "You here\n";
	//std::cout << "std::max(capacity_str_ - 1, size_str_) = " << std::max(capacity_str_ - 1, size_str_);
	//std::cout << "dest = " << str_ + index << "\ndest_size =" << static_cast<int>(capacity_str_) - 1 - index 
	//	<< "\nsrc = " << str_ + index + count << "\ncount = " << static_cast<int>(capacity_str_) - 1 - index - count << "\n";
	//std::cout << "You here 2\n";
	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ != 0 ? capacity_str_ - 1 : 0), index);

	MyStringErrors::check_out_of_range_count(static_cast<int>((capacity_str_ != 0 ? capacity_str_ - 1 : 0) - index), count);

	errno_t err = memmove_s(str_ + index, capacity_str_ - 1 - index, str_ + index + count, capacity_str_ - 1 - index - count);
	MyStringErrors::check_memmove_s(err);

	memset(str_ + capacity_str_ - 1 - count, '\0', count);
	size_str_ -= count;
}

void MyString::replace(const int index, const int count, const char* str) {
	if (str_ != nullptr) this->erase(index, count);
	this->insert(index, str);
}
void MyString::replace(const int index, const int count, const std::string& str) {
	this->replace(index, count, str.c_str());
}
void MyString::replace(const int index, const int count, MyString& other) {
	this->replace(index, count, other.c_str());
}

void MyString::replace(const int index, const int count, const char* str, const int s_count) {
	if (str_ != nullptr) this->erase(index, count);
	this->insert(index, str, s_count);
}
void MyString::replace(const int index, const int count, const std::string& str, const int s_count) {
	this->replace(index, count, str.c_str(), s_count);
}
void MyString::replace(const int index, const int count, MyString& other, const int s_count) {
	this->replace(index, count, other.c_str(), s_count);
}

void MyString::replace(const int index, const int count, const char* str, const int s_index, const int s_count) {
	this->erase(index, count);
	this->insert(index, str, s_index, s_count);
}
void MyString::replace(const int index, const int count, const std::string& str, const int s_index, const int s_count) {
	this->replace(index, count, str.c_str(), s_index, s_count);
}
void MyString::replace(const int index, const int count, MyString& other, const int s_index, const int s_count) {
	this->replace(index, count, other.c_str(), s_index, s_count);
}

MyString MyString::substr(const int index) {
	MyStringErrors::check_out_of_range_index(static_cast<int>(size_str_), index);

	MyString other(this->c_str());
	other.erase(0, index);
	/*	MyString other;
	other.size_str_ = this->size_str_ - index;
	other.capacity_str_ = this->capacity_str_ - index;

	other.str_ = new (std::nothrow) char[other.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(other.str_);

	errno_t err = strncpy_s(other.str_, other.capacity_str_, this->str_ + index, this->size_str_);
	MyStringErrors::check_strncpy_s(err);*/
	return other;
}

MyString MyString::substr(const int index, const int count) {
	MyStringErrors::check_count_sumbols(count);

	MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), count);

	MyStringErrors::check_out_of_range_count(static_cast<int>(capacity_str_ - index - 1), count);

	MyString other(this->c_str());
	other.erase(0, index);
	other.erase(count, static_cast<int>(other.size_str_) - count);
	/*	MyString other;
	other.size_str_ = static_cast<size_t>(count);
	other.capacity_str_ = static_cast<size_t>(count + 1);

	other.str_ = new (std::nothrow) char[other.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(other.str_);

	errno_t err = strncpy_s(other.str_, other.capacity_str_, this->str_ + index, other.size_str_);
	MyStringErrors::check_strncpy_s(err);*/


	return other;
}

MyString MyString::operator+(const char* str) {
	if (str == nullptr) {
		return *this;
	}

	MyString my_str(*this);
	my_str.append(str);
	/*	MyString my_str;
	my_str.size_str_ = this->size_str_ + strlen(str);
	my_str.capacity_str_ = this->capacity_str_ + strlen(str);

	my_str.str_ = new (std::nothrow) char[my_str.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(my_str.str_);

	errno_t err = strncpy_s(my_str.str_, my_str.capacity_str_, this->str_, this->size_str_);
	MyStringErrors::check_strncpy_s(err);

	err = strncpy_s(my_str.str_ + this->size_str_, my_str.capacity_str_ - this->size_str_, str, strlen(str));
	MyStringErrors::check_strncpy_s(err);*/
	
	return my_str;
}

MyString MyString::operator+(const std::string& str) {
	return this->operator+(str.c_str());
}

MyString MyString::operator+(const MyString& other) {
	if (other.str_ == nullptr) {
		return *this;
	}
	/*	MyString my_str;
	my_str.size_str_ = this->size_str_ + other.size_str_;
	my_str.capacity_str_ = this->capacity_str_ + other.capacity_str_ - 1;

	my_str.str_ = new (std::nothrow) char[my_str.capacity_str_];
	MyStringErrors::check_memory_allocate_exception(my_str.str_);

	errno_t err = strncpy_s(my_str.str_, my_str.capacity_str_, this->str_, this->size_str_);
	MyStringErrors::check_strncpy_s(err);

	err = strncpy_s(my_str.str_ + this->size_str_, my_str.capacity_str_ - this->size_str_, other.str_, other.size_str_);
	MyStringErrors::check_strncpy_s(err);*/

	return this->operator+(other.c_str());
}

MyString& MyString::operator+=(const char* str) {
	if (str == nullptr) {
		return *this;
	}
	this->append(str);
	/*	size_t size_str = this->size_str_ + strlen(str);
	size_t capacity_str = this->capacity_str_ + strlen(str);
	//this->size_str_ += strlen(str);
	//this->capacity_str_ += strlen(str);

	char* new_str = new (std::nothrow) char[capacity_str];
	MyStringErrors::check_memory_allocate_exception(new_str);

	errno_t err = strncpy_s(new_str, capacity_str, this->str_, this->size_str_);
	MyStringErrors::check_strncpy_s(err);

	err = strncpy_s(new_str + this->size_str_, this->size_str_, str, strlen(str));
	MyStringErrors::check_strncpy_s(err);*/

	return *this;
}
MyString& MyString::operator+=(const std::string& str) {
	return this->operator+=(str.c_str());
}
MyString& MyString::operator+=(const MyString& other) {
	if (other.c_str() == nullptr) {
		return *this;
	}

	return this->operator+=(other.c_str());
}

char& MyString::operator[](const int index) {
	MyStringErrors::check_out_of_range_index(this->c_str(), index);

	return this->str_[index];
}

char MyString::operator[](const int index) const { 
	MyStringErrors::check_out_of_range_index(this->c_str(), index);

	return this->str_[index];
}

LexicographicComparisonStringsResult MyString::compare(const MyString& other) const {

	if (str_ == nullptr && other.c_str() != nullptr) {
		return LexicographicComparisonStringsResult::cIsSmaller;
	}
	if (str_ != nullptr && other.c_str() == nullptr) {
		return LexicographicComparisonStringsResult::cIsGreater;
	}
	
	int small_size = static_cast<int>(std::min(this->size_str_, other.size_str_));

	for (int i = 0; i < small_size; ++i) {
		if (this->operator[](i) > other.operator[](i)) {
			return LexicographicComparisonStringsResult::cIsGreater;
		}
		if (this->operator[](i) < other.operator[](i)) {
			return LexicographicComparisonStringsResult::cIsSmaller;
		}
	}

	return LexicographicComparisonStringsResult::cIsEqual;
}

bool MyString::operator>(const MyString& other) const {
	if (this->compare(other) == LexicographicComparisonStringsResult::cIsGreater) {
		return true;
	}
	else {
		return false;
	}
}
bool MyString::operator<(const MyString& other) const {
	if (this->compare(other) == LexicographicComparisonStringsResult::cIsSmaller) {
		return true;
	}
	else {
		return false;
	}
}
bool MyString::operator>=(const MyString& other) const {
	return !this->operator<(other);
}
bool MyString::operator<=(const MyString& other) const {
	return !this->operator>(other);
}
bool MyString::operator!=(const MyString& other) const {
	return !this->operator==(other);
}
bool MyString::operator==(const MyString& other) const {
	if (this->compare(other) == LexicographicComparisonStringsResult::cIsEqual) {
		return true;
	}
	else {
		return false;
	}
}

int MyString::find(const char* str) const {
	return this->find(str, 0);
}
int MyString::find(const std::string& str) const {
	return this->find(str.c_str(), 0);
}
int MyString::find(const MyString& other) const {
	return this->find(other.c_str(), 0);
}


int MyString::find(const char* str, const int index) const {
	MyStringErrors::check_out_of_range_index(str_, index);
	
	char* substing_ptr = strstr(str_ + index, str);

	if (substing_ptr) {
		return static_cast<int>(substing_ptr - str_);
	}
	else {
		return -1;
	}
}
int MyString::find(const std::string& str, const int index) const {
	return this->find(str.c_str(), index);
}
int MyString::find(const MyString& other, const int index) const {
	return this->find(other.c_str(), index);
}

MyString::MyString(MyString&& other) noexcept : 
	str_(other.str_), size_str_(other.size_str_), capacity_str_(other.capacity_str_) {
	other.str_ = nullptr;
	other.size_str_ = 0;
	other.capacity_str_ = 0;
}

MyString::MyString(const int number) : MyString(static_cast<long long>(number)) {}

MyString::MyString(const long long number) {
	if (number == 0) {
		allocate_memory(1);
		str_[0] = '0';
		return;
	}

	long long current_number = number;
	MyStringErrors::check_boundary_number(current_number);
	char numbers[MAX_NUMBER_LENGTH] = { 0 };


	bool is_negative = number < 0 ? true : false;
	int length;
	current_number = abs(current_number);
	for (length = 0; current_number != 0; ++length) {
		numbers[length] = static_cast<char>(current_number % 10 + 48);
		current_number /= 10;
	}

	allocate_memory(is_negative ? length + 1: length);
	

	if (is_negative) {
		str_[0] = '-';

		for (int i = 1; i < length + 1; ++i) {
			str_[i] = numbers[length - i];
		}
	}
	else {
		for (int i = 0; i < length; ++i) {
			str_[i] = numbers[length - i - 1];
		}
	}
}

MyString::MyString(const float number) {
	const int PRECISION = 10;

	if (number == 0.0f) {
		allocate_memory(1);
		str_[0] = '0';
		return;
	}

	bool is_negative = number < 0 ? true : false;
	float abs_number = abs(number);

	long long integer_part = static_cast<long long>(abs_number);
	float fractional = abs_number - static_cast<float>(integer_part);

	for (int i = 0; i < PRECISION; ++i) {
		if (fractional != static_cast<float>(static_cast<long long>(fractional))) {
			fractional *= 10;
		}
		else {
			break;
		}
	}

	long long fractional_part = static_cast<long long>(fractional);

	MyString integer_str(is_negative ? -integer_part : integer_part),
		fractional_str(fractional_part);

	*this = integer_str + "." + fractional_str;
}

MyString& MyString::operator=(MyString&& other) {
	if (this != &other) {
		delete[] str_;

		str_ = other.str_;
		size_str_ = other.size_str_;
		capacity_str_ = other.capacity_str_;

		other.str_ = nullptr;
		other.size_str_ = 0;
		other.capacity_str_ = 0;
	}
	
	return *this;
}

void MyString::findAll(std::unordered_map<MyString, std::vector<size_t>>& dictionary) const {
	AhoCorasick AC(dictionary);

	AC.add_words();
	AC.add_suff();
	AC.add_output_ref();
	AC.check_string(*this);
	/*	std::cout << "\nString: " << this->c_str() << "\n";
	for (auto& string : AC.includings) {
		std::cout << "string \"" << string.first << "\" there are in these indexes: ";
		for (auto& index : string.second) {
			std::cout << index << ", ";
		}
		std::cout << "\n";
	}*/

}

std::vector<size_t> MyString::findAll(const MyString& other) const {
	std::vector<size_t> includings = {};
	if (other.size_str_ > size_str_) {
		return includings;
	}
	if (other.size_str_ == 0) {
		for (size_t i = 0; i < size_str_; ++i) {
			includings.push_back(i);
		}
		return includings;
	}

	std::vector<size_t> pi(other.size_str_, 0);
	for (size_t i = 1, k = 0; i < other.size_str_; ++i) {
		while (k > 0 && other[k] != other[i]) {
			k = pi[k - 1];
		}
		if (other[k] == other[i]) {
			++k;
		}
		pi[i] = k;
	}

	for (size_t i = 0, j = 0; i < size_str_; ++i) {
		while (j > 0 && str_[i] != other[j]) {
			j = pi[j - 1];
		}

		if (str_[i] == other[j]) {
			++j;
		}

		if (j == other.size_str_) {
			includings.push_back(i - other.size_str_ + 1);
			j = pi[j - 1];
		}
	}

	return includings;
	
}

char MyString::at(const int index) {
	MyStringErrors::check_out_of_range_index(str_, index);

	return str_[index];
}

long long MyString::to_int() {
	MyStringErrors::check_null_pointer_string(str_);
	MyStringErrors::check_invalid_symbol_integer(str_);

	long long number = 0;
	bool is_negative = false;
	int i = 0;
	if (str_[0] == '-') {
		is_negative = true;
		i = 1;
	}
	for (i; i < MAX_NUMBER_LENGTH; ++i) {
		number += str_[i] * static_cast<long long>(pow(10, i - static_cast<float>(is_negative)));
	}

	if (is_negative) {
		number *= -1;
	}

	return number;
}

float MyString::to_float() {
	MyStringErrors::check_null_pointer_string(str_);
	MyStringErrors::check_invalid_symbol_float(str_);

	int i;
	bool has_dot = true;
	for (i = 0; i < size_str_ && str_[i] != '.'; ++i);
	if (i == size_str_) {
		--i;
		has_dot = false;
	}

	MyString integer_str(this->substr(0, i));
	long long integer_part = integer_str.to_int();
	if (has_dot) {
		MyString float_str(this->substr(i + 1));
		long long float_part = float_str.to_int();

		float part = static_cast<float>(float_part / pow(10, float_str.size()));

		return static_cast<float>(integer_part) + part;
	}
	else {
		return static_cast<float>(integer_part);
	}
	
}



/*
Caregory1:
{
	Easy:
	{
		молоко: создается коровой
		кот: 
	}

	Normal:


	Hard:
}

\

Caregory1:

*/