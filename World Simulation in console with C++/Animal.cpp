#pragma warning (disable: 26812)
#include"Animal.h"

Point Animal::Move() {
	/* Default move procedure for an animal. Animal can go NORTH,EAST,SOUTH OR WEST if move is in bounds of world return
	coordinats of point where Animal want to move */
	bool made_valid_move = false;
	Point position;

	while (!made_valid_move){
		position = coordinates;
		int move = rand() % 4;
		switch (move) {
		case NORTH:
			position.y--;
			break;
		case EAST:
			position.x++;
			break;
		case SOUTH:
			position.y++;
			break;
		case WEST:
			position.x--;
			break;
		}
		if ((position.x < this->world->getWidth() && position.x >= 0) && (position.y < this->world->getHeight() && position.y >= 0)) { // In bounds
			made_valid_move = true;
		}
	}
	this->world->writeLog(this->getName() + " wants to move on field " +"("+ std::to_string(position.x) +","+ std::to_string(position.y)+")");
	return position;
}

action Animal::Collision(Organism* attacker,Organism* defender) {
	/* Default Animal collision for an animal */
	if (attacker == this) {
		return Attack(defender);
	}
	else {
		return Defend(attacker);
	}
}

action Animal::Attack(Organism* defender) {
	/* Decide collision between two organisms, return true if attacker wins and false if he loses */
	if (!this->getName().compare(defender->getName())) {
		this->world->writeLog(this->getName() + " decided to reproduce");
		return REPRODUCED;
	}
	if (this->getStrength() > defender->getStrength()) { // Attacker is stronger, he wins 
		return KILLED;
	}
	else if (this->getStrength() == defender->getStrength()) {
		if (this->getAge() > defender->getAge()) { // Attacker is older, he wins
			return KILLED;
		}
		return DIED; // Attacker is younger, he dies
	}
	else { // Attacker is weaker,he dies
		return DIED;
	}
	return KILLED; // All stats are equal, attacker wins
}

action Animal::Defend(Organism* attacker) {
	/* By default Animal has no special defence mechanism */
	this->world->writeLog(this->getName() + " is being attacked by " + attacker->getName() + ".It has no special defence!");
	return NO_DEFENCE;
}


action Animal::specialCollision() {
	/* By defualt no special modifier during collision */
	return NO_DEFENCE;
}

void Animal::Reproduce(Organism* partner) {
	/* */
}

Point Animal::Action() {
	/* All actions made by an animal in given turn, by default it is move and age */
	this->Age();
	Point target = this->Move();
	return specialAction(target);
}

Point Animal::specialAction(Point target) {
	/* By default no special modifier during action */
	this->world->writeLog(this->getName() + " is moving towards " + "(" + std::to_string(target.x) + "," + std::to_string(target.y) + ")");
	return target;
}

void Animal::Age() {
	this->age++;
}

