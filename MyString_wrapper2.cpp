#include <boost/python.hpp>
#include <boost/python/return_value_policy.hpp>
#include "MyString.h"

using namespace boost::python;

const char* get_c_str(const char* str) { return str; }
const char* get_c_str(const std::string& str) { return str.c_str(); }
const char* get_c_str(const MyString& str) { return str.c_str(); }

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

std::string get_c_str_wrapper(const MyString& self) {
    const char* ptr = self.c_str();
    return ptr ? std::string(ptr) : std::string();
}

MyString& assign_char(MyString& self, const char* s) { return self = s; }
MyString& assign_string(MyString& self, const std::string& s) { return self = s; }
MyString& assign_mys(MyString& self, const MyString& other) { return self = other; }

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

void erase(MyString& self, int index, int count) {
    self.erase((index < 0 ? index + static_cast<int>(self.size()) : index), count);
}

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

MyString substr(MyString& self, int index) {
    return self.substr(index < 0 ? index + static_cast<int>(self.size()) : index);
}
MyString substr(MyString& self, int index, const int count) {
    return self.substr((index < 0 ? index + static_cast<int>(self.size()) : index), count);
}

MyString add_char_ptr(MyString& self, const char* str) {
    return self + str;
}
MyString add_std_string(MyString& self, const std::string& str) {
    return self + str;
}
MyString add_mystring(MyString& self, const MyString& other) {
    return self + other;
}

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

void set_char_at(MyString& self, int index, char ch) {
    int size = static_cast<int>(self.size());
    int idx = index < 0 ? index + size : index;
    if (idx < 0 || idx >= size) {
        PyErr_SetString(PyExc_IndexError, "Index out of range");
        boost::python::throw_error_already_set();
    }
    self[idx] = ch;
}

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

size_t get_size(MyString& self) {
    return self.size();
}



BOOST_PYTHON_MODULE(mystring) {
    class_<MyString>("MyString")
        .def(init<>()) //1
        .def(init<const char*>()) //2
        .def(init<const std::string&>()) //3
        .def(init<const MyString&>()) //4
        .def(init<const char*, const int>()) //5
        .def(init<const std::string&, const int>()) //6
        .def(init<const MyString&, const int>()) //7
        .def(init<const int, const char>()) //8
        .def("clear", &MyString::clear) //10
        .def("shrink_to_fit", &MyString::shrink_to_fit) //11 

        .def("assign", assign_char, return_self<>()) //12
        .def("assign", assign_string, return_self<>()) //12
        .def("assign", assign_mys, return_self<>()) //12

        .def("c_str", get_c_str_wrapper) //14
        .def("size", &MyString::size) // 15
        .def("capacity", &MyString::capacity) //16
        .def("empty", &MyString::empty) // 17

        .def("insert", insert_count_char) //18
        .def("insert", insert_char_ptr) //19
        .def("insert", insert_std_string) //20
        .def("insert", insert_mystring) //21
        .def("insert", insert_char_ptr_count) //22
        .def("insert", insert_std_string_count) //23
        .def("insert", insert_mystring_count) //24
        .def("insert", insert_char_ptr_count_from_index) //25
        .def("insert", insert_std_string_count_from_index) //26
        .def("insert", insert_mystring_count_from_index) //27

        .def("append", append_count_char) //28
        .def("append", append_char_ptr) //29
        .def("append", append_std_string) //30
        .def("append", append_mystring) //31
        .def("append", append_char_ptr_count) //32
        .def("append", append_std_string_count) //33
        .def("append", append_mystring_count) //34
        .def("append", append_char_ptr_count_from_index) //35
        .def("append", append_std_string_count_from_index) //36
        .def("append", append_mystring_count_from_index) //37

        .def("erase", erase) //38

        .def("replace", replace_char_ptr) //39
        .def("replace", replace_std_string) //40
        .def("replace", replace_mystring) //41
        .def("replace", replace_char_ptr_count) //42
        .def("replace", replace_std_string_count) //43
        .def("replace", replace_mystring_count) //44
        .def("replace", replace_char_ptr_count_from_index) //45
        .def("replace", replace_std_string_count_from_index) //46
        .def("replace", replace_mystring_count_from_index) //47

        .def("substr", static_cast<MyString(MyString::*)(int)>(&MyString::substr)) //48
        .def("substr", static_cast<MyString(MyString::*)(int, int)>(&MyString::substr)) //49

        .def("__add__", add_char_ptr) //50
        .def("__add__", add_std_string) //51
        .def("__add__", add_mystring) //52

        .def("__iadd__", iadd_char_ptr, return_self<>()) //53
        .def("__iadd__", iadd_std_string, return_self<>()) //54
        .def("__iadd__", iadd_mystring, return_self<>()) //55

        .def("__getitem__", static_cast<char (MyString::*)(int) const>(&MyString::operator[])) //56
        .def("__setitem__", set_char_at) //56

        .def("__len__", get_size) 

        .def("compare", compare_as_int)
        .def("__gt__", &MyString::operator>)
        .def("__lt__", &MyString::operator<)
        .def("__ge__", &MyString::operator>=)
        .def("__le__", &MyString::operator<=)
        .def("__ne__", &MyString::operator!=)
        .def("__eq__", &MyString::operator==)

        .def("find", static_cast<int (MyString::*)(const char*)>(&MyString::find))
        .def("find", static_cast<int (MyString::*)(const std::string&)>(&MyString::find))
        .def("find", static_cast<int (MyString::*)(const MyString&)>(&MyString::find))
        .def("find", static_cast<int (MyString::*)(const char*, int)>(&MyString::find))
        .def("find", static_cast<int (MyString::*)(const std::string&, int)>(&MyString::find))
        .def("find", static_cast<int (MyString::*)(const MyString&, int)>(&MyString::find))
        ;
}

