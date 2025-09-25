#ifndef _MYSTRINGEXAMPLES_
#define _MYSTRINGEXAMPLES_

#include <iostream>
#include "MyString.h"
#include "MyStringPrinter.h"

class MyStringExamples {
public:
	static void case_1();
	static void case_2();
	static void case_3();
	static void case_4();
	static void case_5();
	static void case_6();
	static void case_7();
	static void case_8();
	static void case_10();
	static void case_11();
	static void case_12();
	static void case_13();
	static void case_14();
	static void case_15();
	static void case_16();
	static void case_17();
	static void case_18();
	static void case_19();
	static void case_20();
	static void case_21();
	static void case_22();
	static void case_23();
	static void case_24();
	static void case_38();
	static void case_48();
	static void case_49();
	static void case_50();
	static void case_51();
	static void case_52();
private:
	static void pstr(const MyString& my_str) {
		std::cout << "\"" << my_str << "\" (" << my_str.size() << ", " << my_str.capacity() << ")" << "\n";
	}
};

#endif // !_MYSTRINGEXAMPLES_