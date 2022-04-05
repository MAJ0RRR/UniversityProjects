#include"board.h"
#include"player.h"
#include"GM.h"
int main() {
	// Initialize board
	Board* board = new Board();
	// Initialize Players
	Player* P1 = new Player(board, 'A');
	Player* P2 = new Player(board, 'B');
	// Initialize GM
	GameMaster* GM = new GameMaster(P1,P2,board);
	// Game loop
	char buffer[MAX_TAG_SIZE];
	while (scanf_s("%s", buffer,MAX_TAG_SIZE) != EOF)
	{
		if (!GM->errorOccured()) {
			if (!strcmp(buffer, "[playerA]") || !strcmp(buffer, "[playerB]")) {  // Player commands
				GM->initPlayerTurn(buffer);
				GM->startProcessing();
				while (GM->isProcessing()) GM->parsePlayer(buffer);
			}
			else if (!strcmp(buffer, "[state]")) {	// State commands
				GM->startProcessing();
				while (GM->isProcessing()) GM->parseState(buffer);
			}
		}
	}
	return 0;
}