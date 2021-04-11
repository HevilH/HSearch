#include "h_stack.h"

h_stack::h_stack() {
	max_size = 100;
	size = 0;
	bottom = new h_string[max_size];
	top = bottom;
}

h_stack::~h_stack() {
	delete[] bottom;
}

int h_stack::push(h_string s) {
	if (size == max_size) {
		max_size *= 2;
		h_string* tmp = bottom;
		bottom = new h_string[max_size];
		top = bottom;
		for (int i = 0; i < size; i++) {
			*top = tmp[i];
			top++;
		}
		*top = s;
		delete[] tmp;
		size++;
	}
	else {
		if (size != 0)
			top++;
		*top = s;
		size++;
	}
	return 1;
}

h_string h_stack::pop() {
	if (size == 0) {
		h_string result;
		return result;
	}
	else {
		size--;
		h_string result(*top);
		top--;
		return result;
	}
}

h_string& h_stack::get_top(){
	return *top;
}