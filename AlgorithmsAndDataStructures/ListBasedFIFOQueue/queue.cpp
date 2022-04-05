#include "Queue.h"

Queue::Queue() {
	this->front = NULL;
	this->back = NULL;
	this->prev_front = NULL;
	this->back_next = NULL;
	this->count = 0;
	this->list = List();
}

void Queue::Push(int n) {
	/* Push value to queue */
	if (list.getSize() == count) this->equalSizeAdd(n);
	else this->differentSizeAdd(n);
}

void Queue::printQueue() {
	/* Prints contnet of queue */
	if (count == 1) printf("%i\n", front->val); // Case with one element
	else if (count > 1) {
		Node* cursor = front;
		Node* cursor_prev = prev_front;
		Node* tmp = NULL;

		for (int i = 0; i < count; i++) {
			printf("%i ", cursor->val);
			tmp = cursor_prev;
			cursor_prev = list.getPtr(cursor,tmp->xr);
			cursor = tmp;
		}
		printf("\n");
	}
	else printf("NULL\n");
}

void Queue::printCount() {
	printf("%i\n", count);
}

void Queue::Pop() {
	/* Pops first element from queue */
	if (count > 0) {
		printf("%i\n", front->val);
		Node* new_prev = list.getPtr(front,prev_front->xr);
		this->front = prev_front;
		this->prev_front = new_prev;
		this->count--;
	}
	else printf("NULL\n");
}

void Queue::garbageSoft() {
	/* Set all elements to zero if they don't belong to queue */
	if (list.getSize() == 1 && count > 0) { // Case with one element
		if (list.getBeg() != front) front->val = 0;
	}
	else if (count > 0) {
		Node* cursor = front;
		Node* cursor_prev = prev_front;
		Node* tmp = NULL;
		bool in_queue = true;
		for (int i = 0; i < list.getSize(); i++) {
			if (!in_queue) cursor->val = 0;
			if (cursor == back) in_queue = false;

			tmp = cursor_prev;
			cursor_prev = list.getPtr(cursor, tmp->xr);
			cursor = tmp;
		}
	}
	else { // If queue is empty set all elements of list to zero
		Node* cursor = list.getBeg();
		Node* cursor_prev = list.getEnd();
		Node* tmp = NULL;
		for (int i = 0; i < list.getSize(); i++) {
			cursor->val = 0;
			tmp = cursor;
			cursor = list.getPtr(cursor_prev, tmp->xr);
			cursor_prev = tmp;
		}
	}
}

void Queue::garbageHard(int n, Node* cursor_prev, Node* cursor) {
	/* Deletes all nodes that doesn't belong to queue, Works like DEL_VAL by using grbageSoft perviously */
	this->garbageSoft();
	if (list.getSize() && cursor != list.getEnd()) {
		if (cursor->val == n) { // Delete
			if (cursor == list.getBeg()) { // Deleted node was beginning of list
				this->updateCount(list.getBeg());
				this->list.delBeg();
			}
			else if (cursor == list.getEnd()) { // Deleted node was end of list
				this->updateCount(list.getEnd());
				this->list.delEnd();
			}
			else {
				Node* succesor = list.getPtr(cursor_prev, cursor->xr);
				Node* succesor_next = list.getPtr(cursor, succesor->xr);
				Node* predecessor_prev = list.getPtr(cursor, cursor_prev->xr);

				cursor_prev->xr = list.getPtr(predecessor_prev, succesor); // Update Node's predecessor
				succesor->xr = list.getPtr(cursor_prev, succesor_next); // Update Node's succesor

				delete cursor;
				if (list.getSize() == 1) list.setState(true);
				list.updateSize(-1);
				this->list.delVal(n, cursor_prev, succesor);
			}
			this->list.delVal(n, list.getEnd(), list.getBeg()); // Next position after deleting end/beg
		}
		else { // Next position without deleting
			Node* succesor = list.getPtr(cursor_prev, cursor->xr);
			this->list.delVal(n, cursor, succesor);
		}
	}
	else if (cursor == list.getEnd()) { // Escape condition if list isn't empty and cursor arrived to end
		if (cursor->val == n) { // Deleted node was end of list
			this->updateCount(list.getEnd());
			this->list.delEnd();
		}
	}
}

