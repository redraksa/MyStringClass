#ifndef _BASEITERATOR_H_
#define _BASEITERATOR_H_
#include "MyStringErrors.h"
#include <cstddef>

class MyString;

template<typename IteratorType, typename ReferenceType, typename StringType>
class BaseIterator
{
public:
	using reference = ReferenceType;
	using string_type = StringType;

	BaseIterator(string_type ptr, size_t pos) : ptr_(ptr), pos_(pos) {
		MyStringErrors::check_out_of_range_iterator(this->ptr_->size(), this->pos_);
	}

	reference operator*() const {
		return (*ptr_)[pos_];
	}

	IteratorType& operator++() {
		MyStringErrors::check_out_of_range_iterator(this->ptr_->size(), this->pos_ + 1);
		++this->pos_;
		return static_cast<IteratorType&>(*this);
	}
	IteratorType operator++(int) {
		MyStringErrors::check_out_of_range_iterator(this->ptr_->size(), this->pos_ + 1);

		IteratorType temp = static_cast<IteratorType&>(*this);
		++(*this);
		return temp;
	}
	IteratorType& operator--() {
		MyStringErrors::check_out_of_range_iterator(this->ptr_->size(), static_cast<int>(this->pos_) - 1);
		--this->pos_;
		return static_cast<IteratorType&>(*this);
	}
	IteratorType operator--(int) {
		MyStringErrors::check_out_of_range_iterator(this->ptr_->size(), static_cast<int>(this->pos_) - 1);

		IteratorType temp = static_cast<IteratorType&>(*this);
		--(*this);
		return temp;
	}

	bool operator==(const IteratorType& other) const {
		MyStringErrors::check_iterators(this->ptr_, other.ptr_);
		return pos_ == other.pos_; // || this->pos_ == -1;
	}
	bool operator!=(const IteratorType& other) const {
		return pos_ != std::numeric_limits<size_t>::max() && !this->operator==(other) || this->pos_ == 0; // || this->pos_ == 0;
	}

	IteratorType operator+(const ptrdiff_t n) const {
		MyStringErrors::check_out_of_range_iterator(this->ptr_->size(), static_cast<int>(this->pos_) + n);
		return IteratorType(this->ptr_, this->pos_ + n);
	}
	IteratorType operator-(const ptrdiff_t n) const {
		MyStringErrors::check_out_of_range_iterator(this->ptr_->size(), static_cast<int>(this->pos_) - n);
		return IteratorType(this->ptr_, this->pos_ - n);
	}
	ptrdiff_t operator-(const IteratorType& other) const {
		MyStringErrors::check_iterators(this->ptr_, other.ptr_);
		return static_cast<ptrdiff_t>(this->pos_) - static_cast<ptrdiff_t>(other.pos_);
	}

	bool operator>(const IteratorType& other) const {
		MyStringErrors::check_iterators(this->ptr_, other.ptr_);
		return this->pos_ > other.pos_;
	}
	bool operator<(const IteratorType& other) const {
		MyStringErrors::check_iterators(this->ptr_, other.ptr_);
		return this->pos_ < other.pos_;
	}
	bool operator>=(const IteratorType& other) const {
		return !this->operator<(other);
	}
	bool operator<=(const IteratorType& other) const {
		return !this->operator>(other);
	}

	string_type get_container() const { return ptr_; }
	size_t get_position() const { return pos_; }
private:
	string_type ptr_;
	size_t pos_;
};

template<typename IteratorType>
class ReversedWrapper
{
public:
	using reference = typename IteratorType::reference;       
	using string_type = typename IteratorType::string_type;

	ReversedWrapper(const IteratorType& iterator) : iterator_(iterator) {}

	reference operator*() const {
		return *iterator_;
	}

	ReversedWrapper& operator++() {
		--iterator_;
		return *this;
	}
	ReversedWrapper operator++(int) {
		IteratorType temp = iterator_;
		--iterator_;
		return temp;
	}
	ReversedWrapper& operator--() {
		++iterator_;
		return *this;
	}
	ReversedWrapper operator--(int) {
		IteratorType temp = iterator_;
		++iterator_;
		return temp;
	}

	bool operator==(const ReversedWrapper& other) const {
		//std::cout << "operator==" << (iterator_ == other.iterator_) << " ";
		return iterator_ == other.iterator_; // || iterator_.get_position() == -1;
	}
	bool operator!=(const ReversedWrapper& other) {
		//std::cout << "operator!=" << (iterator_ != other.iterator_) << " ";
		return iterator_ != other.iterator_;
	}

	ReversedWrapper operator+(const ptrdiff_t n) const {
		return iterator_ + n;
	}
	ReversedWrapper operator-(const ptrdiff_t n) const {
		return iterator_ - n;
	}
	ptrdiff_t operator-(const ReversedWrapper& other) const {
		return iterator_ - other;
	}

	bool operator>(const ReversedWrapper& other) const {
		return iterator_ < other.iterator_;
	}
	bool operator<(const ReversedWrapper& other) const {
		return iterator_ > other.iterator_;
	}
	bool operator>=(const ReversedWrapper& other) const {
		return iterator_ <= other.iterator_;
	}
	bool operator<=(const ReversedWrapper& other) const {
		return iterator_ < other.iterator_;
	}

	string_type get_container() const { return iterator_.get_container(); }
	size_t get_position() const { return iterator_.get_position(); }
private:
	IteratorType iterator_;
};

/*extern template class BaseIterator<MyString::iterator, char&, MyString*>;
extern template class BaseIterator<MyString::const_iterator, const char&, const MyString*>;

extern template class ReversedWrapper<MyString::const_iterator>;
extern template class ReversedWrapper<MyString::iterator>;*/



#endif // !_BASEITERATOR_H_


