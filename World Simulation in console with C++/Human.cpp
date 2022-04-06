#include"Human.h"
#include"CONST.h"

Human::Human(World* world, Point coordinates) {
	this->name = "Human";
	this->strength = 5;
	this->initiative = 4;
	this->active = false;
	this->cooldown = 0;
	this->duration = 0;
	this->coordinates = coordinates;
	this->world = world;
}

Point Human::Move() {
	/* Player moves by using arrows */
	Point move = this->getCoordinates();
	printf("\n\n WAITING FOR HUMAN PLAYER...\n\n");
	int c = 0;
	while (c = _getch()) {
		if (c == 'q') {
			if (cooldown <= 0 && !active) {
				magicElixir(true);
				this->world->writeLog("Elixir is activated");
			}
			break;
		}
		else {
			if (c == UP) {
				move.x--;
			}
			else if (c == DOWN) {
				move.x++;
			}
			else if (c == RIGHT) {
				move.y++;
			}
			else if (c == LEFT) {
				move.y--;
			}
			else {
				continue;
			}
		}
		if (cooldown > 0 && !active) this->cooldown--;
		if ((move.x < this->world->getWidth() && move.x >= 0) && (move.y < this->world->getHeight() && move.y >= 0)) { // In bounds
			return move;
		}
		return coordinates;
	}
	return coordinates;
}

Point Human::Action() {
	magicElixir(false);
	Point target = this->Move();
	return target;
}

void Human::Draw() const {
	printf("H");
}

void Human::magicElixir(bool use) {
	/* Special Ability */
	if (active && !use && duration > 0) {
		this->duration--;
		if (strength >= 5) {
			this->strength--;
			this->world->writeLog("Elixir will last for " + std::to_string(duration) + " turns");
		}
	}
	else if (use && !active && cooldown <= 0) {
		this->strength = 10;
		this->duration = 5;
		this->active = true;
	}
	else if (cooldown == 0 && active && !use) {
		this->world->writeLog("Elixir duration ended");
		this->cooldown = 5;
		this->active = false;
	}
}

Human::~Human() {}