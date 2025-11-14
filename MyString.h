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
#include "BaseIterator.h"

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
private:

	template <typename T>
	struct is_my_string_iterator {
	private:
		template <typename U>
		static auto test(int) -> decltype(
			std::declval<U>().get_container(),      
			std::declval<U>().get_position(),       
			std::true_type{}
		);

		template<typename>
		static std::false_type test(...);

	public:
		static constexpr bool value = decltype(test<T>(0))::value;
	};

	template<typename T>
	static constexpr bool is_my_string_iterator_v = is_my_string_iterator<T>::value;



public:
	class const_iterator;
	class iterator;
	class const_reverse_iterator;
	class reverse_iterator;

	//1.default constructor
	MyString(); // : str_(nullptr), size_str_(0), capacity_str_(0) {}

	//2. copy constructor from origin string (const char*)
	MyString(const char* str); /*{
		MyStringErrors::check_null_pointer_string(str);

		allocate_memory(strlen(str));

		errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
		MyStringErrors::check_strncpy_s(err);
	}*/ 

	//3. copy constructor from origin string (const std::string&)
	MyString(const std::string& str); //: MyString(str.c_str()) {}

	//4. copy constructor from other MyString
	MyString(const MyString& other); /*: MyString(other.c_str()) {
		/*MyStringErrors::check_null_pointer_string(other.str_);
		
		capacity_str_ = other.capacity_str_;
		size_str_ = other.size_str_;

		str_ = new (std::nothrow) char[capacity_str_];
		MyStringErrors::check_memory_allocate_exception(str_);

		errno_t err = strncpy_s(str_, capacity_str_, other.str_, size_str_);
		MyStringErrors::check_strncpy_s(err);*/	  

	//5. Initializing constructor with definite number of symbols from const char*
	MyString(const char* str, const int count); /*{
		MyStringErrors::check_count_sumbols(count);

		MyStringErrors::check_null_pointer_string(str, count);

		MyStringErrors::check_out_of_range_count(str, count);

	allocate_memory(static_cast<size_t>(count));

	errno_t err = strncpy_s(str_, capacity_str_, str, size_str_);
	MyStringErrors::check_strncpy_s(err);
}*/

	//6. Initializing constructor with definite number of symbols from std::string
	MyString(const std::string& str, const int count); // : MyString(str.c_str(), count) {}

	//7. Initializing constructor with definite number of symbols from MyString
	MyString(const MyString& other, const int count); /*: MyString(other.c_str(), count) {
		/*		MyStringErrors::check_count_sumbols(count);

		MyStringErrors::check_null_pointer_string(other.str_, count);

		MyStringErrors::check_out_of_range_count(other.str_, count);

		size_str_ = static_cast<size_t>(count);
		capacity_str_ = static_cast<size_t>(count + 1);
		str_ = new (std::nothrow) char[count + 1];

		MyStringErrors::check_memory_allocate_exception(str_);

		errno_t err = strncpy_s(str_, capacity_str_, other.str_, size_str_);
		MyStringErrors::check_strncpy_s(err);*/

	//8. Initializing constructor with definite number of same symbols
	MyString(const int count, const char c); /* {
		MyStringErrors::check_count_sumbols(count);

		/*		size_str_ = static_cast<size_t>(count);
		capacity_str_ = static_cast<size_t>(count + 1);
		str_ = new (std::nothrow) char[capacity_str_];

		MyStringErrors::check_memory_allocate_exception(str_);
	allocate_memory(static_cast<size_t>(count));

	memset(str_, c, count);
	str_[count] = '\0';
}*/

	//9. Destructor
	~MyString(); /*{
		delete[] str_;
		str_ = nullptr;
	}*/ 

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
	char* c_str() const; /*const {
		return str_;
	}*/ 

	//15. Get count of symbols of char in string
	size_t size() const; /*{
		return size_str_;
	}*/ 

	//16. Get volume of allocated memory
	size_t capacity() const; /* {
		return capacity_str_;
	}*/

	//17. Return true if string is empty
	bool empty() const; /*{
		return str_ == nullptr;
	}*/ 

	//18. Insert count symbols ch by index
	void insert(int index, int count, char ch);

	template <typename IteratorType>
	void insert(const IteratorType& iter, const int count, const char ch);

	//19, 20, 21. Insert string by index
	void insert(const int index, const char* str);
	void insert(const int index, const std::string& str);
	void insert(const int index, const MyString& other);

	template <typename IteratorType>
	void insert(const IteratorType& iter, const char* str);
	template <typename IteratorType>
	void insert(const IteratorType& iter, const std::string& str);
	template <typename IteratorType>
	void insert(const IteratorType& iter, const MyString& other);

	//22, 23, 24. Isert count symbols of string by index
	void insert(const int index, const char* str, const int count);
	void insert(const int index, const std::string& str, const int count);
	void insert(const int index, const MyString& other, const int count);

	template <typename IteratorType>
	void insert(const IteratorType& iter, const char* str, const int count);
	template <typename IteratorType>
	void insert(const IteratorType& iter, const std::string& str, const int count);
	template <typename IteratorType>
	void insert(const IteratorType& iter, const MyString& other, const int count);

	//25, 26, 27. Insert count symbols of string from s_index by index
	void insert(const int index, const char* str, int s_index, int count);
	void insert(const int index, const std::string& str, int s_index, int count);
	void insert(const int index, const MyString& other, int s_index, int count);

	template <typename IteratorType1, typename IteratorType2>
	auto insert(const IteratorType1& iter, const char* str, const IteratorType2& s_iter, const int count) ->
	 decltype(iter.get_position(), s_iter.get_position(), void()) {
		MyStringErrors::check_iterator_validity(this, iter.get_container());

		MyStringErrors::check_count_sumbols(count);

		MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ + 1), iter.get_position());

		MyStringErrors::check_out_of_range_index(str, s_iter.get_position());

		MyStringErrors::check_out_of_range_count(str + s_iter.get_position(), count);

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

		if (count == 0 || strlen(str) == 0) {
			return;
		}

		{
			auto border_it = rbegin() - (size_str_ - count - iter.get_position());
			for (auto it = rbegin(); it < border_it; ++it) {
				*it = *(it - count);
			}
		}

		{
			iterator border_it(this, iter.get_position() + (count - 1));
			for (auto it = begin() + iter.get_position(); it <= border_it; ++it) {
				*it = str[it.get_position() - iter.get_position() + s_iter.get_position()];
			}
		}


		if (is_equal) {
			delete[] str;
		}

	}
	template <typename IteratorType1, typename IteratorType2>
	auto insert(const IteratorType1& iter, const std::string& str, const IteratorType2& s_iter, const int count) ->
		decltype(iter.get_position(), s_iter.get_position(), void()) {
		this->insert(iter, str.c_str(), s_iter, count);
	}
	template <typename IteratorType1, typename IteratorType2>
	auto insert(const IteratorType1& iter, const MyString& other, const IteratorType2& s_iter, const int count) ->
		decltype(iter.get_position(), s_iter.get_position(), void()) {
		MyStringErrors::check_iterator_validity(&other, s_iter.get_container());

		this->insert(iter, other.c_str(), s_iter, count);
	}
	template <typename IteratorType1, typename IteratorType2>
	//void insert(const IteratorType1& iter, const IteratorType2& s_iter, const int count);
	auto insert(const IteratorType1& iter, const IteratorType2& s_iter, const int count)
		-> decltype(iter.get_position(), s_iter.get_position(), void()) {
		this->insert(iter, *(s_iter.get_container()), s_iter, count);
	}
	

	//28. Append count symbols
	void append(const int count, const char ch);

	//29, 30, 31. Append string 
	void append(const char* str);
	void append(const std::string& str);
	void append(const MyString& other);

	//32, 33, 34. Append count symbols of string 
	void append(const char* str, const int count);
	void append(const std::string& str, const int count);
	void append(const MyString& other, const int count);

	//35, 36, 37. Append count symbols of string from s_index
	void append(const char* str, const int s_index, const int count);
	void append(const std::string& str, const int s_index, const int count);
	void append(const MyString& other, const int s_index, const int count);

	template <typename IteratorType>
	auto append(const char* str, const IteratorType& iter, const int count) -> 
		decltype(iter.get_position(), void()){
		iterator it_end = this->end();
		//this->insert(it_end, str, iter, count);
		this->insert<iterator, IteratorType>(it_end, str, iter, count);
	}
	template <typename IteratorType>
	auto append(const std::string& str, const IteratorType& iter, const int count) ->
		decltype(iter.get_position(), void()) {
		this->insert<iterator, IteratorType>(this->end(), str, iter, count);
	}
	template <typename IteratorType>
	auto append(const MyString& other, const IteratorType& iter, const int count) ->
		decltype(iter.get_position(), void()) {
		//std::cout << "LOX";
		this->insert<iterator, IteratorType>(this->end(), other, iter, count);
	}

	//38. Remove count symbols by index
	void erase(const int index, const int count);

	template <typename IteratorType>
	auto erase(const IteratorType& iter, const int count) ->
		decltype(iter.get_position(), void()) {

		MyStringErrors::check_iterator_validity(iter.get_container(), this);

		MyStringErrors::check_count_sumbols(count);

		MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ != 0 ? capacity_str_ - 1 : 0), iter.get_position());

		MyStringErrors::check_out_of_range_count(static_cast<int>((capacity_str_ != 0 ? capacity_str_ - 1 : 0) - iter.get_position()), count);

		auto border_it = end() - count;

		for (auto it = begin() + iter.get_position(); it < border_it; ++it) {
			*it = *(it + count);
		}

		memset(str_ + size_str_ - count, '\0', count);
		size_str_ -= count;
	}

	//39, 40, 41. Replace count symbols on string by index
	void replace(const int index, const int count, const char* str);
	void replace(const int index, const int count, const std::string& str);
	void replace(const int index, const int count, const MyString& other);

	template <typename IteratorType>
	auto replace(const IteratorType& iter, const int count, const char* str) -> 
		decltype(iter.get_position(), void()) {
		if (str_ != nullptr) this->erase(iter, count);
		this->insert(iter, str);
	}
	template <typename IteratorType>
	auto replace(const IteratorType& iter, const int count, const std::string& str) ->
		decltype(iter.get_position(), void()) {
		this->replace(iter, count, str.c_str());
	}
	template <typename IteratorType>
	auto replace(const IteratorType& iter, const int count, const MyString& other) -> 
		decltype(iter.get_position(), void()) {
		this->replace(iter, count, other.c_str());
	}


	//42, 43, 44. Replace count symbols on s_count symbols of string by index
	void replace(const int index, const int count, const char* str, const int s_count);
	void replace(const int index, const int count, const std::string& str, const int s_count);
	void replace(const int index, const int count, const MyString& other, const int s_count);

	template <typename IteratorType>
	auto replace(const IteratorType& iter, const int count, const char* str, const int s_count) -> 
		decltype(iter.get_position(), void()) {
		if (str_ != nullptr) this->erase(iter, count);
		this->insert(iter, str, s_count);
	}
	template <typename IteratorType>
	auto replace(const IteratorType& iter, const int count, const std::string& str, const int s_count) -> 
		decltype(iter.get_position(), void()) {
		this->replace(iter, count, str.c_str(), s_count);
	}
	template <typename IteratorType>
	auto replace(const IteratorType& iter, const int count, const MyString& other, const int s_count) -> 
		decltype(iter.get_position(), void()) {
		this->replace(iter, count, other.c_str(), s_count);
	}

	//45, 46, 47. Replace count symbols on s_count symbols of string by index from s_index
	void replace(const int index, const int count, const char* str, const int s_index, const int s_count);
	void replace(const int index, const int count, const std::string& str, const int s_index, const int s_count);
	void replace(const int index, const int count, const MyString& other, const int s_index, const int s_count);

	template <typename IteratorType1, typename IteratorType2>
	auto replace(const IteratorType1& iter, const int count, const char* str, const IteratorType2& s_iter, const int s_count) -> 
		decltype(iter.get_position(), s_iter.get_position(), void()) {
		if (str_ != nullptr) this->erase(iter, count); //
		this->insert(iter, str, s_iter, s_count);
	}
	template <typename IteratorType1, typename IteratorType2>
	auto replace(const IteratorType1& iter, const int count, const std::string& str, const IteratorType2& s_iter, const int s_count) -> 
		decltype(iter.get_position(), s_iter.get_position(), void()) {
		this->replace(iter, count, str.c_str(), s_iter, s_count);
	}
	template <typename IteratorType1, typename IteratorType2>
	auto replace(const IteratorType1& iter, const int count, const MyString& other, const IteratorType2& s_iter, const int s_count) -> 
		decltype(iter.get_position(), s_iter.get_position(), void()) {
		MyStringErrors::check_iterator_validity(&other, s_iter.get_container());
		this->replace(iter, count, other.c_str(), s_iter, s_count);
	}
	template <typename IteratorType1, typename IteratorType2>
	auto replace(const IteratorType1& iter, const int count, const IteratorType2& s_iter, const int s_count) ->
		decltype(iter.get_position(), s_iter.get_position(), void()) {
		this->replace(iter, count, *(s_iter.get_container()), s_iter, s_count);
	}

	//48. Return substring from index
	MyString substr(const int index) const;

	template <typename IteratorType>
	auto substr(const IteratorType& iter) const -> 
		std::enable_if_t<is_my_string_iterator_v<IteratorType>, MyString> {
		MyStringErrors::check_iterator_validity(this, iter.get_container());
		MyStringErrors::check_out_of_range_index(static_cast<int>(size_str_), iter.get_position());

		MyString other(this->c_str());
		other.erase(other.begin(), iter.get_position());

		return other;
	}

	//49. Return substring with some length from index
	MyString substr(const int index, const int count) const;

	template <typename IteratorType>
	auto substr(const IteratorType& iter, const int count) const -> 
		std::enable_if_t<is_my_string_iterator_v<IteratorType>, MyString> {
		MyStringErrors::check_iterator_validity(this, iter.get_container());
		MyStringErrors::check_count_sumbols(count);
		MyStringErrors::check_out_of_range_index(static_cast<int>(capacity_str_ - 1), count);
		MyStringErrors::check_out_of_range_count(static_cast<int>(capacity_str_ - iter.get_position() - 1), count);

		MyString other(this->c_str());
		other.erase(other.begin(), iter.get_position());
		//std::cout << other.c_str() << "\n";
		other.erase(other.begin() + count, static_cast<int>(other.size_str_) - count);
		//std::cout << other.c_str() << "\n";
		return other;
	}

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

	template <typename IteratorType>
	auto operator[](const IteratorType& iter) -> 
		decltype(iter.get_container(), *iter, static_cast<char&>(*iter)) {
		MyStringErrors::check_iterator_validity(this, iter.get_container());

		return *iter;
	}
	template <typename IteratorType>
	auto operator[](const IteratorType& iter) const -> 
		decltype(iter.get_container(), *iter, char()) {
		MyStringErrors::check_iterator_validity(this, iter.get_container());

		return *iter;
	}

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

	template <typename IteratorType>
	auto find(const char* str, const IteratorType& iter) const -> 
		decltype(iter.get_position(), iter.get_position(), int()) {
		MyStringErrors::check_iterator_validity(this, iter.get_container());
		MyStringErrors::check_out_of_range_index(str_, iter.get_position());

		char* substing_ptr = strstr(str_ + iter.get_position(), str);

		if (substing_ptr) {
			return static_cast<int>(substing_ptr - str_);
		}
		else {
			return -1;
		}
	}
	template <typename IteratorType>
	auto find(const std::string& str, const IteratorType& iter) const -> 
		decltype(iter.get_position(), iter.get_position(), int()) {
		return this->find(str.c_str(), iter);
	}
	template <typename IteratorType>
	auto find(const MyString& other, const IteratorType& iter) const -> 
		decltype(iter.get_position(), iter.get_position(), int()) {
		return this->find(other.c_str(), iter);
	}

	//Additional functional of MyString class
	MyString(MyString&& other) noexcept;
	MyString(const int number);
	MyString(const long long number);
	MyString(const float number);
	MyString& operator=(MyString&& other) noexcept;
	char at(const int index) const;
	long long to_int() const;
	float to_float() const;
	void findAll(std::unordered_map<MyString, std::vector<size_t>>& dictionary) const;
	std::vector<size_t> findAll(const MyString& other) const;


	MyString& operator+=(const char ch);

	

	const_iterator cbegin() const;
	const_iterator cend() const;
	iterator begin() const;
	iterator end() const;
	const_reverse_iterator rcbegin() const;
	const_reverse_iterator rcend() const;
	reverse_iterator rbegin() const;
	reverse_iterator rend() const;

	struct const_reversed_range {
		const MyString* str;
		
		const_reverse_iterator begin() const {
			return str->rcbegin();
		}
		const_reverse_iterator end() const {
			return str->rcend();
		}
	};


	const_reversed_range reversed() const {
		return const_reversed_range{ this };
	}

	struct reversed_range {
		MyString* str;

		reverse_iterator begin() {
			return str->rbegin();
		}
		reverse_iterator end() {
			return str->rend();
		}
	};

	reversed_range reversed() {
		return reversed_range{ this };
	}

