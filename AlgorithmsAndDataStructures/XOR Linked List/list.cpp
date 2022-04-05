#include"List.h"

	List::List() {
		this->beginning = NULL;
		this->actual = NULL;
		this->end = NULL;
		this->prev = NULL;
		this->empty = true;
	}

	void List::addBeg(int n) {
		/* Add Node at the beginning of List*/
		if (empty) addToEmpty(n);
		else {
			Node* node = new Node(n);
			node->xr = getPtr(end,beginning);
			if (actual == beginning) {
				this->prev = node;
			}
			Node* next_node = getPtr(end,beginning->xr); // Update node's succesor
			this->beginning->xr = getPtr(node, next_node);

			Node* prev_node = getPtr(beginning, end->xr); // Update node's predecssor
			this->end->xr = getPtr(prev_node, node);

			this->beginning = node; // Node becomes new beginning
		}
	}

	void List::addEnd(int n) {
		/* Add Node at the end of List */
		if (empty) addToEmpty(n);
		else {
			Node* node = new Node(n);
			node->xr = getPtr(end,beginning);
			if (actual == beginning) {
				this->prev = node;
			}
			
			Node* prev_node = getPtr(beginning, end->xr); // Update node's predecessor
			this->end->xr = getPtr(prev_node, node);

			Node* next_node = getPtr(end, beginning->xr); // Update node's succesor
			this->beginning->xr = getPtr(node, next_node);
			
			this->end = node; // Node becomes new end
		}
	}

	void List::addAct(int n) {
		/* Adds Node as predecessor of Actual cursor */
		if (empty) addToEmpty(n);
		else {
			if (actual == beginning) {
				this->addBeg(n);
			}
			else {
				Node* node = new Node(n);
				node->xr = getPtr(prev, actual);

				Node* next_node = getPtr(prev, actual->xr); // Update node's succesor
				this->actual->xr = getPtr(node, next_node);

				Node* prev_node = getPtr(actual, prev->xr); // Update node's predecessor
				this->prev->xr = getPtr(prev_node, node);

				this->prev = node; // Node is set as predecessor of actual
			}
		}
	}

	void List::delBeg() {
		/* Deletes first Node from list */
		if (!empty) {
			if (beginning == actual && end == actual) this->empty = true;
			Node* node = getPtr(end, beginning->xr);
			Node* predecessor_prev = getPtr(beginning, end->xr);
			Node* next = getPtr(beginning, node->xr);

			node->xr = getPtr(end, next); // Update new beginning
			end->xr = getPtr(predecessor_prev, node); // Update node's predecessor
			if (actual == beginning) {
				this->actual = end;
			}

			delete beginning;
			this->beginning = node;
		}
	}

	void List::delEnd() {
		/* Deletes last node in list */
		if (!empty) {
			if (beginning == actual && end == actual) this->empty = true;
			Node* node = getPtr(beginning, end->xr);
			Node* predecessor_prev = getPtr(end, node->xr);
			Node* next = getPtr(end, beginning->xr);

			node->xr = getPtr(predecessor_prev, beginning); // Update new end
			beginning->xr = getPtr(node, next); // Update node's succesor
			if (actual == end) {
				this->actual = node;
			}
			delete end;
			this->end = node;
		}
	}

	void List::delAct() {
		/* Deletes node where cursor points */
		if (!empty) {
			if (beginning == actual && end == actual) this->empty = true;
			if (actual == beginning) {
				this->delBeg();
			}
			else if (actual == end) {
				this->delEnd();
			}
			else {
				Node* node = prev;
				Node* succesor = getPtr(prev, actual->xr);
				Node* predecessor = getPtr(actual, prev->xr);
				Node* predecessor_prev = getPtr(prev, predecessor->xr);
				Node* succesor_next = getPtr(actual, succesor->xr);

				node->xr = getPtr(predecessor, succesor); // Update new actual
				succesor->xr = getPtr(node, succesor_next); // Update node's succesor
				predecessor->xr = getPtr(predecessor_prev, node); // Update node's predecessor

				delete actual;
				this->actual = prev;
				this->prev = predecessor;
			}
		}
	}

	void List::delVal(int n,Node* cursor_prev,Node* cursor) {
		/* Deletes all nodes containg 'n' value */
		if (!empty && cursor != end) {
			if (cursor->val == n) { // Delete
				if (cursor == beginning) this->delBeg();
				else if (cursor == end) this->delEnd();
				else {
					Node* succesor = getPtr(cursor_prev, cursor->xr);
					Node* succesor_next = getPtr(cursor, succesor->xr);
					Node* predecessor_prev = getPtr(cursor, cursor_prev->xr);

					cursor_prev->xr = getPtr(predecessor_prev, succesor); // Update Node's predecessor
					succesor->xr = getPtr(cursor_prev, succesor_next); // Update Node's succesor

					delete cursor;
					if (succesor == NULL) this->empty = true;
					this->delVal(n, cursor_prev, succesor);
				}
				this->delVal(n, end, beginning); // Next position after deleting end/beg
			}
			else { // Next position without deleting
				Node* succesor = getPtr(cursor_prev, cursor->xr);
				this->delVal(n, cursor, succesor);
			}
		}
		else if (cursor == end) { // Escape condition if list isn't empty and cursor arrived to end
			if (cursor->val == n) this->delEnd();
		}
	}

	void List::printForward() {
		/* Prints all Nodes from beginning to end */
		if (!empty) {
			Node* cursor = beginning;
			Node* cursor_prev = end;
			Node* tmp;

			while (cursor != end) {
				printf("%i ", (*cursor).val);
				tmp = cursor;
				cursor = getPtr(cursor_prev, tmp->xr);
				cursor_prev = tmp;
			}
			printf("%i\n", (*cursor).val);
		}
		else {
			printf("NULL\n");
		}
	}

	void List::printBackward() {
		/* Prints all Nodes from end to beginning */
		if (!empty) {
			Node* cursor = end;
			Node* cursor_next = beginning;
			Node* tmp;

			while (cursor != beginning) {
				printf("%i ", (*cursor).val);
				tmp = cursor;
				cursor = getPtr(cursor_next, tmp->xr);
				cursor_next = tmp;
			}
			printf("%i\n", (*cursor).val);
		}
		else {
			printf("NULL\n");
		}
	}

	void List::Actual() {
		/* Returns value of element pointed currently by cursor */
		if (empty) printf("NULL\n");
		else if (beginning == actual && end == actual) printf("%i\n", actual->val);
		else printf("%i\n", actual->val);
	}

	void List::Next() {
		/* Moves cursor to the right and returns value of next element */
		if (empty) printf("NULL\n");
		else if (beginning == actual && end == actual) printf("%i\n", actual->val);
		else {
			Node* next = getPtr(prev, actual->xr);
			this->prev = actual;
			this->actual = next;
			printf("%i\n", actual->val);
		}
	}

	void List::Prev() {
		/* Moves cursor to the left and returns value of previous element */
		if (empty) printf("NULL\n");
		else if (beginning == actual && end == actual) printf("%i\n", actual->val);
		else {
			Node* node = getPtr(actual, prev->xr);
			this->actual = prev;
			this->prev = node;
			printf("%i\n", actual->val);
		}
	}

	Node* List::getBeg() {
		return beginning;
	}

	Node* List::getEnd() {
		return end;
	}

	void List::addToEmpty(int n) {
		/* Procedrue to Add Node to Empty List */
		Node* node = new Node(n);
		node->xr = NULL;
		this->beginning = node;
		this->actual = node;
		this->end = node;
		this->empty = false;
	}

	Node* List::getPtr(Node* a, Node* b) {
		/* Returns XOR of two adresses */
		return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
	}

	List::~List() {
	}