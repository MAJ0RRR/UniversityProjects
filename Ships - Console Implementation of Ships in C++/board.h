#pragma once
#include"defines.h"
class Board {
private:
	int rows;
	int cols;
	Field** fields;
	void initBoard();
	// Data validation
	bool validatePlacement(int min, int max, int x, int y, int dx, int dy, int size); 
	bool inBound(int min, int max, int val);
public:
	// Constructors
	Board();
	Board(int rows_amount, int cols_amount);
	// Utility
	int  typeToIdx(char* type);
	Direction charToDir(char* c);
	void encodeDirection(int* dx, int* dy, Direction dir);
	void calculateBounds(int* min, int* max, const char name) const;
	// Ship placement
	Ship assembleShip(const char* type, int x, int y, Direction dir);
	bool placeShip(Ship* ship,int y,int x,Direction dir,char* ship_class,const char name,int* err_code);
	bool shoot(int y, int x,int* err_code);
	void boundToField(Ship* ship,int x,int y);
	// Info
	void printBoard();
	// Destructors
	~Board();
};
