#pragma once
#include<stdio.h>
#include<stdlib.h>

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

class List {
	Node* beginning;
	Node* actual;
	Node* end;
	Node* prev;
	bool empty;
public:
	void addBeg(int n);
	void addEnd(int n);
	void addAct(int n);
	void delBeg();
	void delAct();
	void delEnd();
	void delVal(int n,Node* cursor_prev,Node* cursor);
	void printForward();
	void printBackward();
	void Next();
	void Prev();
	void Actual();
	Node* getBeg();
	Node* getEnd();
	List();
	~List();
private:
	void addToEmpty(int n);
	Node* getPtr(Node* a, Node* b);
};