#define _CRT_SECURE_NO_WARNINGS
#include"GM.h"

GameMaster::GameMaster(Player* p1,Player* p2, Board* b): game_over(false), processing_segment(false),
					   error_occured(false),ships_placed(false),player1(p1),player2(p2), 
					   current_player(nullptr), board(b) {};


// Sets current player
void GameMaster::initPlayerTurn(char* command) {
	if (!strcmp(command, "[playerA]")) current_player = player1;
	else if(!strcmp(command,"[playerB]")) current_player = player2;
}

// Organize player's input and invokes placeShip command from Board
bool GameMaster::placeShip(char* command) {
	// PLACE_SHIP y x D i C
	// 0		  1 2 3 4 5
	if (!strcmp(getNextWord(command, 0), "PLACE_SHIP")) {
		// Declarations
		int y, x, i, err_code = 0;
		Direction dir;
		char ship_class[4];
		// Translate
		y = atoi(getNextWord(command, 1));
		x = atoi(getNextWord(command, 2));
		dir = board->charToDir(getNextWord(command, 3));
		i = atoi(getNextWord(command, 4));
		strcpy(ship_class, getNextWord(command, 5));
		if (i >= current_player->fleet_info[board->typeToIdx(ship_class)]) // all ships of the class error 
			err_code = ALL_SHIPS_OF_THE_CLASS_ALREDY_SET;
		Ship* ship = current_player->getShip(board->typeToIdx(ship_class),i);
		if (current_player->ships_on_board.is_on_board(ship)) err_code = SHIP_ALREDY_PRESENT; // ship present error
		board->placeShip(ship,y,x,dir,ship_class,current_player->getName(),&err_code);
		if (err_code < 0) {
			handleErrorPlaceShip(err_code, y, x, i, getNextWord(command,3), ship_class);
			return false;
		}
		current_player->dockShip(ship,i);
		board->boundToField(ship, x, y);
		return true;
	}
	return false;
}

// Invoke shooting function for currently playing player
bool GameMaster::shoot(char* command) {
	// SHOOT y x
	// 0	 1 2
	if (!strcmp(getNextWord(command, 0), "SHOOT")) {
		// Declarations
		int y, x, err_code = 0;
		// Translate
		y = atoi(getNextWord(command, 1));
		x = atoi(getNextWord(command, 2));
		if (player1->ships_on_board.getLength() == player1->getSize() && // check if all ships are placed
			player2->ships_on_board.getLength() == player2->getSize()) {
			ships_placed = true;
		}
		if (ships_placed) {
			board->shoot(y, x, &err_code);
			checkforWinner();
		}
		else err_code = NOT_ALL_SHIPS_PLACED; 
		if (err_code < 0) {
			handleErrorShoot(err_code, y, x);
			return false;
		}
		return true;
	}
	return false;
}

// Check if any of the players won
void GameMaster::checkforWinner() {
	if (player1->ships_on_board.sum() == 0) {
		printf("B won\n");
		game_over = true;
	}
	else if (player2->ships_on_board.sum() == 0) {
		printf("A won\n");
		game_over = true;
	}
}

// Set custom fleet for player
bool GameMaster::setFleet(char* command) {
	// SET_FLEET P a1 a2 a3 a4
	// 0         1  2  3  4  5
	if (!strcmp(getNextWord(command, 0), "SET_FLEET")) {
		// Declarations
		int a1, a2, a3, a4;
		char name = *getNextWord(command, 1);
		a1 = atoi(getNextWord(command, 2));
		a2 = atoi(getNextWord(command, 3));
		a3 = atoi(getNextWord(command, 4));
		a4 = atoi(getNextWord(command, 5));
		if (name == 'A') player1->setFleet(a1, a2, a3, a4);
		else if (name == 'B') player2->setFleet(a1, a2, a3, a4);
		else return false;
		return true;
	}
	return false;
}

// Print current game state
bool GameMaster::printState(char* command) {
	if (!strcmp("PRINT", getNextWord(command,0))) {
		board->printBoard();
		printf("PARTS REMAINING:: A : %i B : %i\n", player1->ships_on_board.sum(), player2->ships_on_board.sum());
		return true;
	}
	return false;
}

// Handles error codes for placeShip
void GameMaster::handleErrorPlaceShip(int error_code,int y,int x,int i,char* dir,char* ship_class) {
	switch (error_code) {
		case NOT_IN_STARTING_POSITION:
			printf("INVALID OPERATION \"PLACE_SHIP %d %d %s %d %s\": NOT IN STARTING POSITION",
				    y,x,dir,i,ship_class);
		break;
		case SHIP_ALREDY_PRESENT:
			printf("INVALID OPERATION \"PLACE_SHIP %d %d %s %d %s\": SHIP ALREADY PRESENT",
				y, x, dir, i, ship_class);
			break;
		case ALL_SHIPS_OF_THE_CLASS_ALREDY_SET:
			printf("INVALID OPERATION \"PLACE_SHIP %d %d %s %d %s\": ALL SHIPS OF THE CLASS ALREADY SET",
				y, x, dir, i, ship_class);
			break;
	}
	error_occured = true;
	processing_segment = false;
}

