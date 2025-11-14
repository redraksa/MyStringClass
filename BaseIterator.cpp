/*#include "BaseIterator.h"
#include "MyString.h"

template<typename IteratorType, typename ReferenceType, typename StringType>
BaseIterator<IteratorType, ReferenceType, StringType>::BaseIterator(BaseIterator<IteratorType, ReferenceType, StringType>::string_type ptr, size_t pos) : ptr_(ptr), pos_(pos) {
	MyStringErrors::check_out_of_range_index(this->ptr_->size(), this->pos_);
}

template<typename IteratorType, typename ReferenceType, typename StringType>
BaseIterator<IteratorType, ReferenceType, StringType>::reference BaseIterator<IteratorType, ReferenceType, StringType>::operator*() const {
	return this->ptr_->operator[](this->pos_);
}

template<typename IteratorType, typename ReferenceType, typename StringType>
IteratorType& BaseIterator<IteratorType, ReferenceType, StringType>::operator++() {
	MyStringErrors::check_out_of_range_index(this->ptr_->size(), this->pos_ + 1);
	++this->pos_;
	return *this;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
IteratorType BaseIterator<IteratorType, ReferenceType, StringType>::operator++(int) {
	MyStringErrors::check_out_of_range_index(this->ptr_->size(), this->pos_ + 1);

	IteratorType temp = *this;
	++(*this);
	return temp;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
IteratorType& BaseIterator<IteratorType, ReferenceType, StringType>::operator--() {
	MyStringErrors::check_out_of_range_index(this->ptr_->size(), static_cast<int>(this->pos_) - 1);
	--this->pos_;
	return *this;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
IteratorType BaseIterator<IteratorType, ReferenceType, StringType>::operator--(int) {
	MyStringErrors::check_out_of_range_index(this->ptr_->size(), static_cast<int>(this->pos_) - 1);

	IteratorType temp = *this;
	--(*this);
	return temp;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
bool BaseIterator<IteratorType, ReferenceType, StringType>::operator==(const IteratorType& other) const {
	MyStringErrors::check_iterators(this->ptr_, other.ptr_);
	return pos_ == other.pos_ || this->pos_ == -1;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
bool BaseIterator<IteratorType, ReferenceType, StringType>::operator!=(const IteratorType& other) const {
	return !this->operator==(other) || this->pos_ == 0;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
IteratorType BaseIterator<IteratorType, ReferenceType, StringType>::operator+(const ptrdiff_t n) const {
	MyStringErrors::check_out_of_range_index(this->ptr_->size(), static_cast<int>(this->pos_) + n);
	return IteratorType(this->ptr_, this->pos_ + n);
}

template<typename IteratorType, typename ReferenceType, typename StringType>
IteratorType BaseIterator<IteratorType, ReferenceType, StringType>::operator-(const ptrdiff_t n) const {
	MyStringErrors::check_out_of_range_index(this->ptr_->size(), static_cast<int>(this->pos_) - n);
	return IteratorType(this->ptr_, this->pos_ - n);
}

template<typename IteratorType, typename ReferenceType, typename StringType>
ptrdiff_t BaseIterator<IteratorType, ReferenceType, StringType>::operator-(const IteratorType& other) const {
	MyStringErrors::check_iterators(this->ptr_, other.ptr_);
	return static_cast<ptrdiff_t>(this->pos_) - static_cast<ptrdiff_t>(other.pos_);
}

template<typename IteratorType, typename ReferenceType, typename StringType>
bool BaseIterator<IteratorType, ReferenceType, StringType>::operator>(const IteratorType& other) const {
	MyStringErrors::check_iterators(this->ptr_, other.ptr_);
	return this->pos_ > other.pos_;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
bool BaseIterator<IteratorType, ReferenceType, StringType>::operator<(const IteratorType& other) const {
	MyStringErrors::check_iterators(this->ptr_, other.ptr_);
	return this->pos_ < other.pos_;
}

template<typename IteratorType, typename ReferenceType, typename StringType>
bool BaseIterator<IteratorType, ReferenceType, StringType>::operator>=(const IteratorType& other) const {
	return !this->operator<(other);
}

template<typename IteratorType, typename ReferenceType, typename StringType>
bool BaseIterator<IteratorType, ReferenceType, StringType>::operator<=(const IteratorType& other) const {
	return !this->operator>(other);
}

template<typename IteratorType>
ReversedWrapper<IteratorType>::ReversedWrapper(const IteratorType& iterator) : iterator_(iterator) {}

template<typename IteratorType>
ReversedWrapper<IteratorType>::reference ReversedWrapper<IteratorType>::operator*() const {
	return *iterator_;
}

template<typename IteratorType>
ReversedWrapper<IteratorType>& ReversedWrapper<IteratorType>::operator++() {
	--iterator_;
	return this;
}

template<typename IteratorType>
ReversedWrapper<IteratorType> ReversedWrapper<IteratorType>::operator++(int) {
	IteratorType temp = iterator_;
	--iterator_;
	return temp;
}

template<typename IteratorType>
ReversedWrapper<IteratorType>& ReversedWrapper<IteratorType>::operator--() {
	++iterator_;
	return this;
}

template<typename IteratorType>
ReversedWrapper<IteratorType> ReversedWrapper<IteratorType>::operator--(int) {
	IteratorType temp = iterator_;
	++iterator_;
	return temp;
}

template<typename IteratorType>
bool ReversedWrapper<IteratorType>::operator==(const ReversedWrapper& other) const {
	return iterator_ == other;
}

template<typename IteratorType>
bool ReversedWrapper<IteratorType>::operator!=(const ReversedWrapper& other) const {
	return iterator_ != other;
}

template<typename IteratorType>
ReversedWrapper<IteratorType> ReversedWrapper<IteratorType>::operator+(const ptrdiff_t n) const {
	return iterator_ + n;
}

template<typename IteratorType>
ReversedWrapper<IteratorType> ReversedWrapper<IteratorType>::operator-(const ptrdiff_t n) const {
	return iterator_ - n;
}

template<typename IteratorType>
ptrdiff_t ReversedWrapper<IteratorType>::operator-(const ReversedWrapper& other) const {
	return iterator_ - other;
}

template<typename IteratorType>
bool ReversedWrapper<IteratorType>::operator>(const ReversedWrapper& other) const {
	return iterator_ < other;
}

template<typename IteratorType>
bool ReversedWrapper<IteratorType>::operator<(const ReversedWrapper& other) const {
	return iterator_ > other;
}

template<typename IteratorType>
bool ReversedWrapper<IteratorType>::operator>=(const ReversedWrapper& other) const {
	return iterator_ <= other;
}

template<typename IteratorType>
bool ReversedWrapper<IteratorType>::operator<=(const ReversedWrapper& other) const {
	return iterator_ >= other;
}

template class BaseIterator<MyString::iterator, char&, MyString*>;
template class BaseIterator<MyString::const_iterator, const char&, const MyString*>;

template class ReversedWrapper<MyString::const_iterator>;
template class ReversedWrapper<MyString::iterator>;*/