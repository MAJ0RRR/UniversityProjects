#pragma once
#include"Plant.h"
class Grass : public Plant {
public:
	Grass(World* world, Point coordinates);
	void Draw() const;
	void Sow();
	~Grass();
private:
};