#include "h_trie.h"

void h_trie::insert(h_string &s) {
	if (root == NULL)
		root = new htr_node;
	htr_node *temp = root;
	int i = 0;
	int len = s.length();
	while (i != len) {
		rb_node *check= temp->hptr_set.search(s[i]);
		if (check == NULL) {
			check = temp->hptr_set.insert(s[i]);
			check->trie_ptr = new htr_node(s[i]);
		}
		temp = check->trie_ptr;
		i++;
	}

	if (temp != NULL) {
		temp->is_finish = true;
	}
	return;
}

int h_trie::search(h_string &s, int &index) {
	htr_node* temp = root;
	int i = 0;
	int len = s.length();
	while (i != len) {
		rb_node* check = temp->hptr_set.search(s[i + index]);
		if (check == NULL)
			return 0;
		temp = check->trie_ptr;
		if (temp->is_finish == true)
			return i+1;
		i++;
	}
	return 0;
}