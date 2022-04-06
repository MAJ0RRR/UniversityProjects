#pragma once
#include"Animal.h"
class Fox : public Animal {
public:
	Fox(World* world,Point coordinates);
	void Draw() const;
	~Fox();
private:
	Point specialAction(Point Target);
};