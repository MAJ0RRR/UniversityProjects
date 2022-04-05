#pragma warning (disable : 26812 )

#include"demon.h"
#include"texturemanager.h"

void Demon::initTextures( SDL_Renderer* renderer) {
	/* Load textures */
	tex = TextureManager::loadTexture("./media/Enemies/demon.bmp", true, renderer);
	tex_bullet = TextureManager::loadTexture("./media/Enemies/bullet_demon.bmp", false, renderer);
	/* Animation and movement config */
	dest = { pos.x,pos.y,ENTITY_SIZE,ENTITY_SIZE };
	moving_frames = demon_moving_frames;
}

void Demon::updateExplosion(int radius) {
	// For rendering
	explosion_bullets_ren[0].x = explosion_origin.x;
	explosion_bullets_ren[0].y = explosion_origin.y - radius - explosion_bullets_size;
	// For collision
	for (int i = 1; i < explosion_bullets_amount; i++) {
		rotate(explosion_angle, Point(explosion_bullets_ren[i - 1].x, explosion_bullets_ren[i - 1].y),
			   explosion_origin, explosion_bullets_ren[i]);
	}
}

void Demon::modifyBulletsBehavior() {
	if (exploding) {
		if (explosion_start + 1000 > SDL_GetTicks()) {
			explosion_radius += explosion_radius_increase;
			updateExplosion(explosion_radius);
		}
		else {
			calculateExplosionOrigin();
			exploding = false;
		}
	}
	if (!shoot) { // If not shooting -> shoot
		shoot_start = SDL_GetTicks();
		shoot = true;
		bullet_size++; // Every time Demon shoots it makes his bullets bigger
		for (int i = 0; i < bullets_amount; i++) { 
			bullets_position[i].w++;
			bullets_position[i].h++;
		}
		if (bullet_size == bullet_size_cap) { // If bullet achive their cap reset it back to normal size once again
			bullet_size = DEFAULT_BULLET_SIZE;
			for (int i = 0; i < bullets_amount; i++) {
				bullets_position[i].w = DEFAULT_BULLET_SIZE;
				bullets_position[i].h = DEFAULT_BULLET_SIZE;
			}
		}
	}
	if (shoot_start + shooting_time > SDL_GetTicks()){ // While shooting
		shoot_radius += radius_increase;
		updateBullets(shoot_radius);
	}
	else { // After phase of shooting ended
		if (!exploding) {
			explosion_start = SDL_GetTicks();
			explosion_radius = 0;
			exploding = true;
		}
		shoot_radius = 0;
		shoot = false;
	}
}


void Demon::renderSpecial(SDL_Renderer* renderer, int cam_x, int cam_y) {
	if (exploding) {
		for (int i = 0; i < explosion_bullets_amount; i++) {
			explosion_bullets_ren[i].x -= cam_x; // Subtract offset
			explosion_bullets_ren[i].y -= cam_y;
			TextureManager::drawTexture(tex_bullet, src_bullet, explosion_bullets_ren[i], renderer);
			explosion_bullets_ren[i].x += cam_x; // Add offset
			explosion_bullets_ren[i].y += cam_y;
		}
	}
}

void Demon::initBullets() {
	type = DEMON;
	hp = hp_amount;
	bullets_amount = DEFAULT_AMMO_CAP;
	angle = M_PI / (bullets_amount / 2);
	bullets_position = new SDL_Rect[bullets_amount];
	for (int i = 0; i < bullets_amount; i++) {
		bullets_position[i] = { 0,0,bullet_size,bullet_size };
	}
	/* Special ability initialization */
	explosion_bullets_ren = new SDL_Rect[explosion_bullets_amount];
	for (int i = 0; i < explosion_bullets_amount; i++) {
		explosion_bullets_ren[i] = { 0,0,explosion_bullets_size,explosion_bullets_size };
	}
	special_amount = explosion_bullets_amount;
	explosion_radius = 0;
	exploding = false;
	shoot_radius = shooting_radius_cap;
	updateBullets(0);
	calculateExplosionOrigin();
}

void Demon::calculateExplosionOrigin() {
	explosion_origin.x = origin_position.x;
	explosion_origin.y = origin_position.y - shooting_radius_cap;
}

SDL_Rect* Demon::getSpecial() {
	return explosion_bullets_ren;
}

void Demon::clean() {
	delete[] explosion_bullets_ren;
}

