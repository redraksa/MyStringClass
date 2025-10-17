#ifndef _AHOCORASICK_H_
#define _AHOCORASICK_H_
#include "MyString.h"
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>


struct Node {
	bool terminal = false;
	std::unordered_map<char, std::unique_ptr<Node>> childrens;
	Node* suff_ref = nullptr;
	const MyString* string_ref = nullptr;
	Node* output_ref = nullptr;
	size_t id;
};

class AhoCorasick
{
public:
	AhoCorasick(std::unordered_map<MyString, std::vector<size_t>>& includings);
	void add_words();
	void add_suff();
	void add_output_ref();
	void check_string(const MyString& str);
	std::unordered_map<MyString, std::vector<size_t>> includings;
private:
	std::unique_ptr<Node> bor;

};
#endif // !AHOCORASICK_H




