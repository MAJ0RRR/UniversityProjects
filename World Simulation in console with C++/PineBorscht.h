#pragma once
#include"Plant.h"
class PineBorscht : public Plant {
public:
	PineBorscht(World* world, Point coordinates);
	void Draw() const;
	void Sow();
	~PineBorscht();
private:
	action Defend(Organism* attacker);
	action Effect();
};