#pragma once
#include"defines.h"

class Player {
private:
	Point pos;														// Position
	int vel_x, vel_y;												// Velocity
	SDL_Rect src;													// Frame to render
	SDL_Rect dest;													// From where to render
	SDL_Rect hitbox;												// Player's Hitbox
	SDL_Rect bullet_hitbox;											// Bullet's Hitbox
	SDL_Rect bullet_src;											// From where to render
	Dir direction;													// Which direction player is facing
	Dir shooting_direction;											// Last pressed arrow is direction of shooting
	/* Player textures */
	SDL_Texture* tex_left;
	SDL_Texture* tex_right;
	SDL_Texture* tex_up;
	SDL_Texture* tex_down;
	SDL_Texture* current_texture;
	SDL_Texture* bullet_texture_left;
	SDL_Texture* bullet_texture_right;
	SDL_Texture* bullet_texture_up;
	SDL_Texture* bullet_texture_down;
	SDL_Texture* invicibility_tex;
	SDL_Texture* current_bullet_texture;
	SDL_Texture* hearth_tex;
	/* Animation */
	int current_frame;												// Counter for current frame of the game
	int current_animation_frame;									// Which animation frame is currently rendered 
	const int animation_frames = 4;									// How many frames does animation have
	Dir determineDirection(Point old_pos,Point new_pos);			// Encode which direction is player facing
	SDL_Texture* chooseTexture(Dir direction);						// Swap texture based on direction of the player
	void animate();													// Cycle through animation frames
	void shoot();													// Shoot bullet in given diretion
	bool shooting;													// Shooting flag
	void renderShoot(SDL_Renderer* rendere,int cam_x,int cam_y);	// Draw bullet
	unsigned int shooting_start;									// Keep time when the shoot started
	bool moving_and_shooting;										// flag if player is moving while shooting
	int bullet_speed;												// Current speed of bullet
	int hp;
	bool recently_hit;
	unsigned int hit_start;
	SDL_Rect health_bar_dest;
	SDL_Rect health_bar_src;
	/* Stats */
	const int shooting_time = 300;
	const int bullet_size = 32;
	const int bullet_speed_default = 32;
	const int bullet_speed_moving = 40;
	const int hp_amount = 5;
	const int hearth_size = 16;
public:
	Player(SDL_Renderer* renderer);
	/* Draw */
	void render(SDL_Renderer* renderer, int cam_x,int cam_y);
	void renderHealthBar(SDL_Renderer* renderer, int cam_x, int cam_y);
	/* Movement */
	void move();
	void handleEvent(SDL_Event& e);
	/* Getters */
	int getHp() { return hp; }
	int getX() { return pos.x; }
	int getY() { return pos.y; }
	int getVelX() { return vel_x; }
	int getVelY() { return vel_y; }
	SDL_Rect getHitbox() { return hitbox; }
	SDL_Rect getBullet() { return bullet_hitbox; }
	/* Collision */
	bool checkCollision(SDL_Rect* projectiles, int bullets_amount); // Check if player colides with given set of projectiles
	bool handleCollsiion(SDL_Rect* bullets, int bullets_amount);    // Take action if player collide with projectile
	/* Setters */
	void setPosX(int val) { pos.x = val; }
	void setPosY(int val) { pos.y = val; }
	~Player();
};