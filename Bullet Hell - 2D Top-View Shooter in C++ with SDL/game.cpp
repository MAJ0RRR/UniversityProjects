#pragma warning (disable : 6386 )
#include"game.h"
#include"texturemanager.h"

/* Initialize everything */
Game::Game() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		exit(1);
	}
	else {
		// Initialize Window and Renderer 
		int rc;
		rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
			&window, &renderer);

		// Check errors while Initializing window and renderer
		if (rc != 0) {
			SDL_Quit();
			printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
			exit(1);
		};
	}
	// Initialize Render Color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);							
	// Setting Window Title
	SDL_SetWindowTitle(window, "Bullet Hell by Sebastian Lesniewski 184711");
	// Initialize screen
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	// Turn off mouse cursor
	SDL_ShowCursor(SDL_DISABLE);
	// Load charset
	charset = loadSurface("./media/Menu/cs8x8.bmp");
	SDL_SetColorKey(charset, true, 0x000000); 
	// Set up flags
	quit = false;
	new_game = false;
	// Load colors
	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	// Create a player
	player = new Player(renderer);
	// Set up camera
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// Create a map
	map = new Map(renderer);
	// Spawn enemies
	enemies_count = DEFAULT_ENEMIES_COUNT;
	enemies_count = goblins = DEFAULT_ENEMIES_COUNT;;
	demons = guards = 0;
	spawnEnemies();
	// Menu initialization
	display = GAME;
	/* Other */
	current_lvl = LEVEL_ONE;
	multipier = 1;
	player_points = 0;
	grade = TextureManager::loadTexture("./media/Menu/grades.bmp",true,renderer);
	grade_src = { 64,0,TILE_SIZE,TILE_SIZE }; // Start from C
	grade_dest = { INFO_WINDOW_X - 50, INFO_WINDOW_Y+20,TILE_SIZE,TILE_SIZE };
}

void Game::DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

void Game::DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void Game::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

void Game::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

void Game::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

SDL_Surface* Game::loadSurface(const char* path) {
	SDL_Surface* optimized = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(path);
	if (surface == NULL) {
		handleErrorLoading();
	}
	else {
		optimized = SDL_ConvertSurface(surface, screen->format, 0);
		if (optimized == NULL)
		{
			handleErrorLoading();
		}
		SDL_FreeSurface(surface);
	}
	return optimized;
}

void Game::handleErrorLoading() {
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	exit(1);
}

void Game::handleEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) { // Quit
				quit = true;
				break;
			}
			else if (event.key.keysym.sym == SDLK_n) { // New Game
				if (display != GAME) destroyMenu(GAME);
				killEnemies();
				// LEVEL ONE DEFAULT
				if (current_lvl == LEVEL_ONE) {
					enemies_count = goblins = 3;
					demons = guards = 0;
				}
				newGame();
				break;
			}
			else if (event.key.keysym.sym == SDLK_1) { // Level 1
				enemies_count = goblins = 3;
				demons = guards = 0;
				current_lvl = LEVEL_ONE;
				break;
			}
			else if (event.key.keysym.sym == SDLK_2) { // Level 2
				enemies_count = demons = 3;
				goblins = guards = 0;
				current_lvl = LEVEL_TWO;
				break;
			}
			else if (event.key.keysym.sym == SDLK_3) { // Level 3
				enemies_count = guards = 3;
				goblins = demons = 0;
				current_lvl = LEVEL_THREE;
				break;
			}
			else if (event.key.keysym.sym == SDLK_m) { // Enter menu
				if (display != GAME) destroyMenu(MAIN_MENU);
				menu = new Menu(screen, charset, renderer);
				menu->setDisplay(MAIN_MENU);
				display = MAIN_MENU;
				break;
			}
			else if (event.key.keysym.sym == SDLK_e) { // Exit menu
				menu->setDisplay(GAME);
				destroyMenu(GAME);
				break;
			}
			else if (event.key.keysym.sym == SDLK_x && isLevelCleared()) { // Next Level
				initNextLevel();
				break;
			}
		}
		// Display
		switch (display) {
		case GAME:
			player->handleEvent(event); // handle Player's movement
			break;
		case MAIN_MENU:
			menu->handleEvent(event); // handle player's interaction in menu
			break;
		}
	}
}

void Game::changeGrade() {
	if (player_points <= 0 ) grade_src.x = 64;
	if (player_points > 500) grade_src.x = 32;
	if (player_points > 1000) grade_src.x = 0;
}

void Game::initNextLevel() {
	killEnemies();
	switch (current_lvl) { 
	case LEVEL_ONE: // LOAD LEVEL 2
		demons = enemies_count = 3;
		goblins = guards = 0;
		current_lvl = LEVEL_TWO;
		break;
	case LEVEL_TWO: // LOAD LEVEL 3
		guards = enemies_count = 3;
		demons = goblins = 0;
		current_lvl = LEVEL_THREE;
		break;
	case LEVEL_THREE: // LOAD LEVEL 1 ONCE AGAIN
		goblins = enemies_count = 3;
		demons = guards = 0;
		current_lvl = LEVEL_ONE;
		break;
	}
	newGame();
}

void Game::destroyMenu(Display new_display) {
	display = new_display;
	SDL_FreeSurface(screen);
	screen = nullptr;
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	delete menu;
	menu = nullptr;
}

