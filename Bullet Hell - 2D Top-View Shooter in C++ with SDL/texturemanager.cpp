#include"texturemanager.h"

SDL_Texture* TextureManager::loadTexture(const char* path, bool transparent, SDL_Renderer* renderer) {
	SDL_Surface* tmp = SDL_LoadBMP(path);
	if (transparent == true) { // If transparent texture is wanted 
		SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 255, 255));
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}

void TextureManager::drawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,SDL_Renderer* renderer) {
	if (tex != NULL) SDL_RenderCopy(renderer, tex, &src, &dest);
}