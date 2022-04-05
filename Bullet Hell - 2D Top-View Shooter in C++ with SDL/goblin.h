#include"enemyobject.h"

class Goblin : public EnemyObject {
private:
	void modifyBulletsBehavior();
	void initTextures(SDL_Renderer* renderer);
	void initBullets();
	void renderSpecial(SDL_Renderer* renderer, int cam_x, int cam_y);
	void clean();
	/* Special ability - Projectile of a significantly greater size */
	SDL_Texture* tex_mega_bullet;				// Mega bullet texture
	//SDL_Rect megaBullet_ren;					// Special ability render spot
	SDL_Rect megaBullet_pos;					// Special ability render spot
	SDL_Rect megaBullet_src;					// Special ability sprite 
	Dir mega_bullet_dir;						// Direction where mega bullet is approaching
	unsigned int mega_shoot_start;				// Counter for special ability
	bool mega_shoot;							// Flag if ability is active
	int mega_shoot_radius;						// Current distance from caster for special ability
	void megaShoot();							// Handles timing ofspecial ability 
	void moveMegaBullet();						// Movement of mega bullet
	void resetMegaBullet();						// Reset mega bullet position
	/* Stats */
	const int goblin_moving_frames = 12;
	const int shoot_radius_cap = 150;
	const int megaBullet_size = 96;
	const int megaBullet_delay = 2000;
	const int shooting_time = 1400;
	const int mega_shooting_time = 2000;
	const int radius_increase = 5;
	const int mega_shoot_radius_increase = 10;
	const int special_bullets_amount = 1;
	const int mega_shoot_radius_cap = 400;
	const double angle_increase = 0.01;
	const int hp_amount = 5;
public:
	SDL_Rect* getSpecial();
	Goblin(SDL_Renderer* renderer, Point position) : EnemyObject(renderer,position) {
		initTextures(renderer);
		initBullets();
	}
	~Goblin() { clean(); }
};