void Game::update() {
	switch (display) {
	case GAME:
		printInfo();
		player->move();
		for (int i = 0; i < enemies_count; i++) { // Handle interaction between player and enemies
			if (!enemies[i]->isDead()) {
				if (player->handleCollsiion(enemies[i]->getBullets(), enemies[i]->getBulletsAmount())) {
					multipier = 1;
					player_points -= POINTS_FOR_HIT * multipier;
				}
				if (enemies[i]->checkCollision(player->getBullet())) {
					player_points += POINTS_FOR_HIT * multipier;
					multipier += 0.1;
				}
				if (enemies[i]->getHP() == 0) killEnemy(i);
				if (enemies[i]->getSpecialAmount() != 0) {
					player->handleCollsiion(enemies[i]->getSpecial(), enemies[i]->getSpecialAmount());
				}
			}
		}
		updateCamera();
		changeGrade();
		if (gameOver() && display != DEATH_SCREEN) {
			throwDeathScreen();
		}
		break;
	case MAIN_MENU:
		break;
	case DEATH_SCREEN:
		break;
	}
}

void Game::throwDeathScreen() {
	player_points = 0;
	menu = new Menu(screen, charset, renderer);
	menu->setDisplay(DEATH_SCREEN);
	display = DEATH_SCREEN;
}

void Game::render() {
	SDL_RenderClear(renderer); // Clear the screen
	switch (display) {
	case MAIN_MENU:
		menu->render();
		break;
	case DEATH_SCREEN:
		menu->render();
		break;
	case GAME:
		map->render(renderer, camera.x, camera.y); // Render map
		for (int i = 0; i < enemies_count; i++) { // Render enemies
			if (!enemies[i]->isDead()) {
				enemies[i]->render(renderer, camera.x, camera.y);
			}
		}
		player->render(renderer, camera.x, camera.y); // Render player
		TextureManager::drawTexture(grade, grade_src, grade_dest, renderer);
		SDL_RenderCopy(renderer, info, NULL, NULL);
		SDL_DestroyTexture(info);
		break;
	}
	SDL_RenderPresent(renderer);
}

void Game::spawnEnemies() {
	enemies = new EnemyObject * [enemies_count];
	int created = 0;
	Point placement;
	for (int i = 0; i < goblins; i++) { // Create Goblins
		placement.x = rand() % LEVEL_WIDTH;
		placement.y = rand() % LEVEL_HEIGHT;
		enemies[created] = new Goblin(renderer,placement);
		created++;
	}
	for (int i = 0; i < demons; i++) { // Create demons
		placement.x = rand() % LEVEL_WIDTH/2;
		placement.y = rand() % LEVEL_HEIGHT/2;
		enemies[created] = new Demon(renderer, placement);
		created++;
	}
	for (int i = 0; i < guards; i++) { // Create guards
		placement.x = rand() % LEVEL_WIDTH / 2 + LEVEL_WIDTH/4;
		placement.y = rand() % LEVEL_HEIGHT / 2 + LEVEL_HEIGHT/4;
		enemies[created] = new Guard(renderer, placement);
		created++;
	}
}

bool Game::isLevelCleared() {
	switch (current_lvl) {
	case LEVEL_ONE:
		if (goblins == 0) {
			return true;
		}
		break;
	case LEVEL_TWO:
		if (demons == 0) {
			return true;
		}
		break;
	case LEVEL_THREE:
		if (guards == 0) {
			return true;
		}
		break;
	}
	return false;
}

void Game::updateCamera()
{
	camera.x = (player->getX() + ENTITY_SIZE / 2) - SCREEN_WIDTH / 2;
	camera.y = (player->getY() + ENTITY_SIZE / 2) - SCREEN_HEIGHT / 2;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > LEVEL_WIDTH - SCREEN_WIDTH) camera.x = LEVEL_WIDTH - SCREEN_WIDTH;
	if (camera.y > LEVEL_HEIGHT - SCREEN_HEIGHT) camera.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
}

void Game::newGame() {
	delete player;
	delete map;
	player = new Player(renderer);
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	map = new Map(renderer);
	spawnEnemies();
	new_game = true;
}

void Game::killEnemies() {
	for (int i = 0; i < enemies_count; i++) {
		delete enemies[i];
	}
	delete[] enemies;
}

void Game::killEnemy(int idx) {
	switch (enemies[idx]->getType()) {
	case GOBLIN:
		goblins--;
		break;
	case DEMON:
		demons--;
		break;
	case GUARD:
		guards--;
		break;
	}
	enemies[idx]->setDead();
}

void Game::setTime(int t) {
	world_time = t;
}

void Game::printInfo() {
	char text[128];	
	DrawRectangle(screen, INFO_WINDOW_X, INFO_WINDOW_Y, INFO_WINDOW_W, INFOW_WINDOW_H, green, black);
	sprintf(text, "TIME = %.1lfs |  X:%i Y: %i ", world_time/1000.0,player->getX(),player->getY());
	DrawString(screen,INFO_WINDOW_X + 50,INFO_WINDOW_Y+10, text, charset);
	sprintf(text, "POINTS = %i MULTIPLIER = %.1f", player_points,multipier);
	DrawString(screen, INFO_WINDOW_X + 50, INFO_WINDOW_Y + 30, text, charset);
	if (isLevelCleared()) {
		sprintf(text, "YOU CAN GO TO NEXT LEVEL! PRESS X");
		DrawString(screen, INFO_WINDOW_X + 40, INFO_WINDOW_Y + 50, text, charset);
	}
	info = SDL_CreateTextureFromSurface(renderer, screen);
}

bool Game::gameOver() {
	return (player->getHp() == 0);
}

Game::~Game() {
	SDL_DestroyTexture(info);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

