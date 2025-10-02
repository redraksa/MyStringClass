#ifndef _MYSTRINGPRINTER_
#define _MYSTRINGPRINTER_

#include <iostream>
#include "MyString.h"

class MyStringPrinter {
public:
	void pstr(const MyString& my_str) {
		std::cout << my_str.c_str();
	}
};
#endif // !_MYSTRINGPRINTER_
