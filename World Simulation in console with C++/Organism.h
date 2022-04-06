#pragma once
#include"World.h"
#include"CONST.h"

class World;

class Organism {
public:
	virtual Point Action() = 0;
	virtual action Collision(Organism* attacker,Organism* defender) = 0;
	virtual void Reproduce(Organism* partner) = 0;
	virtual void Draw() const = 0;
	Point getCoordinates() const;
	int getStrength() const;
	int getInitiative() const;
	int getAge() const;
	std::string getName() const;
	void setCoordinates(Point new_coordinates);
	void setStrength(int strength);
	bool operator>(const Organism& a) const;
protected:
	const char* name = "Empty Field";
	int strength = 0;
	int initiative = 0;
	int age = 0;
	Point coordinates = Point();
	World* world = nullptr;
	virtual action Defend(Organism* attacker) = 0;
};