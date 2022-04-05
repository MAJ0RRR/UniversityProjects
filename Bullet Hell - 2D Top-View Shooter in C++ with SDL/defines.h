#pragma once
#define _USE_MATH_DEFINES


extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include<math.h>
#include<stdio.h>
#include<string.h>
#include <time.h>     
#include<stdlib.h>

enum Dir { // Direction 
	LEFT,
	RIGHT,
	UP,
	DOWN,
	IDLE
};

enum EnemyType {
	GOBLIN,
	DEMON,
	GUARD
};

enum Display {
	GAME,
	MAIN_MENU,
	DEATH_SCREEN,
};

enum Level {
	LEVEL_ONE,
	LEVEL_TWO,
	LEVEL_THREE
};

struct Point {
	Point() { x = 0; y = 0; }
	Point(int a, int b) { x = a;  y = b; }
	int x;
	int y;
};


#ifdef __cplusplus
extern "C"
#endif

#define SCREEN_WIDTH				640
#define SCREEN_HEIGHT				480
#define ENTITY_SIZE					32
#define DEFAULT_BULLET_SIZE			8
#define PLAYER_VEL					8
#define FPS_CAP						30
#define LEVEL_WIDTH					1280
#define LEVEL_HEIGHT				960
#define TILE_SIZE					32
#define DEFAULT_AMMO_CAP			12
#define DEFAULT_ENEMY_SPEED_LIMIT	3
#define INFO_WINDOW_X				SCREEN_WIDTH/2
#define INFO_WINDOW_Y				6
#define INFO_WINDOW_W				SCREEN_WIDTH/2 -6
#define INFOW_WINDOW_H				SCREEN_HEIGHT/6
#define DEFAULT_ENEMIES_COUNT		3
#define HIT_INVICIBILITY_TIME		200
#define HIT_INVICIBILITY_TIME_PLAYER 2500
#define HP_BAR_RENDER_OFFSET		16
#define POINTS_FOR_HIT				10
