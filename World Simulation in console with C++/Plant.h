#pragma once
#include"Organism.h"
class Plant : public Organism {
public:
	virtual Point Action();
	action Collision(Organism* attacker,Organism* defender);
	virtual void Reproduce(Organism* partner);
private:
	virtual action Defend(Organism* attacker);
	virtual action Effect();
};