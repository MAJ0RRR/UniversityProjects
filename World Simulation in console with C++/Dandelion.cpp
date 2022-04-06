#include"Dandelion.h"

Dandelion::Dandelion(World* world, Point coordinates) {
	this->name = "Dandelion";
	this->strength = 0;
	this->initiative = 0;
	this->coordinates = coordinates;
	this->world = world;
}

void Dandelion::Draw() const {
	printf("%c", 153);
}

void Dandelion::Sow() {}

Dandelion::~Dandelion() {}