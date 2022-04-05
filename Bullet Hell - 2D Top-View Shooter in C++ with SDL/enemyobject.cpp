#pragma warning (disable : 26812 )

#include"enemyobject.h"
#include"texturemanager.h"

EnemyObject::EnemyObject(SDL_Renderer* renderer,Point position) {
	/* Default values set up */
	pos = position;
	bullet_size = DEFAULT_BULLET_SIZE;
	src = { 0,0,ENTITY_SIZE,ENTITY_SIZE };
	src_bullet = { 0,0,bullet_size,bullet_size };
	vel = 0;
	direction = DOWN;
	current_moving_frame = 0;
	shoot_radius = 0;
	special_amount = 0;
	shoot = false;
	hitbox = { pos.x,pos.y,ENTITY_SIZE,ENTITY_SIZE };
	recently_hit = false;
	dead = false;
	current_frame = 0;
	current_animation_frame = 0;
}

void EnemyObject::renderBullets(SDL_Renderer* renderer, int cam_x, int cam_y) {
	modifyBulletsBehavior();
	for (int i = 0; i < bullets_amount; i++) {
		bullets_position[i].x -= cam_x;
		bullets_position[i].y -= cam_y;
		TextureManager::drawTexture(tex_bullet, src_bullet, bullets_position[i], renderer);
		bullets_position[i].x += cam_x;
		bullets_position[i].y += cam_y;
	}
}

void EnemyObject::animate() {
	current_frame++; // Count frames 
	if (current_frame + 1 == animation_frames) { // Load up next animation every 4th frame
		current_animation_frame++; // Increment currently rendered frame 
		if (current_animation_frame == animation_frames) current_animation_frame = 0; // Reset animation cycle
		current_frame = 0; // Reset counter 
	}
}

void EnemyObject::updateBullets(int radius) {
	origin_position.x = pos.x + ENTITY_SIZE / 2;
	origin_position.y = pos.y + ENTITY_SIZE / 2;
	bullets_position[0].x = origin_position.x;
	bullets_position[0].y = origin_position.y - radius - ENTITY_SIZE / 2;
	for (int i = 1; i < bullets_amount; i++) {
		rotate(angle, Point(bullets_position[i - 1].x, bullets_position[i - 1].y), origin_position, bullets_position[i]);
	}
}

void EnemyObject::rotate(double angle, Point prev, Point origin, SDL_Rect& rect) {
	rect.x = cos(angle) * (prev.x - origin.x) - sin(angle) * (prev.y - origin.y) + origin.x;
	rect.y = sin(angle) * (prev.x - origin.x) + cos(angle) * (prev.y - origin.y) + origin.y;
}

void EnemyObject::move() {
	if (current_moving_frame == moving_frames) {
		direction = static_cast<Dir>(rand() % 4); // Randomize direction
		vel = rand() % DEFAULT_ENEMY_SPEED_LIMIT; // Randomize velocity
		switch (direction) {
		case UP: // Adjust velocity according to direction
			vel *= -1;
			break;
		case LEFT:
			vel *= -1;
		}
		current_moving_frame = 0; // Cycle of movement in given direction ends, reset counter
	}
	else { // Still moving
		if (direction == LEFT || direction == RIGHT) pos.x += vel;
		else if (direction == UP || direction == DOWN) pos.y += vel;

		if ((pos.x < 0) || (pos.x + ENTITY_SIZE > LEVEL_WIDTH))
		{
			pos.x -= vel; //Move back
		}
		if ((pos.y < 0) || (pos.y + ENTITY_SIZE > LEVEL_HEIGHT))
		{
			pos.y -= vel; //Move back
		}
		current_moving_frame++; // Update moving frames
	}
	updateHitbox();
}

void EnemyObject::render(SDL_Renderer* renderer, int cam_x, int cam_y) {
	move(); // Move the model
	animate();
	src.x = current_animation_frame * ENTITY_SIZE;
	dest.x = pos.x - cam_x; // Adjust relative to camera
	dest.y = pos.y - cam_y;
	renderBullets(renderer, cam_x, cam_y); // Draw bullets
	TextureManager::drawTexture(tex, src, dest, renderer); // Draw model
	renderSpecial(renderer, cam_x, cam_y); // Draw special projectiles
}

bool EnemyObject::checkCollision(SDL_Rect projectile) {
	if (recently_hit) {
		if (hit_time + HIT_INVICIBILITY_TIME < SDL_GetTicks()) recently_hit = false;
	}
	else {
		SDL_Rect res;
		if (SDL_IntersectRect(&projectile, &hitbox, &res) == SDL_TRUE) { // Check for intersections
			recently_hit = true;
			hit_time = SDL_GetTicks();
			hp--;
			return true;
		}
	}
	return false;
}

void EnemyObject::updateHitbox() {
	hitbox.x = pos.x;
	hitbox.y = pos.y;
}

EnemyObject::~EnemyObject() {
	delete[] bullets_position;
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(tex_bullet);
}