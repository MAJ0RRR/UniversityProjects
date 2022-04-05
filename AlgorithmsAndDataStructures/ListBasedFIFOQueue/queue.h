#pragma once
#include"List.h"

class Queue {
private:
	Node* front;
	Node* back;
	Node* prev_front;
	Node* back_next;
	int count;
public:
	Queue();
	List list;
	void Push(int n);
	void printQueue();
	void printCount();
	void Pop();
	void garbageSoft();
	void garbageHard(int n,Node* cursor_prev,Node* cursor);
	Node* getFront();
	Node* getPrevFront();
	int getCount() const;
	void forcePushBeg();
	void forcePushEnd(Node* prev_end);
	void setPrevFront(Node* new_prev);
	void updateCount(Node* deleted_node);
	bool isPassed(Node* node);
	~Queue();
private:
	void equalSizeAdd(int n);
	void differentSizeAdd(int n);
};