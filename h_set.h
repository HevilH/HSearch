#pragma once
#include "h_string.h"


enum color {red, black, d_black};

class htr_node;

class rb_node {
	friend class h_set;
	friend class h_trie;
private:
	wchar_t value;
	htr_node* trie_ptr;

	int color;
	rb_node* parent;
	rb_node* right;
	rb_node* left;

public:
	rb_node() {
		parent = NULL;
		right = NULL;
		left = NULL;
		color = red;
		trie_ptr = NULL;
		value = 0;
	}
	rb_node(wchar_t &s) {
		parent = NULL;
		right = NULL;
		left = NULL;
		trie_ptr = NULL;

		color = red;
		value = s;
	}
	~rb_node() {
		right = NULL;
		left = NULL;
		parent = NULL;
		trie_ptr = NULL;
	}
};

class h_set
{
private:
	rb_node* root;
	void rotate_l(rb_node *node);
	void rotate_r(rb_node *node);
	rb_node* insert_node(rb_node *temp, rb_node *node);
	rb_node *search_node(rb_node* temp, wchar_t &s);

public:
	h_set();
	rb_node *insert(wchar_t s);
	rb_node *search(wchar_t s);
};
