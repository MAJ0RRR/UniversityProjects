#pragma once
#include"Plant.h"
class Guarana : public Plant {
public:
	Guarana(World* world, Point coordinates);
	void Draw() const;
	void Sow();
	~Guarana();
private:
	action Defend(Organism* attacker);
};