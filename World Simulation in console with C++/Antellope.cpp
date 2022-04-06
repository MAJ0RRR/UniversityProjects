#pragma warning (disable: 26812 )
#include"Antelope.h"

Antelope::Antelope(World* world, Point coordinates) {
	this->name = "Antelope";
	this->strength = 4;
	this->initiative = 4;
	this->coordinates = coordinates;
	this->world = world;
}

void Antelope::Draw() const {
	printf("A");
}

action Antelope::Defend(Organism* attacker) {
	/* Antelope defence is trying their specialCollsion */
	this->world->writeLog(this->getName() + "is trying to escape from " + attacker->getName() + "attack!");
	return specialCollision();
}

action Antelope::specialCollision() {
	/* 50% chance to dodge a fight and run away to different free field */
	int chance = rand() % 2;
	if (chance == 0) { // FAILED
		this->world->writeLog(this->getName() + "escape plan failed!");
		return NO_DEFENCE;
	}
	else {
		if (coordinates == this->world->Scan(coordinates)) { // NO_EMPTY FIELD TO RUN AWAY
			this->world->writeLog(this->getName() + "escape plan failed!");
			return NO_DEFENCE;
		}
		else {
			this->world->writeLog(this->getName() + "escape plan succed!");
			return RAN_AWAY; // FOUND EMPTY FIELD
		}
	}
}

Point Antelope::specialAction(Point target) {
	/* Antelope range is doubled */
	Point initial_move = target;
	if (coordinates.x == target.x) {
		if (coordinates.y < target.y) {
			target.y++;
		}
		else {
			target.y--;
		}
	}
	else {
		if (coordinates.x < target.x) {
			target.x++;
		}
		else {
			target.x--;
		}
	}
	if ((target.x >= 0 && target.x < this->world->getWidth()) && (target.y >= 0 && target.y < this->world->getHeight())) {
		this->world->writeLog(this->getName() + " leaped to " +"("+ std::to_string(target.x) +","+ std::to_string(target.y) +")"+ " instead");
		return target;
	}
	return initial_move; // If double range move would end up behind bounds perform initial 1 range move
}

Antelope::~Antelope() {}