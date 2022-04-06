#pragma once
#include"Organism.h"
class Animal : public Organism {
public:
	virtual Point Move();
	virtual action Collision(Organism* attacker,Organism* defender);
	void Reproduce(Organism* partner);
	virtual Point Action();
private:
	virtual action Attack(Organism* defender);
	virtual action Defend(Organism* attacker);
	virtual action specialCollision();
	virtual Point specialAction(Point target);
	void Age();
};