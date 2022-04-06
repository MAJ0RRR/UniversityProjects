#include"Fox.h"

Fox::Fox(World* world, Point coordinates) {
	this->name = "Fox";
	this->strength = 3;
	this->initiative = 7;
	this->coordinates = coordinates;
	this->world = world;
}

void Fox::Draw() const {
	printf("F");
}

Point Fox::specialAction(Point target) {
	/* Fox never moves to field that is currently occupied by stronger animal */
	if (this->world->Peek(coordinates, target)) {
		this->world->writeLog(this->getName() + " didn't smell stronger enemy and he decided to move");
		return target;
	}
	else {
		this->world->writeLog(this->getName() + " smelled stronger enemy and he decided to not move");
		return coordinates;
	}
}

Fox::~Fox() {}