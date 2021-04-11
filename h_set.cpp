#include "h_set.h"

h_set::h_set() {
	root = NULL;
}

rb_node *h_set::insert(wchar_t s){
	rb_node* node = new rb_node(s);
	rb_node* result = node;
	root = insert_node(root, node);
	//fix
	rb_node *parent = NULL;
	rb_node* grand_parent = NULL;
	while (node != root && node->color == red && node->parent->color == red) {
		parent = node->parent;
		grand_parent = parent->parent;
		if (parent == grand_parent->left) {
			rb_node* uncle = grand_parent->right;
			if (uncle != NULL && uncle->color == red) {
				grand_parent->color = red;
				uncle->color = black;
				parent->color = black;
				node = grand_parent;
			}
			else {
				if (node == parent->right) {
					rotate_l(parent);
					node = parent;
					parent = node->parent;
				}
				rotate_r(grand_parent);
				int tmp_color = parent->color;
				parent->color = grand_parent->color;
				grand_parent->color = tmp_color;
				node = parent;
			}
		}
		else {
			rb_node* uncle = grand_parent->left;
			if (uncle != NULL && uncle->color == red) {
				grand_parent->color = red;
				uncle->color = black;
				parent->color = black;
				node = grand_parent;
			}
			else {
				if (node == parent->left) {
					rotate_r(parent);
					node = parent;
					parent = node->parent;
				}
				rotate_l(grand_parent);
				int tmp_color = parent->color;
				parent->color = grand_parent->color;
				grand_parent->color = tmp_color;
				node = parent;
			}
		}
	}
	root->color = black;
	return result;
}

rb_node* h_set::insert_node(rb_node *temp, rb_node *node) {
	if (temp == NULL)
		return node;

	if (node->value >= temp->value) {
		temp->right = insert_node(temp->right, node);
		temp->right->parent = temp;
	}
	else {
		temp->left = insert_node(temp->left, node);
		temp->left->parent = temp;
	}
	return temp;
}

void h_set::rotate_l(rb_node* node) {
	rb_node* right_child = node->right;
	node->right = right_child->left;

	if (node->right != NULL)
		node->right->parent = node;

	right_child->parent = node->parent;

	if (node->parent == NULL)
		root = right_child;
	else if (node == node->parent->left)
		node->parent->left = right_child;
	else
		node->parent->right = right_child;

	right_child->left = node;
	node->parent = right_child;
}

void h_set::rotate_r(rb_node* node) {
	rb_node* left_child = node->left;
	node->left = left_child->right;

	if (node->left != NULL)
		node->left->parent = node;

	left_child->parent = node->parent;

	if (node->parent == NULL)
		root = left_child;
	else if (node == node->parent->left)
		node->parent->left = left_child;
	else
		node->parent->right = left_child;

	left_child->right = node;
	node->parent = left_child;
}

rb_node *h_set::search(wchar_t s) {
	return search_node(root, s);
}

rb_node *h_set::search_node(rb_node* temp, wchar_t &s) {
	if (temp == NULL)
		return NULL;
	if (s == temp->value)
		return temp;
	if (s >= temp->value)
		return search_node(temp->right, s);
	else
		return search_node(temp->left, s);
}