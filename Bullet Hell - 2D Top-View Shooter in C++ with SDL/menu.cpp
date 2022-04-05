#include"menu.h"
#include"game.h"
#include"texturemanager.h"

Menu::Menu(SDL_Surface* scr,SDL_Surface* chset,SDL_Renderer* ren) {
	renderer = ren;
	screen = scr;
	charset = chset;
	currently_displaying = GAME;
	initColors();
	dimensions = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
}

void Menu::loadMainMenu() {
	Game::DrawRectangle(screen, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, black, black);
	Game::DrawRectangle(screen, SCREEN_WIDTH/4,SCREEN_HEIGHT/4,SCREEN_WIDTH/2,SCREEN_HEIGHT/2, red,black);
	sprintf(text, "MAIN MENU");
	Game::DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 160, text, charset);
	sprintf(text, "START NEW GAME (PRESS N)");
	Game::DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 200, text, charset);
	sprintf(text, "QUIT THE GAME (PRESS ESC)");
	Game::DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 240, text, charset);
	currently_displaying = MAIN_MENU;
	displaying = SDL_CreateTextureFromSurface(renderer, screen);
}

void Menu::loadDeathScreen(){
	Game::DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, black, black);
	Game::DrawRectangle(screen, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, green, blue);
	sprintf(text, "YOU ARE DEAD");
	Game::DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 160, text, charset);
	sprintf(text, "GO TO MAIN MENU (PRESS M)");
	Game::DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 200, text, charset);
	sprintf(text, "QUIT THE GAME (PRESS ESC)");
	Game::DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 240, text, charset);
	currently_displaying = DEATH_SCREEN;
	displaying = SDL_CreateTextureFromSurface(renderer, screen);
}

void Menu::handleEvent(SDL_Event& e) {
}

void Menu::render() {
	switch (currently_displaying) {
	case MAIN_MENU:
		loadMainMenu();
		break;
	case DEATH_SCREEN:
		loadDeathScreen();
		break;
	}
	TextureManager::drawTexture(displaying, dimensions,dimensions,renderer);
	SDL_DestroyTexture(displaying);
}

void Menu::initColors() {
	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
}

