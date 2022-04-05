#include"map.h"
#include"texturemanager.h"

Map::Map(SDL_Renderer* renderer) {
	// Load textures
	floor = TextureManager::loadTexture("./media/Map/floor.bmp",false,renderer);
	rows = LEVEL_HEIGHT / TILE_SIZE;
	cols = LEVEL_WIDTH / TILE_SIZE;
	floor_type = new int* [rows];
	for (int i = 0; i < rows; i++) {
		floor_type[i] = new int[cols];
	}
	srand(time(NULL)); 	// Randomize floor
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			floor_type[i][j] = rand() % 3;
		}
	}
	// Set up render properties
	dest = { 0,0,TILE_SIZE,TILE_SIZE };
	src = { 0,0,TILE_SIZE,TILE_SIZE };
}

void Map::render(SDL_Renderer* renderer, int cam_x, int cam_y) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			dest.x = j * TILE_SIZE - cam_x;
			dest.y = i * TILE_SIZE - cam_y;
			src.x = floor_type[i][j] * TILE_SIZE;
			TextureManager::drawTexture(floor, src, dest, renderer);
		}
	}
}

Map::~Map() {
	SDL_DestroyTexture(floor);
	for (int i = 0; i < rows; i++) {
		delete[] floor_type[i];
	}
	delete[] floor_type;
}
