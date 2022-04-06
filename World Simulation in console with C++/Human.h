#pragma once
#include"Animal.h"
class Human : public Animal {
public:
	Human(World* world, Point coordinates);
	Point Move();
	Point Action();
	void Draw() const;
	~Human();
private:
	void magicElixir(bool use);
	bool active;
	int cooldown;
	int duration;
};
