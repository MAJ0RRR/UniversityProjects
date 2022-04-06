#include"Grass.h"

Grass::Grass(World* world, Point coordinates) {
	this->name = "Grass";
	this->strength = 0;
	this->initiative = 0;
	this->coordinates = coordinates;
	this->world = world;
}

void Grass::Draw() const {
	printf("%c",176);
}

void Grass::Sow() {}

Grass::~Grass() {}