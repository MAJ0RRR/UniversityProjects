#pragma once
#include"defines.h"

class EnemyObject {
protected:
	EnemyType type;																// Which enemy is it
	Point pos;																	// Position 
	int vel;																	// Velocity
	Dir direction;																// Direction model is facing
	int current_moving_frame;													// Counter for frame of movement
	int moving_frames;															// How many frames model go in one direction
	int bullet_size;															// Size of bullets model shoots
	int bullets_amount;															// How many bullets does the moode have
	int special_amount;															// Amount of special projectiles
	int shoot_radius;															// How far does bullets go
	double angle;																// Angle between every othe bullet
	unsigned int shoot_start;													// Saving time stamp of shoot start
	bool shoot;																	// Flag if model is shooting
	Point origin_render;														// Point that bullets go around on screen
	Point origin_position;														// Point that bullets go around on level
	SDL_Texture* tex_bullet;													// Texture for model
	SDL_Texture* tex;															// Texture for model
	SDL_Rect dest;																// Place to render
	SDL_Rect src;																// Frame to render for model
	SDL_Rect src_bullet;														// Frame to render for bullet
	SDL_Rect* bullets_position;													// Info about bullets real position on level
	SDL_Rect hitbox;															// Enemy model hitbox
	int hp;																		// Amount of hits model can take before dying
	bool recently_hit;
	unsigned int hit_time;
	bool dead;
	int current_frame;
	int current_animation_frame;
	// Virtual methods
	virtual void modifyBulletsBehavior() = 0;									// Custom bullet behavior
	virtual void initTextures(SDL_Renderer* renderer) = 0;						// Load custom textures
	virtual void initBullets() = 0;												// Initialize model bullet's
	virtual void renderSpecial(SDL_Renderer* renderer,							// Render special ability projectiles
		                       int cam_x, int cam_y) = 0; 
	// Common methods
	void renderBullets(SDL_Renderer* renderer, int cam_x, int cam_y);			// Draw model bullets on screen
	void updateBullets(int radius);												// Move bullets
	void rotate(double angle, Point prev, Point origin, SDL_Rect& rect);		// Rotate bullets by given angle around origin
	void move();																// handle model's movement 
	void updateHitbox();
	void animate();
	const int animation_frames = 4;
public:
	EnemyObject(SDL_Renderer* renderer, Point position);
	void render(SDL_Renderer* renderer, int cam_x, int cam_y);					// Draw everything related to model
	bool checkCollision(SDL_Rect projectile);									// Check if hit
	/* Setters */
	void setDead() { dead = true; }
	/* Getters */
	bool isDead() { return dead; }
	int getHP() { return hp; }
	EnemyType getType() {return type;}
	unsigned int getHitTime() { return hit_time; }
	SDL_Rect* getBullets() { return bullets_position; }							
	int getBulletsAmount() { return bullets_amount; }								
	virtual SDL_Rect* getSpecial() = 0;											// Return special projectiles
	int getSpecialAmount() { return special_amount; }
	~EnemyObject();
};