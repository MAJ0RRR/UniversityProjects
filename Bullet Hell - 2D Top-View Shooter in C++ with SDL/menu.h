#pragma once
#pragma warning (disable : 26812 )
#include"defines.h"

class Menu {
private:
	Display currently_displaying;
	char text[128];
	SDL_Surface* charset;
	SDL_Surface* screen;
	SDL_Renderer* renderer;
	int black, blue, red, green;
	SDL_Texture* displaying;
	SDL_Rect dimensions;
public:
	Menu(SDL_Surface* scr,SDL_Surface* chset,SDL_Renderer* ren);
	Display getDisplay() { return currently_displaying; }
	void loadMainMenu();
	void loadDeathScreen();
	void handleEvent(SDL_Event& e);
	void render();
	void initColors();
	void setDisplay(Display display) { currently_displaying = display; }
	~Menu() {};
};