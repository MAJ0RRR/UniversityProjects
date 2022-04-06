#pragma once
#include"Animal.h"
class Antelope : public Animal {
public:
	Antelope(World* world,Point coordinates);
	void Draw() const;
	~Antelope();
private:
	action Defend(Organism* attacker);
	action specialCollision();
	Point specialAction(Point target);
};