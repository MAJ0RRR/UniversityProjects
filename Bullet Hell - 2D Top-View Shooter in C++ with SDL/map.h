#pragma once
#include"defines.h"

class Map {
private:
	SDL_Texture* floor;													// Sprite with difeerent floor textures
	int rows;															// Amount of tiles in y axis
	int cols;															// Amount of tiles in x axis
	int** floor_type;													// Array holding type of every tile
	SDL_Rect src;														// Frame to render
	SDL_Rect dest;														// Where to render
public:
	Map(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer, int cam_x, int cam_y);
	~Map();
};