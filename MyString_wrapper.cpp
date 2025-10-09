#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "MyString.h"

namespace py = pybind11;

template<typename StringType>
void insert_wrapper(MyString& self, int index, const StringType& str, int s_index, int count) {
    int size = static_cast<int>(self.size());
    int python_index = index;

    if (index < 0) {
        python_index = index + size;
    }

    int size_s = static_cast<int>(strlen(get_c_str(str)));
    int python_index_s = s_index;

    if (s_index < 0) {
        python_index_s = s_index + size_s;
    }

    if (python_index_s == 0) {
        if (count == size) {
            self.insert(python_index, get_c_str(str));
        }
        else {
            self.insert(python_index, get_c_str(str), count);
        }
    }
    else {
        self.insert(python_index, get_c_str(str), python_index_s, count);
    }
}

// === Функции-обёртки для assign ===
MyString& assign_char(MyString& self, const char* s) { return self = s; }
MyString& assign_string(MyString& self, const std::string& s) { return self = s; }
MyString& assign_mys(MyString& self, const MyString& other) { return self = other; }

// === Функции-обёртки для insert ===
void insert_count_char(MyString& self, int index, int count, char ch) {
    self.insert(index, count, ch);
}

void insert_char_ptr(MyString& self, int index, const char* str) {
    insert_wrapper(self, index, str, 0, static_cast<int>(strlen(str)));
}
void insert_std_string(MyString& self, int index, const std::string& str) {
    insert_wrapper(self, index, str, 0, static_cast<int>(str.length()));
}
void insert_mystring(MyString& self, int index, const MyString& other) {
    insert_wrapper(self, index, other, 0, static_cast<int>(other.size()));
}

void insert_char_ptr_count(MyString& self, int index, const char* str, const int count) {
    insert_wrapper(self, index, str, 0, count);
}
void insert_std_string_count(MyString& self, int index, const std::string& str, const int count) {
    insert_wrapper(self, index, str, 0, count);
}
void insert_mystring_count(MyString& self, int index, const MyString& other, const int count) {
    insert_wrapper(self, index, other, 0, count);
}

void insert_char_ptr_count_from_index(MyString& self, int index, const char* str, int s_index, const int count) {
    insert_wrapper(self, index, str, s_index, count);
}
void insert_std_string_count_from_index(MyString& self, int index, const std::string& str, int s_index, const int count) {
    insert_wrapper(self, index, str, s_index, count);
}
void insert_mystring_count_from_index(MyString& self, int index, const MyString& other, int s_index, const int count) {
    insert_wrapper(self, index, other, s_index, count);
}

// === Функции-обёртки для append ===
void append_count_char(MyString& self, int count, char ch) {
    self.append(count, ch);
}

void append_char_ptr(MyString& self, const char* str) {
    self.append(str);
}
void append_std_string(MyString& self, const std::string& str) {
    self.append(str);
}
void append_mystring(MyString& self, MyString& other) {
    self.append(other);
}

void append_char_ptr_count(MyString& self, const char* str, const int count) {
    self.append(str, count);
}
void append_std_string_count(MyString& self, const std::string& str, const int count) {
    self.append(str, count);
}
void append_mystring_count(MyString& self, MyString& other, const int count) {
    self.append(other, count);
}

void append_char_ptr_count_from_index(MyString& self, const char* str, int s_index, const int count) {
    self.append(str, (s_index < 0 ? s_index + static_cast<int>(strlen(str)) : s_index), count);
}
void append_std_string_count_from_index(MyString& self, const std::string& str, int s_index, const int count) {
    self.append(str, (s_index < 0 ? s_index + static_cast<int>(strlen(str.c_str())) : s_index), count);
}
void append_mystring_count_from_index(MyString& self, MyString& other, int s_index, const int count) {
    self.append(other, (s_index < 0 ? s_index + static_cast<int>(other.size()) : s_index), count);
}

// === Функции-обёртки для erase ===
void erase(MyString& self, int index, int count) {
    self.erase((index < 0 ? index + static_cast<int>(self.size()) : index), count);
}

// === Функции-обёртки для replace ===
void replace_char_ptr(MyString& self, int index, const int count, const char* str) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, str);
}
void replace_std_string(MyString& self, int index, const int count, std::string& str) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, str);
}
void replace_mystring(MyString& self, int index, const int count, MyString& other) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, other);
}

void replace_char_ptr_count(MyString& self, int index, const int count, const char* str, const int s_count) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, str, s_count);
}
void replace_std_string_count(MyString& self, int index, const int count, std::string& str, const int s_count) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, str, s_count);
}
void replace_mystring_count(MyString& self, int index, const int count, MyString& other, const int s_count) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, other, s_count);
}

void replace_char_ptr_count_from_index(MyString& self, int index, const int count, const char* str, int s_index, const int s_count) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, str,
        (s_index < 0 ? s_index + static_cast<int>(strlen(str)) : s_index), s_count);
}
void replace_std_string_count_from_index(MyString& self, int index, const int count, std::string& str, int s_index, const int s_count) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, str,
        (s_index < 0 ? s_index + static_cast<int>(strlen(str.c_str())) : s_index), s_count);
}
void replace_mystring_count_from_index(MyString& self, int index, const int count, MyString& other, int s_index, const int s_count) {
    self.replace((index < 0 ? index + static_cast<int>(self.size()) : index), count, other,
        (s_index < 0 ? s_index + static_cast<int>(other.size()) : s_index), s_count);
}

// === Функции-обёртки для substr ===
MyString substr(MyString& self, int index) {
    return self.substr(index < 0 ? index + static_cast<int>(self.size()) : index);
}
MyString substr(MyString& self, int index, const int count) {
    return self.substr((index < 0 ? index + static_cast<int>(self.size()) : index), count);
}