// Handles error codes for shoot
void GameMaster::handleErrorShoot(int error_code, int y, int x) {
	switch (error_code) {
		case FIELD_DOES_NOT_EXIST:
			printf("INVALID OPERATION \"SHOOT %d %d\": FIELD DOES NOT EXIST", y, x);
			break;
		case NOT_ALL_SHIPS_PLACED:
			printf("INVALID OPERATION \"SHOOT %d %d\": NOT ALL SHIPS PLACED", y, x);
			break;
	}
	error_occured = true;
	processing_segment = false;
}

// Handle error codes when player tries to make too many moves in one turn
void GameMaster::handleErrorTurn(int error_code, char* tag) {
	switch (error_code) {
		case THE_OTHER_PLAYER_EXPECTED:
			printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED", tag);
			break;
	}
	error_occured = true;
	processing_segment = false;
}

// Parse player's commands untill closing bracket
void GameMaster::parsePlayer(char* tag) {
	if (!strcmp("[playerA]", tag)) current_player = player1;
	else if (!strcmp("[playerB]", tag)) current_player = player2;

	char buffer[MAX_LINE_LENGTH];
	bool made_move = false;
	while (true) {
		fgets(buffer, MAX_LINE_LENGTH, stdin);
		char* word = getNextWord(buffer, 0);
		if (strlen(word) == 0) continue;
		if (!strcmp(word, tag)) { // Closing tag occured
			processing_segment = false;	
			delete[] word;
			break;
		}
		//if (nextPlayer(buffer)) {
		//	made_move = false;
		//	continue;
		//}
		//if (!made_move) {											//FOR TESTS 11 & 12
			if (placeShip(buffer)) {
				made_move = true;
				continue;
			}
			if (shoot(buffer)) {
				made_move = true;
				continue;
			}
		//}
		//else {
		//	err_code = THE_OTHER_PLAYER_EXPECTED;
		//	handleErrorTurn(err_code, tag);
		//		delete[] word;
		//		break;
		//}
		delete[] word;
	}
}

// Let the player moves more than once
bool GameMaster::nextPlayer(char* command) {
	if (!strcmp(getNextWord(command, 0), "NEXT_PLAYER")) {
		if (!strcmp(getNextWord(command, 1),"A" )) {
			current_player = player1;
		}
		else if (!strcmp(getNextWord(command, 1), "B")) {
			current_player = player2;
		}
		return true;
	}
	return false;
}

// Dynamicaly set board 
bool GameMaster::setBoardSize(char* command) {
	// BOARD y x (row x col)
	//       1 2
	if (!strcmp(getNextWord(command, 0), "BOARD")) {
		// Declarations
		int y, x;
		//Translation
		y = atoi(getNextWord(command, 1));
		x = atoi(getNextWord(command, 2));
		delete board;
		board = new Board(y, x);
	}
	return false;
}

// Starting from first letter return string up to \n or space
char* GameMaster::getNextWord(char* buffer, int idx) {
	char dup[MAX_LINE_LENGTH];
	strcpy(dup, buffer);
	int i = 0;
	char* part = strtok(dup, " ");
	// Iterate to desired word
	while (part != NULL && i < idx )
	{
		part = strtok(NULL, " ");
		i++;
	}
	// Copy word
	char* word = new char[MAX_WORD_LENGTH];
	if (part != NULL) strcpy(word, part);
	else exit(-1);
	// Cut /n from last word
	if (strchr(word, '\n') != nullptr) {
		char* ptr = strrchr(word, '\n');
		if(ptr != nullptr) word[strlen(word) - 1] = '\0';
	}
	return word;
}

// Parse state commands untill closing brakets
void GameMaster::parseState(char* tag) {
	char buffer[MAX_LINE_LENGTH];
	while (true) {
		fgets(buffer, MAX_LINE_LENGTH, stdin);
		char* word = getNextWord(buffer, 0);
		if (strlen(word) == 0) continue;
		if (!strcmp(word, tag)) { // Closing tag occured
			processing_segment = false;
			delete[] word;
			break;
		}
		if (setBoardSize(buffer)) continue;
		else if (printState(buffer)) continue;
		else if (setFleet(buffer)) continue;
		delete[] word;
	}
}


GameMaster::~GameMaster() {};