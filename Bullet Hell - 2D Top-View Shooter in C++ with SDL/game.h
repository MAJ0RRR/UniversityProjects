#pragma once
#include"defines.h"
#include"player.h"
#include"map.h"
#include"goblin.h"
#include"demon.h"
#include"enemyobject.h"
#include"guard.h"
#include"menu.h"

class Game {
private:
	/* SDL */
	SDL_Window* window;				
	SDL_Surface* screen;			
	SDL_Renderer* renderer;			
	SDL_Event event;				
	SDL_Surface* charset;			
	SDL_Texture* info;	
	/* Viewport */
	SDL_Rect camera;				
	/* Pointers to entities */
	Player* player;							
	Map* map;						
	EnemyObject** enemies;
	/* Info */
	SDL_Texture* grade;
	SDL_Rect grade_src;
	SDL_Rect grade_dest;
	void changeGrade();
	int goblins;
	int demons;
	int guards;
	int enemies_count;
	Uint32 world_time;
	bool quit;										// Quit flag
	bool new_game;									// New game flag
	/* Utility */
	int black, green, red, blue;					// Colors for drawing 
	int player_points;
	double multipier;
	/* Errors */
	void handleErrorLoading();
	/* Render */
	void updateCamera();							// Adjust viewport
	void printInfo();								// Print info bar at top of the screen
	/* Loading */
	SDL_Surface* loadSurface(const char* path);		// Load BMP
	/* Menu */
	void newGame();
	/* Handle creation and deletion of entities */
	void spawnEnemies();							// Spawn enemies for given level
	void killEnemies();								// Kill all enemies
	void killEnemy(int idx);						// Kill specific enemy
	bool gameOver();								// If all enemies are dead , game over
	/* Menu */
	Menu* menu;
	Display display;
	void destroyMenu(Display new_display);
	void throwDeathScreen();
	Level current_lvl;
	bool isLevelCleared();
	void initNextLevel();
public:
	Game();
	/* Getters */
	bool isRunning() { return quit; }
	/* Setters */
	void setTime(int t);
	/* Game loop utility */
	void handleEvents();
	void update();
	void render();
	~Game();
	/* Default drawing functions */
	static void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
	static void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	static void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	static void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	static void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	/* Menu */
	Display getDisplay() { return display; }
};