private:
	char* str_;
	size_t size_str_; 
	size_t capacity_str_;

	void allocate_memory(size_t size);
	void reallocate_memory(size_t size, bool is_equal);

	/*template <typename T>
	struct is_my_string_iterator {
	private:
		template <typename U>
		static auto test(int) -> decltype(
			std::declval<U>().get_container(),
			std::declval<U>().get_position(),
			std::enable_if_t<
				std::is_same_v<decltype(std::declval<U>().get_container()), MyString&> ||
				std::is_same_v<decltype(std::declval<U>().get_container()), const MyString&>
			>(),
			std::is_same_v<decltype(std::declval<U>().get_position()), size_t>,
			std::true_type{}
			);

		template<typename>
		static std::false_type test(...);

	public:
		static constexpr bool value = decltype(test<T>(0))::value;
	};*/
	
public:

	class iterator : public BaseIterator<iterator, char&, MyString*> {
	public:
		using BaseIterator<iterator, char&, MyString*>::BaseIterator;
	};

	class const_iterator : public BaseIterator<const_iterator, const char&, const MyString*> {
	public:
		using BaseIterator<const_iterator, const char&, const MyString*>::BaseIterator;
	};

	class reverse_iterator : public ReversedWrapper<iterator> {
	public:
		explicit reverse_iterator(const iterator& it)
			: ReversedWrapper<iterator>(it) {}
	};

	class const_reverse_iterator : public ReversedWrapper<const_iterator> {
	public:
		explicit const_reverse_iterator(const const_iterator& it)
			: ReversedWrapper<const_iterator>(it) {}
	};

	/*template <typename IteratorType>
	class direct_iterator_;

	template <typename IteratorType>
	class reverse_iterator_;

	template <typename IteratorType, typename StringType>
	class advanced_iterator_;


	template <typename IteratorType, typename ReferenceType, typename StringType>
	class base_iterator_ {
	public:

		base_iterator_();
		base_iterator_(StringType, size_t);

		ReferenceType operator*() const;
		bool operator==(const IteratorType&) const;
		bool operator!=(const IteratorType&) const;
	protected:
		size_t pos_;
		StringType ptr_;

		friend class direct_iterator_<IteratorType>;
		friend class reverse_iterator_<IteratorType>;
		friend class advanced_iterator_<IteratorType, StringType>;
	};

	template <typename IteratorType>
	class direct_iterator_ {
	public:
		IteratorType& operator++();
		IteratorType operator++(int);
	};

	template <typename IteratorType>
	class reverse_iterator_ {
	public:
		IteratorType& operator--();
		IteratorType operator--(int);
	};

	template <typename IteratorType, typename StringType>
	class advanced_iterator_ {
	public:
		IteratorType operator+(ptrdiff_t) const;
		IteratorType operator-(ptrdiff_t) const;
		ptrdiff_t operator-(const IteratorType&) const;

		bool operator>(const IteratorType&) const;
		bool operator<(const IteratorType&) const;
		bool operator>=(const IteratorType&) const;
		bool operator<=(const IteratorType&) const;

		StringType get_ptr() const;
		size_t get_pos() const;
	};

	

public:
	class const_iterator : 
		public base_iterator_<const_iterator, const char&, const MyString*>, 
		public direct_iterator_<const_iterator>, 
		public advanced_iterator_<const_iterator, const MyString*> {
	public:
		using base_iterator_<const_iterator, const char&, const MyString*>::base_iterator_;
	};

	class iterator : 
		public base_iterator_<iterator, char&, MyString*>, 
		public direct_iterator_<iterator>,
		public advanced_iterator_<iterator, MyString*> {
	public:
		using base_iterator_<iterator, char&, MyString*>::base_iterator_;
	};

	class const_reverse_iterator : 
		public base_iterator_<const_reverse_iterator, const char&, const MyString*>, 
		public reverse_iterator_<const_reverse_iterator>,
		public advanced_iterator_<const_reverse_iterator, const MyString*> {
	public:
		using base_iterator_<const_reverse_iterator, const char&, const MyString*>::base_iterator_;
	};

	class reverse_iterator : 
		public base_iterator_<reverse_iterator, char&, MyString*>, 
		public reverse_iterator_<reverse_iterator>,
		public advanced_iterator_<reverse_iterator, MyString*> {
	public:
		using base_iterator_<reverse_iterator, char&, MyString*>::base_iterator_;
	};
	class reversed_wrapper : public reverse_iterator {
	public:
		reversed_wrapper(MyString* ptr, size_t pos);

		reversed_wrapper& operator++();
		reversed_wrapper operator++(int);
	};


	class const_reversed_wrapper : public const_reverse_iterator {
	public:
		const_reversed_wrapper(const MyString* ptr, size_t pos);

		const_reversed_wrapper& operator++();
		const_reversed_wrapper operator++(int);
	};

	struct const_reversed_range {
		const MyString* str;

		const_reversed_wrapper begin() const;
		const_reversed_wrapper end() const;
	};

	
	const_reversed_range reversed() const;
	
	struct reversed_range {
		MyString* str;

		reversed_wrapper begin();
		reversed_wrapper end();
	};

	reversed_range reversed();*/
	

};
/*extern template class MyString::base_iterator_<MyString::const_iterator, const char&, const MyString*>;
extern template class MyString::base_iterator_<MyString::iterator, char&, MyString*>;
extern template class MyString::base_iterator_<MyString::const_reverse_iterator, const char&, const MyString*>;
extern template class MyString::base_iterator_<MyString::reverse_iterator, char&, MyString*>;

extern template class MyString::direct_iterator_<MyString::const_iterator>;
extern template class MyString::direct_iterator_<MyString::iterator>;

extern template class MyString::reverse_iterator_<MyString::const_reverse_iterator>;
extern template class MyString::reverse_iterator_<MyString::reverse_iterator>;

extern template class MyString::advanced_iterator_<MyString::const_iterator, const MyString*>;
extern template class MyString::advanced_iterator_<MyString::iterator, MyString*>;
extern template class MyString::advanced_iterator_<MyString::const_reverse_iterator, const MyString*>;
extern template class MyString::advanced_iterator_<MyString::reverse_iterator, MyString*>;*/

namespace std {
	template<>
	struct hash<MyString> {
		size_t operator()(const MyString& s) const {
			
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

