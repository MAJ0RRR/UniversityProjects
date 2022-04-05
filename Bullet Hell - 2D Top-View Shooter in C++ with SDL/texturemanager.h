#pragma once
#include"defines.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* path, bool transparent, SDL_Renderer* renderer);         // Load texture
	static void drawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer);      // Render texture
};