Node* Queue::getFront(){
	return front;
}
Node* Queue::getPrevFront() {
	return prev_front;
}

int Queue::getCount() const {
	return count;
}

void Queue::forcePushBeg() {
	/* ADD_BEG would otherwise break the list, ADD_BEG in this case is also adding element to queue */
	this->count++;
}

void Queue::forcePushEnd(Node* prev_end) {
	/* ADD_END would otherwise break the list, ADD_END int this case is also adding element to queue */
	this->count++;
	if (prev_end == back) {
		back_next = list.getEnd();
	}
}

void Queue::setPrevFront(Node* new_prev) {
	this->prev_front = new_prev;
}

void Queue::updateCount(Node* deleted_node) {
	/* Checks if deleted node belonged to queue and update size of queue */
	if (count > 0) {
		Node* cursor = front;
		Node* cursor_prev = prev_front;
		Node* tmp = NULL;
		bool in_queue = true;
		for (int i = 0; i < list.getSize(); i++) {
			if (in_queue && cursor == deleted_node) {
				this->count--;
				break;
			}
			if (cursor == back) in_queue = false;

			tmp = cursor_prev;
			cursor_prev = list.getPtr(cursor, tmp->xr);
			cursor = tmp;
		}
	}
}

bool Queue::isPassed(Node* node) {
	/* Check if recently added node is necessary to loop through to get to the back of queue */
	if (count > 0) {
		Node* cursor = front;
		Node* cursor_prev = prev_front;
		Node* tmp = NULL;
		for (int i = 0; i < count; i++) {
			if (cursor == node) return true;
			tmp = cursor_prev;
			cursor_prev = list.getPtr(cursor, tmp->xr);
			cursor = tmp;
		}
	}
	return false;
}

void Queue::equalSizeAdd(int n) {
	/* Procedure to push element inside queue but queue is same size as list */
	if (list.getEnd() == front || list.getSize() == 0) {
		list.addBeg(n);
		Node* node = list.getBeg();
		if (count >= 1) this->back_next = back; // Queue has 2 elements update back_next every time after that
		this->back = node;
		if (count == 0) this->front = node; // Queue has 1 element
		if (count == 1) this->prev_front = back; // Queue has 2 elements, set prev_front
		this->count++;
	}
	else { // add new node between front and back 
		Node* node = new Node(n);
		node->xr = list.getPtr(front, back);
		node->val = n;
		front->xr = list.getPtr(prev_front, node);
		back->xr = list.getPtr(node, back_next);
		this->back_next = back;
		this->back = node;
		this->count++;
		list.updateSize(1);
	}
}

void Queue::differentSizeAdd(int n) {
	/* Procedure to push element inside queue when size > count */
	if (count == 0) {
		Node* cursor = list.getBeg();
		Node* cursor_prev = list.getEnd();
		Node* tmp = NULL;

		while (cursor->val != n) { // Check if element alredy exists in queue
			tmp = cursor;
			cursor = list.getPtr(cursor_prev, tmp->xr);
			cursor_prev = tmp;
			if (cursor == list.getEnd()) {
				cursor = list.getEnd();
				break;
			}
		}
		cursor->val = n; // If not set wanted value at the end of list
		this->prev_front = cursor_prev;
		this->front = cursor;
		this->back = cursor;
	}
	else {
		if (count == 1) this->back_next = list.getPtr(prev_front, front->xr); // Because back_next don't exist yet
		Node* back_prev = list.getPtr(back_next,back->xr); // Getting position in queue if we add new element
		back_prev->val = n;
		this->back_next = back;
		this->back = back_prev;
	}
	this->count++;
}

Queue::~Queue() {}