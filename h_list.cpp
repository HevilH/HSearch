#include "h_list.h"

h_list::h_list() {
	begin = NULL;
	end = NULL;
	len = 0;
}

h_list::~h_list() {
	if (begin == NULL)
		return;
	h_node* temp = begin;
	while (1) {
		h_node* tmp = temp;
		temp = temp->next;
		delete tmp;
		if (temp == end) {
			delete temp;
			break;
		}
	}
	begin = NULL;
	end = NULL;
}

size_t h_list::size(){
	return (size_t)len;
}

int h_list::push_front(h_string& s) {
	if (begin == NULL) {
		begin = new h_node(s);
		begin->prev = begin;
		begin->next = begin;
		end = begin;
	}
	else {
		h_node* tmp = begin;
		begin = new h_node(s);
		begin->next = tmp;
		tmp->prev = begin;
		begin->prev = end;
		end->next = begin;
	}
	len++;
	return 1;
}

h_string h_list::pop_front() {
	if (begin == NULL) {
		h_string result;
		return result;
	}
	else if (len == 1) {
		len--;
		h_string result(begin->value);
		h_node* tmp = begin;
		delete tmp;
		begin = NULL;
		end = NULL;
		return result;
	}
	else {
		len--;
		h_string result(begin->value);
		h_node* tmp = begin;
		begin = begin->next;
		begin->prev = end;
		end->next = begin;
		delete tmp;
		return result;
	}
}

int h_list::push_back(h_string& s) {
	if (begin == NULL) {
		begin = new h_node(s);
		begin->prev = begin;
		begin->next = begin;
		end = begin;
	}
	else {
		h_node* tmp = end;
		end = new h_node(s);
		end->prev = tmp;
		tmp->next = end;
		begin->prev = end;
		end->next = begin;
	}
	len++;
	return 1;
}

h_string h_list::pop_back() {
	if (begin == NULL) {
		h_string result;
		return result;
	}
	else if (len == 1) {
		len--;
		h_string result(begin->value);
		h_node* tmp = begin;
		delete tmp;
		begin = NULL;
		end = NULL;
		return result;
	}
	else {
		len--;
		h_string result(end->value);
		end->value.clear();
		end = end->prev;
		begin->prev = end;
		end->next = begin;
		return result;
	}
}

int h_list::search(h_string& s) {
	h_node* temp = begin;
	int pos = -1;
	for (int i = 0; i < len; i++) {
		if (temp->value == s) {
			pos = i;
			break;
		}
		temp = temp->next;
	}
	return pos;
}