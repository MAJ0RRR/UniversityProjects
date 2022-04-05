#pragma once
#include"defines.h"
#include"player.h"
#include"board.h"

class GameMaster {
private:
	// Game Conditions
	bool game_over;
	bool processing_segment;
	bool error_occured;
	bool ships_placed;
	// Pointers to objects
	Player* player1;
	Player* player2;
	Player* current_player;
	Board* board;
	// Invoking functions with parsed Input
	bool placeShip(char* command);
	bool shoot(char* command);
	bool setFleet(char* command);
	bool printState(char* command);
	bool nextPlayer(char* command);
	// Error handling
	void handleErrorPlaceShip(int error_code, int y, int x, int i, char* dir, char* ship_class);
	void handleErrorShoot(int error_code, int y, int x);
	void handleErrorTurn(int error_code, char* tag);
	// Extended
	bool setBoardSize(char* command);
public:
	// Constructors
	GameMaster(Player* p1, Player* p2, Board* b);
	// Game Conditions
	bool const  isGameOver() const { return game_over; }
	void initPlayerTurn(char* command);
	void startProcessing() { processing_segment = true; }
	bool isProcessing() const { return processing_segment; }
	bool errorOccured() const { return error_occured; }
	void checkforWinner();
	// Matching functions
	void parsePlayer(char* tag);
	void parseState(char* tag);
	// Input manipulation
	char* getNextWord(char* buffer, int idx);
	// Destructors
	~GameMaster();
};