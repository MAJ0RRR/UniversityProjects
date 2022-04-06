#pragma warning (disable: 26812 )
#include"Guarana.h"

Guarana::Guarana(World* world, Point coordinates) {
	this->name = "Guarana";
	this->strength = 0;
	this->initiative = 0;
	this->coordinates = coordinates;
	this->world = world;
}

void Guarana::Draw() const {
	printf("%c", 224);
}

action Guarana::Defend(Organism* attacker) {
	attacker->setStrength(attacker->getStrength() + 3);
	this->world->writeLog(attacker->getName() + " ate Guarana and his strength is raised to " + std::to_string(attacker->getStrength()));
	return NO_DEFENCE;
}

void Guarana::Sow() {}

Guarana::~Guarana() {}