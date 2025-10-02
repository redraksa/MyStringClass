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
	static void case_25();
	static void case_26();
	static void case_27();
	static void case_28();
	static void case_29();
	static void case_30();
	static void case_31();
	static void case_32();
	static void case_33();
	static void case_34();
	static void case_35();
	static void case_36();
	static void case_37();
	static void case_38();
	static void case_39();
	static void case_40();
	static void case_41();
	static void case_42();
	static void case_43();
	static void case_44();
	static void case_45();
	static void case_46();
	static void case_47();
	static void case_48();
	static void case_49();
	static void case_50();
	static void case_51();
	static void case_52();
	static void case_53();
	static void case_54();
	static void case_55();
	static void case_56();
	static void case_57();
	static void case_58_59_60();

	static void case_61();
	static void case_62();
	static void case_63();
	static void case_64();
	static void case_65();
	static void case_66();
private:
	static void pstr(const MyString& my_str) {
		std::cout << "\"" << my_str << "\" (" << my_str.size() << ", " << my_str.capacity() << ")" << "\n";
	}
};

inline std::ostream& operator<<(std::ostream& os, const LexicographicComparisonStringsResult result) {
	os << static_cast<int>(result);
	return os;
}

#endif // !_MYSTRINGEXAMPLES_