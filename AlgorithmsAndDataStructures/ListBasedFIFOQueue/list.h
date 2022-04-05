#pragma once
#include"Node.h"

class List {
private:
	Node* prev;
	Node* beginning;
	Node* actual;
	Node* end;
	bool empty;
	int size;
public:
	void addBeg(int n);
	void addEnd(int n);
	void addAct(int n);
	void delBeg();
	void delEnd();
	void delAct();
	void delVal(int n, Node* cursor_prev, Node* cursor);
	void printBackward();
	void printForward();
	void Next();
	void Prev();
	void Actual();
	int getSize() const;
	void printSize();
	Node* getBeg();
	Node* getEnd();
	Node* getActual();
	void setState(bool state);
	void updateSize(int n);
	Node* getPtr(Node* a, Node* b);
	List();
	~List();
private:
	void addToEmpty(int n);
};