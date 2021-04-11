#pragma once
#include "h_string.h"

class h_node {
	friend class h_list;
private:
	h_node* prev;
	h_node* next;
	h_string value;
public:
	h_node() {
		prev = NULL;
		next = NULL;
	}
	h_node(h_string &s) {
		prev = NULL;
		next = NULL;
		value = s;
	}
	~h_node() {
		prev = NULL;
		next = NULL;
		value.clear();
	}
};

class h_list
{
private:
	h_node *begin;
	h_node *end;
	int len;
public:
	h_list();
	~h_list();
	int push_front(h_string& s);
	h_string pop_front();
	int push_back(h_string& s);
	h_string pop_back();
	int search(h_string& s);
	size_t size();
};


