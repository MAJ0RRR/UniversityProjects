#pragma warning (disable: 26812 )
#include"PineBorscht.h"

PineBorscht::PineBorscht(World* world, Point coordinates) {
	this->name = "Pine Borscht";
	this->strength = 10;
	this->initiative = 0;
	this->coordinates = coordinates;
	this->world = world;
}

void PineBorscht::Draw() const {
	printf("%c", 179);
}

action PineBorscht::Defend(Organism* attacker) {
	return POISONED;
}

action PineBorscht::Effect() {
	/* Kills all nearby animals */
	if (this->world->getOrganism(Point(coordinates.x + 1, coordinates.y)) != nullptr) {
			this->world->writeLog(this->world->getOrganism(Point(coordinates.x+1,coordinates.y))->getName() + " died by standing to close to Pine Borscht");
			this->world->removeOrganism(this->world->getOrganism(Point(coordinates.x + 1, coordinates.y)));
	}
	if (this->world->getOrganism(Point(coordinates.x - 1, coordinates.y)) != nullptr) {
		this->world->writeLog(this->world->getOrganism(Point(coordinates.x - 1, coordinates.y))->getName() + " died by standing to close to Pine Borscht");
			this->world->removeOrganism(this->world->getOrganism(Point(coordinates.x - 1, coordinates.y)));	
	}
	if (this->world->getOrganism(Point(coordinates.x , coordinates.y + 1)) != nullptr) {
		this->world->writeLog(this->world->getOrganism(Point(coordinates.x, coordinates.y+1))->getName() + " died by standing to close to Pine Borscht");
			this->world->removeOrganism(this->world->getOrganism(Point(coordinates.x , coordinates.y + 1)));
	}
	if (this->world->getOrganism(Point(coordinates.x , coordinates.y - 1)) != nullptr) {
		this->world->writeLog(this->world->getOrganism(Point(coordinates.x , coordinates.y-1))->getName() + " died by standing to close to Pine Borscht");
			this->world->removeOrganism(this->world->getOrganism(Point(coordinates.x , coordinates.y - 1)));
	}
	return POISONED;
}

void PineBorscht::Sow() {}

PineBorscht::~PineBorscht() {}