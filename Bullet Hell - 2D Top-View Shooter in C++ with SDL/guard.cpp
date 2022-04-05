#pragma warning (disable : 26812 )

#include"guard.h"
#include"texturemanager.h"

void Guard::initTextures(SDL_Renderer* renderer) {
	/* Load textures*/
	tex = TextureManager::loadTexture("./media/Enemies/knight.bmp", true, renderer);
	tex_bullet = TextureManager::loadTexture("./media/Enemies/knight_bullet.bmp", true, renderer);
	tex_highlight_square = TextureManager::loadTexture("./media/Enemies/bomb.bmp", true, renderer);
	tex_highlight_line = TextureManager::loadTexture("./media/Enemies/flame.bmp", true, renderer);
	/* Animation and movement config */
	dest = { pos.x,pos.y,ENTITY_SIZE,ENTITY_SIZE };
	moving_frames = guard_moving_frames;
}

void Guard::modifyBulletsBehavior() {
	if (!shoot) { // If not shooting -> shoot
		shoot_start = SDL_GetTicks();
		shoot = true;
	}
	if (shoot_start + shooting_time > SDL_GetTicks()) { // While shooting
		shoot_radius += shoot_radius_increase;
		if (shoot_radius == shoot_radius_cap) shoot_radius = 0;
	}
	else { // After phase of shooting ended
		shoot = false;
		shoot_radius = 0;
	}
	updateBullets(shoot_radius);
}

void Guard::initBullets() {
	type = GUARD;
	hp = hp_amount;
	shoot_radius = 0;
	bullet_size = guard_bullet_size;
	src_bullet = { 0,0,bullet_size,bullet_size };
	bullets_amount = DEFAULT_AMMO_CAP;
	bullets_position = new SDL_Rect[bullets_amount];
	angle = M_PI / (bullets_amount - 4 );
	for (int i = 0; i < bullets_amount; i++) {
		bullets_position[i] = { 0,0,bullet_size,bullet_size };
	}
	/* Special ability initialization */
	special_amount = special_bullets_amount;
	highlight = false; // Terrain to highlight isn't choosen yet
	highlight_start = SDL_GetTicks(); // Start of ability 
	updateBullets(0);
}

bool Guard::inRange(int min, int max, int val) {
	return val >= min && val <= max;
}

void Guard::renderSpecial(SDL_Renderer* renderer,int cam_x,int cam_y) {
	if (!highlight) { // If place for higlight isn't choosen, choose it
		shape_src = { 0,0,shape_square_size,shape_square_size };
		highlightTerrain();
		highlight = true;
	}
	if (highlight_start + shooting_time > SDL_GetTicks() && highlight) { // Ability duration
		// Subtract offset
		shape_dest.x -= cam_x;
		shape_dest.y -= cam_y;
		TextureManager::drawTexture(current_highlight, shape_src, shape_dest, renderer);
		// Add offset
		shape_dest.x += cam_x;
		shape_dest.y += cam_y;
		// After 1 sec delay explode bomb
		if (highlight_start + highlight_time < SDL_GetTicks()) {
			special_amount = 1;
			shape_src = { shape_src.w,0,shape_src.w,shape_src.h };
		}
	}
	else { // Special ability duration passed 
		special_amount = 0;
		highlight = false; // Discard previously choosen terrain to highlight
		if (highlight_start + highlight_delay < SDL_GetTicks()) { // If delay time passed use ability again
			highlight_start = SDL_GetTicks();
		}
	}
}

SDL_Rect* Guard::getSpecial() {
	return &shape_dest;
}

void Guard::highlightTerrain() {
	int shape = rand() % 2; // 0 for square and 1 for line
	if (shape == 0) {
		if (inRange(TILE_SIZE, LEVEL_WIDTH - shape_square_size, pos.x) && inRange(0, LEVEL_HEIGHT - shape_square_size, pos.y))
		{ // Make sure he is not near edge
			Point LeftUpper; // left upper point of square that will be highlighted
			LeftUpper.x = pos.x - shape_square_size - TILE_SIZE;
			LeftUpper.y = pos.y;
			while (LeftUpper.x % TILE_SIZE != 0) LeftUpper.x--; // Find closest tile x
			while (LeftUpper.y % TILE_SIZE != 0) LeftUpper.y++; // find closest tile y
			shape_dest = { LeftUpper.x,LeftUpper.y,shape_square_size,shape_square_size }; // update 
			shape_src = { 0,0,shape_square_size,shape_square_size };
			current_highlight = tex_highlight_square;
		}
	}
	else {
		if (inRange(TILE_SIZE, LEVEL_WIDTH - shape_line_width, pos.x) && inRange(0, LEVEL_HEIGHT - shape_line_height, pos.y))
		{ // Make sure he is not near edge
			Point LeftUpper; // left upper point of square that will be highlighted
			LeftUpper.x = pos.x - shape_line_width - TILE_SIZE;
			LeftUpper.y = pos.y;
			while (LeftUpper.x % TILE_SIZE != 0) LeftUpper.x--; // Find closest tile x
			while (LeftUpper.y % TILE_SIZE != 0) LeftUpper.y++; // find closest tile y
			shape_dest = { LeftUpper.x,LeftUpper.y,shape_line_width,shape_line_height }; // update 
			shape_src = { 0,0,shape_line_width,shape_line_height };
			current_highlight = tex_highlight_line;
		}
	}
}

void Guard::clean() {
	SDL_DestroyTexture(tex_highlight_line);
	SDL_DestroyTexture(tex_highlight_square);
}
