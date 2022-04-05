#define _CRT_SECURE_NO_WARNINGS
#define BUFFER 48
#include"Queue.h"
#include<string.h>

int main() {
	Queue Q;
	int n;
	char command[BUFFER];

	while (scanf_s("%s", &command,BUFFER) != EOF) {
		if (!strcmp(command, "ACTUAL")) Q.list.Actual();
		else if (!strcmp(command, "PREV")) Q.list.Prev();
		else if (!strcmp(command, "NEXT")) Q.list.Next();
		else if (!strcmp(command, "SIZE")) Q.list.printSize();
		else if (!strcmp(command, "PRINT_FORWARD")) Q.list.printForward();
		else if (!strcmp(command, "PRINT_BACKWARD")) Q.list.printBackward();
		else if (!strcmp(command, "PRINT_QUEUE")) Q.printQueue();
		else if (!strcmp(command, "COUNT")) Q.printCount();
		else if (!strcmp(command, "POP")) Q.Pop();
		else if (!strcmp(command, "GARBAGE_SOFT")) Q.garbageSoft();
		else if (!strcmp(command, "GARBAGE_HARD")) Q.garbageHard(0, Q.list.getEnd(), Q.list.getBeg());
		else if (!strcmp(command, "ADD_BEG")) {
			scanf("%i", &n);
			Node* current_beg = Q.list.getBeg();
			Q.list.addBeg(n);
			if (current_beg == Q.getFront()) Q.setPrevFront(Q.list.getBeg()); // Update prev_front pointer
			if (Q.isPassed(Q.list.getBeg())) Q.forcePushBeg(); // Special case when ADD_BEG push value to queue
		}
		else if (!strcmp(command, "ADD_END")) {
			scanf("%i", &n);
			Node* prev_end = Q.list.getEnd();
			Q.list.addEnd(n);
			if (Q.getCount() == 1) Q.setPrevFront(Q.list.getEnd()); // Case with 2 elements 
			if (Q.list.getSize() > 2 && Q.isPassed(Q.list.getEnd())) Q.forcePushEnd(prev_end);
		}
		else if (!strcmp(command, "ADD_ACT")) {
			scanf("%i", &n);
			Q.list.addAct(n);
		}
		else if (!strcmp(command, "DEL_BEG")) {
			Q.updateCount(Q.list.getEnd());
			if (Q.list.getBeg() == Q.getPrevFront()) { // Deleted value was prev_front
				Q.setPrevFront(Q.list.getEnd());
			}
			Q.list.delBeg();
		}
		else if (!strcmp(command, "DEL_END")) {
			Q.updateCount(Q.list.getEnd());
			if (Q.list.getEnd() == Q.getPrevFront()) { // Deleted value was prev_front
				Q.setPrevFront(Q.list.getPtr(Q.getFront(),Q.getPrevFront()->xr));
			}
			Q.list.delEnd();
		}
		else if (!strcmp(command, "DEL_ACT")) {
			Q.updateCount(Q.list.getActual());
			Q.list.delAct();
		}
		else if (!strcmp(command, "DEL_VAL")) {
			scanf("%i", &n);
			Q.list.delVal(n, Q.list.getEnd(), Q.list.getBeg());
		}
		else if (!strcmp(command, "PUSH")) {
			scanf("%i", &n);
			Q.Push(n);
		}
	}
	return 0;
}