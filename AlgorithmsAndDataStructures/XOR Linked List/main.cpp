#pragma warning( disable : 6031 6054 )
#define _CRT_SECURE_NO_WARNINGS
#define BUFFER 24
#include"List.h"
#include<string.h>

int main() {
	List list;
	int n;
	char command[BUFFER];

	while (scanf("%s", &command) != EOF) {
		if (!strcmp(command, "ACTUAL")) list.Actual();
		else if (!strcmp(command, "PREV")) list.Prev();
		else if (!strcmp(command, "NEXT"))list.Next();
		else if (!strcmp(command, "DEL_BEG")) list.delBeg();
		else if (!strcmp(command, "DEL_END")) list.delEnd();
		else if (!strcmp(command, "DEL_ACT")) list.delAct();
		else if (!strcmp(command, "PRINT_FORWARD")) list.printForward();
		else if (!strcmp(command, "PRINT_BACKWARD")) list.printBackward();

		else if (!strcmp(command, "ADD_BEG")) {
			scanf("%i", &n);
			list.addBeg(n);
		}
		else if (!strcmp(command, "ADD_END")) {
			scanf("%i", &n);
			list.addEnd(n);
		}
		else if (!strcmp(command, "ADD_ACT")) {
			scanf("%i", &n);
			list.addAct(n);
		}
		else if (!strcmp(command, "DEL_VAL")) {
			scanf("%i", &n);
			list.delVal(n,list.getEnd(),list.getBeg());
		}
	}
	return 0;
}