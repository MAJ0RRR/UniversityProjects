#include"player.h"

// Default Player constructor, allocate space for fleet, ships will be added on placement
Player::Player(Board* b, char n) : name(n), fleet_size(DEFAULT_FLEET_SIZE),ships_on_board(List()), board(b) {
	fleet_info = new int[SHIP_TYPES];
	fleet_info[0] = DEFAULT_CAR_AMOUNT;
	fleet_info[1] = DEFAULT_BAT_AMOUNT;
	fleet_info[2] = DEFAULT_CRU_AMOUNT;
	fleet_info[3] = DEFAULT_DES_AMOUNT;

	fleet = new Ship * [SHIP_TYPES];
	for (int i = 0; i < SHIP_TYPES; i++) fleet[i] = new Ship[fleet_info[i]];
	createFleet();
}

// Create Player's fleet based on fleet_info
void Player::createFleet() {
	// Carriers
	for (int i = 0; i < fleet_info[0]; i++) fleet[0][i] = board->assembleShip("CAR", -1, -1, Direction::NONE);
	// Battleships
	for (int i = 0; i < fleet_info[1]; i++) fleet[1][i] = board->assembleShip("BAT", -1, -1, Direction::NONE);
	// Crusiers
	for (int i = 0; i < fleet_info[2]; i++) fleet[2][i] = board->assembleShip("CRU", -1, -1, Direction::NONE);
	// Destroyers
	for (int i = 0; i < fleet_info[3]; i++) fleet[3][i] = board->assembleShip("DES", -1, -1, Direction::NONE);
}

// Mark ship as placed and push it to list
void Player::dockShip(Ship* ship,int i) {
	int type = board->typeToIdx(ship->type);
	if (type != -1) {
		fleet[type][i].placed = true;
		ships_on_board.push_back(ship);
	}
}

// Used to create fleet for custom set values of ships
void Player::setFleet(int car, int bat, int cru, int des) {
	fleet_info[0] = car;
	fleet_info[1] = bat;
	fleet_info[2] = cru;
	fleet_info[3] = des;
	fleet_size = car + bat + cru + des;
	// Delete Default sizeed fleets
	for (int i = 0; i < SHIP_TYPES; i++) delete[] fleet[i];
	// Allocate space for custom fleet
	for (int i = 0; i < SHIP_TYPES; i++) fleet[i] = new Ship[fleet_info[i]];
	createFleet();
}

Player::~Player() {
	for (int i = 0; i < SHIP_TYPES; i++) {
		delete[] fleet[i];
	}
	delete[] fleet;
	delete[] fleet_info;
};