// === Функции-обёртки для operator+ ===
MyString add_char_ptr(MyString& self, const char* str) {
    return self + str;
}
MyString add_std_string(MyString& self, const std::string& str) {
    return self + str;
}
MyString add_mystring(MyString& self, const MyString& other) {
    return self + other;
}

// === Функции-обёртки для operator+= ===
MyString& iadd_char_ptr(MyString& self, const char* str) {
    self += str;
    return self;
}
MyString& iadd_std_string(MyString& self, const std::string& str) {
    self += str;
    return self;
}
MyString& iadd_mystring(MyString& self, const MyString& other) {
    self += other;
    return self;
}

// === Функции-обёртки для compare ===
int compare_as_int(MyString& self, const MyString& other) {
    auto result = self.compare(other);
    if (result == LexicographicComparisonStringsResult::cIsSmaller) {
        return -1;
    }
    else if (result == LexicographicComparisonStringsResult::cIsGreater) {
        return 1;
    }
    else {
        return 0;
    }
}

// === Функции-обёртки для find ===
int find_char_ptr(MyString& self, const char* str) { return self.find(str); }
int find_std_string(MyString& self, const std::string& str) { return self.find(str); }
int find_mystring(MyString& self, const MyString& other) { return self.find(other); }
int find_char_ptr_index(MyString& self, const char* str, int index) { return self.find(str, index); }
int find_std_string_index(MyString& self, const std::string& str, int index) { return self.find(str, index); }
int find_mystring_index(MyString& self, const MyString& other, int index) { return self.find(other, index); }

// === Функция-обёртка для __len__ ===
size_t get_size(MyString& self) { return self.size(); }

// === Вспомогательная функция ===
const char* get_c_str(const char* str) { return str; }
const char* get_c_str(const std::string& str) { return str.c_str(); }
const char* get_c_str(const MyString& str) { return str.c_str(); }

PYBIND11_MODULE(mystring, m) {
    m.doc() = "MyString wrapper";

    py::class_<MyString>(m, "MyString")
        .def(py::init<>())
        .def(py::init<const char*>())
        .def(py::init<const std::string&>())
        .def(py::init<const MyString&>())
        .def(py::init<const char*, const int>())
        .def(py::init<const std::string&, const int>())
        .def(py::init<const MyString&, const int>())
        .def(py::init<const int, const char*>())

        .def("c_str", [](const MyString& self) { return self.c_str(); })
        .def("size", &MyString::size)
        .def("capacity", &MyString::capacity)
        .def("empty", &MyString::empty)
        .def("clear", &MyString::clear)
        .def("shrink_to_fit", &MyString::shrink_to_fit)

        .def("assign", assign_char)
        .def("assign", assign_string)
        .def("assign", assign_mys)

        .def("insert", insert_count_char)
        .def("insert", insert_char_ptr)
        .def("insert", insert_std_string)
        .def("insert", insert_mystring)
        .def("insert", insert_char_ptr_count)
        .def("insert", insert_std_string_count)
        .def("insert", insert_mystring_count)
        .def("insert", insert_char_ptr_count_from_index)
        .def("insert", insert_std_string_count_from_index)
        .def("insert", insert_mystring_count_from_index)

        .def("append", append_count_char)
        .def("append", append_char_ptr)
        .def("append", append_std_string)
        .def("append", append_mystring)
        .def("append", append_char_ptr_count)
        .def("append", append_std_string_count)
        .def("append", append_mystring_count)
        .def("append", append_char_ptr_count_from_index)
        .def("append", append_std_string_count_from_index)
        .def("append", append_mystring_count_from_index)

        .def("erase", erase)

        .def("replace", replace_char_ptr)
        .def("replace", replace_std_string)
        .def("replace", replace_mystring)
        .def("replace", replace_char_ptr_count)
        .def("replace", replace_std_string_count)
        .def("replace", replace_mystring_count)
        .def("replace", replace_char_ptr_count_from_index)
        .def("replace", replace_std_string_count_from_index)
        .def("replace", replace_mystring_count_from_index)

        .def("substr", static_cast<MyString(MyString::*)(int)>(&MyString::substr))
        .def("substr", static_cast<MyString(MyString::*)(int, int)>(&MyString::substr))

        .def("__add__", add_char_ptr)
        .def("__add__", add_std_string)
        .def("__add__", add_mystring)

        .def("__iadd__", iadd_char_ptr)
        .def("__iadd__", iadd_std_string)
        .def("__iadd__", iadd_mystring)

        .def("__getitem__", [](const MyString& self, int index) {
        int size = static_cast<int>(self.size());
        int idx = index < 0 ? index + size : index;
        if (idx < 0 || idx >= size) {
            throw py::index_error("Index out of range");
        }
        return self[idx];
            })
        .def("__setitem__", [](MyString& self, int index, char ch) {
                int size = static_cast<int>(self.size());
                int idx = index < 0 ? index + size : index;
                if (idx < 0 || idx >= size) {
                    throw py::index_error("Index out of range");
                }
                self[idx] = ch;
            })

                .def("__len__", get_size)

                .def("compare", compare_as_int)
                .def("__gt__", &MyString::operator>)
                .def("__lt__", &MyString::operator<)
                .def("__ge__", &MyString::operator>=)
                .def("__le__", &MyString::operator<=)
                .def("__ne__", &MyString::operator!=)
                .def("__eq__", &MyString::operator==)

                .def("find", find_char_ptr)
                .def("find", find_std_string)
                .def("find", find_mystring)
                .def("find", find_char_ptr_index)
                .def("find", find_std_string_index)
                .def("find", find_mystring_index)
                ;
}