#pragma once
#include "h_string.h"

class h_node {
private:
	h_node* prev;
	h_node* next;
	h_string value;
public:
	h_string get_value() {
		return value;
	}
};

class h_list
{
private:
	h_node *begin;
	h_node *end;
	int len;
public: 
	h_string push_front(h_string& s);
	h_string pop_front(h_string& s);
	h_string push_back(h_string& s);
	h_string pop_back(h_string& s);
	int search(h_string& s);
	size_t size(h_string& s);
};


