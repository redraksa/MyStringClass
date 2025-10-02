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

void MyStringExamples::case_25() {
	std::cout << "25 case:\n";

	MyString str("aaaaa");
	str.insert(1, "abcde", 1, 2);
	pstr(str);
}

void MyStringExamples::case_26() {
	std::cout << "26 case:\n";

	MyString str("aaaaa");
	str.insert(1, std::string("abcde"), 1, 2);
	pstr(str);
}

void MyStringExamples::case_27() {
	std::cout << "27 case:\n";

	MyString str("aaaaa"), str1("abcde");
	str.insert(1, str1, 1, 2);
	pstr(str);
}

void MyStringExamples::case_28() {
	std::cout << "28 case:\n";

	MyString str;
	str.append(3, '!');
	pstr(str);
	str.append(3, '@');
	pstr(str);
}

void MyStringExamples::case_29() {
	std::cout << "29 case:\n";

	MyString str;
	str.append("Hello ");
	pstr(str);
	str.append("world");
	pstr(str);
}

void MyStringExamples::case_30() {
	std::cout << "30 case:\n";

	MyString str;
	str.append(std::string("Hello "));
	pstr(str);
	str.append(std::string("world"));
	pstr(str);
}

void MyStringExamples::case_31() {
	std::cout << "31 case:\n";

	MyString str, str1("Hello "), str2("world");
	str.append(str1);
	pstr(str);
	str.append(str2);
	pstr(str);
}

void MyStringExamples::case_32() {
	std::cout << "32 case:\n";

	MyString str;
	str.append("Hello world", 6);
	pstr(str);
	str.append("world");
	pstr(str);
}

void MyStringExamples::case_33() {
	std::cout << "33 case:\n";

	MyString str;
	str.append(std::string("Hello world") ,6);
	pstr(str);
	str.append(std::string("world"));
	pstr(str);
}

void MyStringExamples::case_34() {
	std::cout << "34 case:\n";

	MyString str, str1("Hello world"), str2("world");
	str.append(str1, 6);
	pstr(str);
	str.append(str2);
	pstr(str);
}

void MyStringExamples::case_35() {
	std::cout << "35 case:\n";

	MyString str;
	str.append("Hello world", 0, 6);
	pstr(str);
	str.append("Hello world", 6, 5);
	pstr(str);
}

void MyStringExamples::case_36() {
	std::cout << "36 case:\n";

	MyString str;
	str.append(std::string("Hello world"), 0, 6);
	pstr(str);
	str.append(std::string("Hello world"), 6, 5);
	pstr(str);
}

void MyStringExamples::case_37() {
	std::cout << "37 case:\n";

	MyString str, str1("Hello world");
	str.append(str1, 0, 6);
	pstr(str);
	str.append(str1, 6, 5);
	pstr(str);
}

void MyStringExamples::case_38() {
	std::cout << "38 case:\n";

	MyString str("Hello world!");
	str.erase(5, 6);
	pstr(str);
}

void MyStringExamples::case_39() {
	std::cout << "39 case:\n";

	MyString str("hello amazing world");
	str.replace(6, 7, "wonderful");
	pstr(str);
}

void MyStringExamples::case_40() {
	std::cout << "40 case:\n";

	MyString str("hello amazing world");
	str.replace(6, 7, std::string("wonderful"));
	pstr(str);
}

void MyStringExamples::case_41() {
	std::cout << "41 case:\n";

	MyString str("hello amazing world"), str1("wonderful");
	str.replace(6, 7, str1);
	pstr(str);
}

void MyStringExamples::case_42() {
	std::cout << "42 case:\n";

	MyString str("hello amazing world");
	str.replace(6, 7, "wonderful", 6);
	pstr(str);
}

void MyStringExamples::case_43() {
	std::cout << "43 case:\n";

	MyString str("hello amazing world");
	str.replace(6, 7, std::string("wonderful"), 6);
	pstr(str);
}

void MyStringExamples::case_44() {
	std::cout << "44 case:\n";

	MyString str("hello amazing world"), str1("wonderful");
	str.replace(6, 7, str1, 6);
	pstr(str);
}

void MyStringExamples::case_45() {
	std::cout << "45 case:\n";

	MyString str("hello amazing world");
	str.replace(6, 7, "wonderful", 1, 2);
	pstr(str);
}

void MyStringExamples::case_46() {
	std::cout << "46 case:\n";

	MyString str("hello amazing world");
	str.replace(6, 7, std::string("wonderful"), 1, 2);
	pstr(str);
}

void MyStringExamples::case_47() {
	std::cout << "47 case:\n";

	MyString str("hello amazing world"), str1("wonderful");
	str.replace(6, 7, str1, 1, 2);
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

void MyStringExamples::case_53() {
	std::cout << "53 case:\n";

	MyString str("hel"), toadd("lo");
	str += toadd.c_str();
	pstr(str);
	pstr(toadd);
}

void MyStringExamples::case_54() {
	std::cout << "54 case:\n";

	MyString str("hel"), toadd("lo");
	str += std::string(toadd.c_str());
	pstr(str);
	pstr(toadd);
}

void MyStringExamples::case_55() {
	std::cout << "55 case:\n";

	MyString str("hel"), toadd("lo");
	str += toadd.c_str();
	pstr(str);
	pstr(toadd);
}

void MyStringExamples::case_56() {
	std::cout << "56 case:\n";

	MyString str("hello");
	std::cout << str[2] << std::endl;
	str[2] = 'L';
	pstr(str);
}

void MyStringExamples::case_57() {
	std::cout << "57 case:\n";

	MyString a("abcd"), b("abce");
	std::cout << a.compare(b) << b.compare(a) << std::endl;
}

void MyStringExamples::case_58_59_60() {
	std::cout << "58, 59, 60 case:\n";

	MyString a("abcd"), b("abce");
	std::cout << (a == b) << (a != b) << (a > b) <<
		(a >= b) << (a < b) << (a <= b) << std::endl;
}

void MyStringExamples::case_61() {
	std::cout << "61 case:\n";

	MyString str = "hello amazing world amazing";
	int i = str.find("amazing");
	std::cout << i << std::endl;
}

void MyStringExamples::case_62() {
	std::cout << "62 case:\n";

	MyString str = "hello amazing world amazing";
	int i = str.find(std::string("amazing"));
	std::cout << i << std::endl;
}

void MyStringExamples::case_63() {
	std::cout << "63 case:\n";

	MyString str = "hello amazing world amazing", str1("amazing");
	int i = str.find(str1);
	std::cout << i << std::endl;
}

void MyStringExamples::case_64() {
	std::cout << "64 case:\n";

	MyString str = "hello amazing world amazing";
	int i = str.find("amazing", 7);
	std::cout << i << std::endl;
}

void MyStringExamples::case_65() {
	std::cout << "65 case:\n";

	MyString str = "hello amazing world amazing";
	int i = str.find(std::string("amazing"), 7);
	std::cout << i << std::endl;
}

void MyStringExamples::case_66() {
	std::cout << "66 case:\n";

	MyString str = "hello amazing world amazing", str1("amazing");
	int i = str.find(str1, 7);
	std::cout << i << std::endl;
}