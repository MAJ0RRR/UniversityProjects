#pragma once
#include<stdlib.h>
#include<stdio.h>

typedef struct Node {
	int val;
	Node* xr;
	Node(int n) {
		this->val = n;
		this->xr = NULL;
	}
	Node(Node* node) {
		this->val = node->val;
		this->xr = node->xr;
	}
}Node;