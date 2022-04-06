#include"Organism.h"

Point Organism::getCoordinates() const {
	return coordinates;
}

int Organism::getStrength() const{
	return strength;
}

int Organism::getInitiative() const{
	return initiative;
}

int Organism::getAge() const {
	return age;
}

std::string Organism::getName() const {
	return name;
}

void Organism::setCoordinates(Point new_coordinates) {
	this->coordinates = new_coordinates;
}

void Organism::setStrength(int strength) {
	this->strength = strength;
}

bool Organism::operator>(const Organism& a) const {
	if (initiative == a.initiative) {
		return age > a.age;
	}
	return initiative > a.initiative;
}



