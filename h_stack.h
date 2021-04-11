#pragma once
#include "h_string.h"

class h_stack{
private:
	int size;
	int max_size;
	h_string* top, * bottom;
public:
	h_stack();
	~h_stack();
	int push(h_string s);
	h_string pop();
	h_string& get_top();
};

