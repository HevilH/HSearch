#pragma once
#include "h_set.h"

class htr_node {
	friend class h_trie;
private:
	wchar_t value;
	h_set hptr_set;
	bool is_finish;
public:
	htr_node() {
		is_finish = false;
		value = 0;
	};
	htr_node(wchar_t s) {
		value = s;
		is_finish = false;
	}
};

class h_trie
{
private:
	htr_node* root;
public:
	h_trie() {
		root = NULL;
	};
	
	void insert(h_string& s);
	int search(h_string& s, int &index);
};

