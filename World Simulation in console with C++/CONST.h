#pragma once
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include<vector>
#include<algorithm>
#include<string>
#include<iostream>
#include<Windows.h>
#include<typeinfo>
#include<conio.h>

#define POP_DENSITY 0.1
#define NUMBER_OF_ENTITIES 10
#define WOLF 0
#define SHEEP 1
#define ANTELOPE 2
#define FOX 3
#define TURTLE 4
#define GRASS 5
#define DANDELION 6
#define GUARANA 7
#define WOLF_BERRIES 8
#define PINE_BORSCHT 9
#define HUMAN 10
#define RIGHT 77
#define LEFT 75
#define DOWN 80
#define UP 72
#define ELIXIR 49

enum directions { // enum used for naming directions of movement
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum action { // enum used for deciding what action was performed
	DIED,
	KILLED,
	BLOCKED,
	RAN_AWAY,
	NO_DEFENCE,
	POISONED,
	NONE,
	REPRODUCED
};

typedef struct Point { // Struct used for representing Point coordinates
	Point() {
		this->x = 0;
		this->y = 0;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	bool operator==(const Point& a) const {
		return x == a.x && y == a.y;
	}
	int x;
	int y;
}Point;

