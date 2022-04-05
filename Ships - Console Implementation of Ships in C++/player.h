#pragma once
#include"defines.h"
#include"board.h"

class Player {
private:
	const char name;
	int fleet_size;
	Ship** fleet;
	// Ship creation
	void createFleet();
public:
	// Constructors
	Player(Board* b, char n);
	// Data structurs and pointers
	int* fleet_info;
	List ships_on_board;
	Board* board;
	// Access
	char getName() const { return name; }
	int getSize() const { return fleet_size; }
	Ship* getShip(int type, int idx) { return &fleet[type][idx]; }
	// Ship placement
	void dockShip(Ship* ship,int i);
	void setFleet(int car,int bat,int cru,int des);
	// Destructors
	~Player();
};