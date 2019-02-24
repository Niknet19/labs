#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
typedef struct node {
	int value;
	int height;
	struct node* left;
	struct node* right;
}node;

node* node_constructor(int key) {
	node* p = (node*)malloc(sizeof(node));
	p->value = key;
	p->height = 1;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void node_destructor(node *p) {
	if (p->left) {
		node_destructor(p->left);
	}
	if (p->right) {
		node_destructor(p->right);
	}
	free(p);
}
int height(node* p) {
	if (p == NULL) {
		return 0;
	}
	else {
		return p->height;
	}
}

int balance_check(node* p) {
	return height(p->right) - height(p->left);
}

void fix_height(node* p) {
	int leftheight = height(p->left);
	int rightheight = height(p->right);
	if (rightheight > leftheight) {
		p->height = ++rightheight;
	}
	else {
		p->height = ++leftheight;
	}
}

node *rightRotation(node* p) {
	node *LeftNode = p->left;
	p->left = LeftNode->right;
	LeftNode->right = p;
	fix_height(p);
	fix_height(LeftNode);
	return LeftNode;
}

node* leftRotation(node* p) {
	node* RightNode = p->right;
	p->right = RightNode->left;
	RightNode->left = p;
	fix_height(p);
	fix_height(RightNode);
	return RightNode;
}

node* make_balance(node* p) {
	fix_height(p);
	int bFactor = balance_check(p);
	if (bFactor == 2) {
		if (balance_check(p->right) < 0) {
			p->right = rightRotation(p->right);
		}
		return leftRotation(p);
	}
	else {
		if (bFactor == -2) {
			if (balance_check(p->left) > 0) {
				p->left = leftRotation(p->left);
			}
			return rightRotation(p);
		}
	}
	return p;
}

node* insertnode(node* p, int key) {
	if (p == NULL)
		return node_constructor(key);
	if (key < p->value) {
		p->left = insertnode(p->left, key);
	}
	else {
		p->right = insertnode(p->right, key);
	}
	return make_balance(p);
}

node* input_node() {
	int count;
	scanf("%d", &count);
	if (count == 0) return NULL;
	node* p = NULL;
	for (int i = 0; i < count; ++i) {
		int tmp;
		scanf("%d", &tmp);
		p = insertnode(p, tmp);
	}
	return p;
}
int main(){
	node* p = input_node();
	if (p == NULL) {
		printf("%d", 0);
		return 0;
	}
	printf("%d", height(p));
	node_destructor(p);
	exit(0);
	return 0;
}