/*
        .def("assign",
    [](MyString& self, const char* str) {
        self = str;
    }) //12
.def("assign",
    [](MyString& self, const std::string& str) {
        self = str.c_str();
    }) //12
.def("assign",
    [](MyString& self, MyString& other) {
        self = other.c_str();
    }) //12


.def("assign",
    [](MyString& self, const char ch) {
        self = ch;
    }) //13

.def("c_str", &MyString::c_str) //14

.def("size", &MyString::size) // 15

.def("capacity", &MyString::capacity) //16

.def("empty", &MyString::empty) // 17

.def("insert",
    [](MyString& self, int index, const char* str) {
        insert_wrapper(self, index, str, 0, strlen(str));
    }) //19
.def("insert",
    [](MyString& self, int index, const std::string& str) {
        insert_wrapper(self, index, str, 0, strlen(str.c_str()));
    }) //20
.def("insert",
    [](MyString& self, int index, const MyString& other) {
        insert_wrapper(self, index, other, 0, other.size());
    }) //21

.def("insert",
    [](MyString& self, int index, const char* str, const int count) {
        insert_wrapper(self, index, str, 0, count);
    }) //22
.def("insert",
    [](MyString& self, int index, std::string& str, const int count) {
        insert_wrapper(self, index, str, 0, count);
    }) //23
.def("insert",
    [](MyString& self, int index, MyString& other, const int count) {
        insert_wrapper(self, index, other, 0, count);
    }) //24

.def("insert",
    [](MyString& self, int index, const char* str, int s_index, const int count) {
        insert_wrapper(self, index, str, s_index, count);
    }) //25
.def("insert",
    [](MyString& self, int index, std::string& str, int s_index, const int count) {
        insert_wrapper(self, index, str, s_index, count);
    }) //26
.def("insert",
    [](MyString& self, int index, MyString& other, int s_index, const int count) {
        insert_wrapper(self, index, other, s_index, count);
    }) //27

.def("append",
    [](MyString& self, const int count, const char ch) {
        self.append(count, ch);
    }) //28

.def("append",
    [](MyString& self, const char* str) {
        self.append(str);
    }) //29
.def("append",
    [](MyString& self, const std::string& str) {
        self.append(str);
    }) //30
.def("append",
    [](MyString& self, MyString& other) {
        self.append(other);
    }) //31

.def("append",
    [](MyString& self, const char* str, const int count) {
        self.append(str, count);
    }) //32
.def("append",
    [](MyString& self, const std::string& str, const int count) {
        self.append(str, count);
    }) //33
.def("append",
    [](MyString& self, MyString& other, const int count) {
        self.append(other, count);
    }) //34

.def("append",
    [](MyString& self, const char* str, int s_index, const int count) {
        self.append(str, (s_index < 0 ? s_index + static_cast<int>(strlen(str)) : s_index), count);
    }) //35
.def("append",
    [](MyString& self, const std::string& str, int s_index, const int count) {
        self.append(str, (s_index < 0 ? s_index + static_cast<int>(strlen(str.c_str())) : s_index), count);
    }) //36
.def("append",
    [](MyString& self, MyString& other, int s_index, const int count) {
        self.append(other, (s_index < 0 ? s_index + static_cast<int>(other.size()) : s_index), count);
    }) //37

.def("erase",
    [](MyString& self, int index, const int count) {
        self.erase((index < 0 ? index + static_cast<int>(self.size()) : index), count);
    }) //38

.def("replace",
    [](MyString& self, int index, const int count, const char* str) {
        self.replace((index < 0 ? index + static_cast<int>(strlen(str)) : index), count, str);
    }) //39
.def("replace",
    [](MyString& self, int index, const int count, const std::string& str) {
        self.replace((index < 0 ? index + static_cast<int>(strlen(str.c_str())) : index), count, str);
    }) //40
.def("replace",
    [](MyString& self, int index, const int count, MyString& other) {
        self.replace((index < 0 ? index + static_cast<int>(other.size()) : index), count, other);
    }) //41

.def("replace",
    [](MyString& self, int index, const int count, const char* str, const int s_count) {
        self.replace((index < 0 ? index + static_cast<int>(strlen(str)) : index), count, str, s_count);
    }) //42
.def("replace",
    [](MyString& self, int index, const int count, const std::string& str, const int s_count) {
        self.replace((index < 0 ? index + static_cast<int>(strlen(str.c_str())) : index), count, str, s_count);
    }) //43
.def("replace",
    [](MyString& self, int index, const int count, MyString& other, const int s_count) {
        self.replace((index < 0 ? index + static_cast<int>(other.size()) : index), count, other, s_count);
    }) //44

.def("replace",
    [](MyString& self, int index, const int count, const char* str, int s_index, const int s_count) {
        self.replace((index < 0 ? index + static_cast<int>(strlen(str)) : index), count, str,
        (s_index < 0 ? s_index + static_cast<int>(strlen(str)) : s_index), s_count);
    }) //45
.def("replace",
    [](MyString& self, int index, const int count, const std::string& str, int s_index, const int s_count) {
        self.replace((index < 0 ? index + static_cast<int>(strlen(str.c_str())) : index), count, str,
        (s_index < 0 ? s_index + static_cast<int>(strlen(str.c_str())) : s_index), s_count);
    }) //46
.def("replace",
    [](MyString& self, int index, const int count, MyString& other, int s_index, const int s_count) {
        self.replace((index < 0 ? index + static_cast<int>(other.size()) : index), count, other,
        (s_index < 0 ? s_index + static_cast<int>(other.size()) : s_index), s_count);
    }) //47

.def("substr",
    [](MyString& self, int index) {
        self.substr((index < 0 ? index + static_cast<int>(self.size()) : index));
    }) //48
 .def("substr",
    [](MyString& self, int index, const int count) {
        self.substr((index < 0 ? index + static_cast<int>(self.size()) : index), count);
    }) //49

.def("__add__",
    [](MyString& self, const char* str) {
        return self + str;
    }) //50
.def("__add__",
    [](MyString& self, const std::string& str) {
        return self + str;
    }) //51
.def("__add__",
    [](MyString& self, MyString& other) {
        return self + other;
    }) //52

.def("__iadd__",
    [](MyString& self, const char* str) {
        self += str;
    }) //53
.def("__iadd__",
    [](MyString& self, const std::string& str) {
        self += str;
    }) //54
.def("__iadd__",
    [](MyString& self, MyString& other) {
        self += other;
    }) //55

.def("__getitem__",
    [](MyString& self, int index) -> char{
        return self.operator[](index < 0 ? index + static_cast<int>(self.size()): index);
    }) //56
.def("__getitem__",
    [](MyString& self, int index, const char ch) {
        self[index < 0 ? index + static_cast<int>(self.size()) : index] = ch;
    }) //56

.def("compare",
    [](MyString& self, const MyString& other) {
        return self.compare(other);
    })*/