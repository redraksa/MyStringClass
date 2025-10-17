#include "AhoCorasick.h"


AhoCorasick::AhoCorasick(std::unordered_map<MyString, std::vector<size_t>>& includings) :
	bor(std::make_unique<Node>()), includings(includings) {}

void AhoCorasick::add_words() {
	size_t id = 0;
	bor->id = 0;
	for (auto& str : includings) {
		Node* x = bor.get();

		for (int i = 0; i < str.first.size(); ++i) {
			if (x->childrens.find(str.first[i]) == x->childrens.end()) {
				x->childrens[str.first[i]] = std::make_unique<Node>();
				x->childrens[str.first[i]]->id = ++id;
				//std::cout << str.first[i] << "->" << id << "\n";
			}
			x = x->childrens[str.first[i]].get();
		}
		x->terminal = true;
		x->string_ref = &str.first;
	}
}

void AhoCorasick::add_suff() {
	std::queue<Node*> q;
	bor->suff_ref = bor.get();

	for (auto& child : bor->childrens) {
		child.second->suff_ref = bor.get();
		q.push(child.second.get());
	}

	while (!q.empty()) {
		Node* q_current = q.front();
		q.pop();

		//std::cout << q_current->id << " ";

		for (auto& child : q_current->childrens) {
			char c = child.first;

			Node* child_node = child.second.get();
			q.push(child_node);

			Node* temp = q_current->suff_ref;
			while (temp != bor.get() && temp->childrens.find(c) == temp->childrens.end()) {
				temp = temp->suff_ref;
			}

			if (temp->childrens.find(c) == temp->childrens.end()) {
				child_node->suff_ref = bor.get();
			}
			else {
				child_node->suff_ref = temp->childrens[c].get();
			}

		}
	}
}

void AhoCorasick::add_output_ref() {
	std::queue<Node*> q;
	bor->output_ref = bor.get();

	for (auto& child : bor->childrens) {
		q.push(child.second.get());
		child.second->output_ref = bor.get();
	}

	while (!q.empty()) {
		Node* current = q.front();
		q.pop();

		//std::cout << current->id << " ";
		if (current->suff_ref->terminal) {
			current->output_ref = current->suff_ref;
		}
		else {
			current->output_ref = current->suff_ref->output_ref;
		}

		for (auto& child : current->childrens) {
			q.push(child.second.get());
		}
	}
}

void AhoCorasick::check_string(const MyString& str) {
	Node* ref = bor.get();

	for (int i = 0; i < str.size(); ++i) {
		char ch = str[i];

		if (ref->childrens.find(ch) != ref->childrens.end()) {
			ref = ref->childrens[ch].get();
		}
		else {
			do {
				ref = ref->suff_ref;
			} while (ref->childrens.find(ch) == ref->childrens.end() && ref != bor.get());
			if (ref->childrens.find(ch) != ref->childrens.end()) {
				ref = ref->childrens[ch].get();
			}
		}

		if (ref->terminal) {
			includings[*ref->string_ref].emplace_back(i - ref->string_ref->size() + 1);
		}

		Node* ref_otput = ref;
		while (ref_otput->output_ref != bor.get()) {
			ref_otput = ref_otput->output_ref;
			if (ref_otput->terminal) {
				includings[*ref_otput->string_ref].emplace_back(i - ref->string_ref->size() + 1);
			}
		}
	}
}