#pragma once
#include "h_list.h"
#include "article.h"
#include <vector>



class node {
	friend class hlist;
	friend class h_unordered_map;
private:
	node* next;
	h_string value;
	std::vector<std::pair<int, int>> IDS;

public:
	node() {
		next = NULL;
	}
	node(h_string &s) {
		value = s;
		next = NULL;
	}
	~node() {
		next = NULL;
	}
};

class hlist
{
	friend class h_unordered_map;
private:
	node* begin;
	node* end;
	int len;
public:
	hlist() {
		begin = NULL;
		end = NULL;
		len = 0;
	}
	~hlist() {
		begin = NULL;
		end = NULL;
	}
	int push_back(h_string &s) {
		len++;
		if (begin == NULL) {
			begin = new node(s);
			end = begin;
			return 1;
		}
		node* tmp = end;
		end = new node(s);
		tmp->next = end;
		return 1;
	}
};

class h_unordered_map {
private:
	hlist table[5000];
public:
	h_unordered_map();
	~h_unordered_map();
	void insert(h_string& s, int ID, article& html);
	std::vector<std::pair<int, int>> search(h_string& s);
	int get_df(h_string& s);
};
