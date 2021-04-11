#include "h_unordered_map.h"
#include <math.h>

int string_to_key(h_string& s) {
	int result = 0;
	for (int i = 0; i < s.length(); i++)
		result += s[i];
	result %= 5000;
	return result;
}

h_unordered_map::h_unordered_map() {}
h_unordered_map::~h_unordered_map() {}

void h_unordered_map::insert(h_string& s, int ID, article &html) {
	int key = string_to_key(s);
	node *temp= table[key].begin;
	while (temp != NULL) {
		if(s == temp->value){
			for (int i = 0; i < temp->IDS.size(); i++) {
				if (temp->IDS[i].first == ID) {
					temp->IDS[i].second++;
					if (temp->IDS[i].second > html.get_tf()) 
						html.set_tf(temp->IDS[i].second);
					return;
				}
			}
			std::pair<int, int> tp;
			tp.first = ID;
			tp.second = 1;
			if (tp.second > html.get_tf())
				html.set_tf(tp.second);
			temp->IDS.push_back(tp);
			return;
		}
		temp = temp->next;
	}
	table[key].push_back(s);
	std::pair<int,int> tp;
	tp.first = ID;
	tp.second = 1;
	if (tp.second > html.get_tf())
		html.set_tf(tp.second);
	table[key].end->IDS.push_back(tp);
}

std::vector<std::pair<int,int>> h_unordered_map::search(h_string& s) {
	int key = string_to_key(s);
	node* temp = table[key].begin;
	while (temp != NULL) {
		if (s == temp->value) {
			return temp->IDS;
		}
		temp = temp->next;
	}
	std::vector<std::pair<int, int>> a;
	return a;
}

int h_unordered_map::get_df(h_string& s) {
	int key = string_to_key(s);
	node* temp = table[key].begin;
	while (temp != NULL) {
		if (s == temp->value) {
			return temp->IDS.size();
		}
		temp = temp->next;
	}
	return -1;
}