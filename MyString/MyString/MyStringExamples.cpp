#include "MyStringExamples.h"

void MyStringExamples::case_1() {
	std::cout << "1 case:\n";

	MyString str;
	pstr(str);
}

void MyStringExamples::case_2() {
	std::cout << "2 case:\n";

	MyString str("Hello world!");
	pstr(str);
}

void MyStringExamples::case_3() {
	std::cout << "3 case:\n";

	std::string s_str = "hello";
	MyString str(s_str);
	pstr(str);
}

void MyStringExamples::case_4() {
	std::cout << "4 case:\n";

	MyString s_str("hello");
	MyString str(s_str);
	pstr(str);
}

void MyStringExamples::case_5() {
	std::cout << "5 case:\n";

	MyString str("hello", 4);
	pstr(str);
}

void MyStringExamples::case_6() {
	std::cout << "6 case:\n";

	MyString str(std::string("hello"), 4);
	pstr(str);
}

void MyStringExamples::case_7() {
	std::cout << "7 case:\n";

	MyString str(MyString("hello"), 4);
	pstr(str);
}

void MyStringExamples::case_8() {
	std::cout << "8 case:\n";

	MyString str(5, '!');
	pstr(str);
}

void MyStringExamples::case_10() {
	std::cout << "10 case:\n";

	MyString str("Hello world!");
	pstr(str);
	str.clear();
	pstr(str);
}

void MyStringExamples::case_11() {
	std::cout << "11 case:\n";

	MyString str("Hello world!");
	pstr(str);
	str.erase(5, 6);
	pstr(str);
	str.shrink_to_fit();
	pstr(str);
}

void MyStringExamples::case_12() {
	std::cout << "12 case:\n";

	MyString str;
	str = "hello";
	pstr(str);
}

void MyStringExamples::case_13() {
	std::cout << "13 case:\n";

	MyString str;
	str = '!';
	pstr(str);
}

void MyStringExamples::case_14() {
	std::cout << "14 case:\n";

	MyString str("str");
	std::cout << str << std::endl;
}

void MyStringExamples::case_15() {
	std::cout << "15 case:\n";

	MyString str("Hello world!");
	std::cout << str.size() << std::endl;
}

void MyStringExamples::case_16() {
	std::cout << "16 case:\n";

	MyString str("Hello world!");
	std::cout << str.capacity() << std::endl;
}

void MyStringExamples::case_17() {
	std::cout << "17 case:\n";

	MyString str("Hello world!");
	std::cout << str.empty() << std::endl;
	MyString empty;
	std::cout << empty.empty() << std::endl;
}

void MyStringExamples::case_18() {
	std::cout << "18 case:\n";

	MyString str("aaaaa");
	str.insert(0, 1, '!');
	pstr(str);
	str.insert(3, 2, '@');
	pstr(str);
}

void MyStringExamples::case_19() {
	std::cout << "19 case:\n";

	MyString str("aaaaa");
	str.insert(1, "@@@@@");
	pstr(str);
}

void MyStringExamples::case_20() {
	std::cout << "20 case:\n";

	MyString str("aaaaa");
	str.insert(1, std::string("@@@@@"));
	pstr(str);
}

void MyStringExamples::case_21() {
	std::cout << "21 case:\n";

	MyString str("aaaaa"), str1("@@@@@");
	str.insert(1, str1);
	pstr(str);
}

void MyStringExamples::case_22() {
	std::cout << "22 case:\n";

	MyString str("aaaaa");
	str.insert(1, "@@@@@", 2);
	pstr(str);
}

void MyStringExamples::case_23() {
	std::cout << "23 case:\n";

	MyString str("aaaaa");
	str.insert(1, std::string("@@@@@"), 2);
	pstr(str);
}

void MyStringExamples::case_24() {
	std::cout << "24 case:\n";

	MyString str("aaaaa"), str1("@@@@@");
	str.insert(1, str1, 2);
	pstr(str);
}

void MyStringExamples::case_38() {
	std::cout << "38 case:\n";

	MyString str("Hello world!");
	str.erase(5, 6);
	pstr(str);
}

void MyStringExamples::case_48() {
	std::cout << "48 case:\n";

	MyString str("hello amazing world"), substr;
	substr = str.substr(6);
	pstr(substr);

}

void MyStringExamples::case_49() {
	std::cout << "49 case:\n";

	MyString str("hello amazing world"), substr;
	substr = str.substr(6, 7);
	pstr(substr);

}

void MyStringExamples::case_50() {
	std::cout << "50 case:\n";

	MyString left("hel");
	const char* right = "lo";
	MyString r = left + right;
	pstr(left);
	pstr(right);
	pstr(r);

}

void MyStringExamples::case_51() {
	std::cout << "51 case:\n";

	MyString left("hel"), r;
	const std::string right = "lo";
	r = left + right;
	pstr(left);
	pstr(right);
	pstr(r);
}

void MyStringExamples::case_52() {
	std::cout << "52 case:\n";

	MyString left("hel"), right("lo"), r;
	r = left + right;
	pstr(left);
	pstr(right);
	pstr(r);
}