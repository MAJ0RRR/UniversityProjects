#include"enemyobject.h"

class Demon : public EnemyObject {
private:
	void modifyBulletsBehavior();
	void initTextures(SDL_Renderer* renderer);
	void initBullets();
	void renderSpecial(SDL_Renderer* renderer, int cam_x, int cam_y);
	void clean();
	/* Special ability - shoot at a place, when the projectile arrives it explodes, creating a
	   circular pattern of bullets*/
	bool exploding;
	unsigned int explosion_start;
	int explosion_radius;
	Point explosion_origin;
	SDL_Rect* explosion_bullets_ren;
	void updateExplosion(int radius);
	void calculateExplosionOrigin();
	/* Stats */
	const int shooting_radius_cap = 200;
	const int explosion_radius_cap= 100;
	const int explosion_radius_increase = 2;
	const int demon_moving_frames = 8;	
	const int explosion_bullets_amount = 6;
	const int explosion_bullets_size = 4;
	const int shooting_time = 1000;
	const int radius_increase = 5;
	const int bullet_size_cap = 24;
	const int explosion_angle = M_PI / (explosion_bullets_amount / 2);
	const int hp_amount = 10;
public:
	SDL_Rect* getSpecial();
	Demon(SDL_Renderer* renderer,Point position) : EnemyObject(renderer, position) {
		initTextures(renderer);
		initBullets();
	}
	~Demon() { clean(); }
};