#pragma once
#include"Plant.h"
class Dandelion : public Plant {
public:
	Dandelion(World* world,Point coordinates);
	void Draw() const;
	void Sow();
	~Dandelion();
private:
};