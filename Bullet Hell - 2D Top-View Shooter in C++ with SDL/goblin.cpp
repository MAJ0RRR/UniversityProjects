#pragma warning (disable : 26812 )

#include"goblin.h"
#include"texturemanager.h"

void Goblin::initTextures( SDL_Renderer* renderer) {
	// Load textures
	tex = TextureManager::loadTexture("./media/Enemies/goblin.bmp", true, renderer);
	tex_bullet = TextureManager::loadTexture("./media/Enemies/bullet_goblin.bmp", false, renderer);
	tex_mega_bullet = TextureManager::loadTexture("./media/Enemies/tornado.bmp", true, renderer);
	// Set up render point for model
	dest = { pos.x,pos.y,ENTITY_SIZE,ENTITY_SIZE };
	// Animation and movement config
	moving_frames = goblin_moving_frames;
}

void Goblin::modifyBulletsBehavior() {
	megaShoot();
	if (!shoot) { // If not shooting -> shoot
		shoot_start = SDL_GetTicks();
		shoot = true;
	}
	if (shoot_start + shooting_time > SDL_GetTicks() && shoot) { // While shooting
		angle += angle_increase; // rotation of bullets 
		shoot_radius += radius_increase; // move bullets futher from center
	}
	else { // After phase of shooting ended
		shoot = false;
		shoot_radius = 0; // move bullets back to center 
	}
	updateBullets(shoot_radius);
}

void Goblin::initBullets() {
	type = GOBLIN;
	hp = hp_amount;
	// Determine angle between every other bullet 
	angle = M_PI / (bullets_amount / 2);
	// Allocation of memory for bullets
	bullets_amount = DEFAULT_AMMO_CAP;
	bullets_position = new SDL_Rect[bullets_amount];
	// Initialize arrays of bullets with placeholder values
	for (int i = 0; i < bullets_amount; i++) {
		bullets_position[i] = { 0,0,bullet_size,bullet_size };
	}
	// Special ability initialization
	megaBullet_src = { 0,0,megaBullet_size,megaBullet_size };
	mega_shoot_radius = 0;
	mega_shoot_start = SDL_GetTicks();
	mega_shoot = true;
	mega_bullet_dir = DOWN;
	special_amount = special_bullets_amount;
	// Create bullets in center of medl
	updateBullets(0);
}

void Goblin::megaShoot() {
	if (mega_shoot_start + mega_shooting_time > SDL_GetTicks() && mega_shoot) { // While special ability is active
		special_amount = 1;
		mega_shoot_radius += mega_shoot_radius_increase;
		moveMegaBullet();
		if (mega_shoot_radius == mega_shoot_radius_cap) mega_shoot_radius = 0;
	}
	else if (!mega_shoot) { // After special ability ends
		mega_shoot = false;
		if (mega_shoot_start + mega_shooting_time + megaBullet_delay < SDL_GetTicks()) { // Set up ability to be used again
			resetMegaBullet();
			special_amount = 1;
			mega_shoot = true;
			mega_shoot_start = SDL_GetTicks();
			mega_bullet_dir = direction;
		}
	}
	else mega_shoot = false;
}

void Goblin::resetMegaBullet() {
	megaBullet_pos = { pos.x,pos.y,megaBullet_size,megaBullet_size };
}

void Goblin::moveMegaBullet() {
	switch (mega_bullet_dir) { 
	case UP:
		megaBullet_pos.y -= mega_shoot_radius_increase;
		break;
	case DOWN:
		megaBullet_pos.y += mega_shoot_radius_increase;
		break;
	case LEFT:
		megaBullet_pos.x -= mega_shoot_radius_increase;
		break;
	case RIGHT:
		megaBullet_pos.x += mega_shoot_radius_increase;
		break;
	}
}

void Goblin::renderSpecial(SDL_Renderer* renderer, int cam_x, int cam_y) {
	if (mega_shoot) {
		megaBullet_pos.x -= cam_x;
		megaBullet_pos.y -= cam_y;
		TextureManager::drawTexture(tex_mega_bullet, megaBullet_src, megaBullet_pos, renderer);
		megaBullet_pos.x += cam_x;
		megaBullet_pos.y += cam_y;
	}
}

SDL_Rect* Goblin::getSpecial() {
	return &megaBullet_pos;
}

void Goblin::clean() {
	SDL_DestroyTexture(tex_mega_bullet);
}

