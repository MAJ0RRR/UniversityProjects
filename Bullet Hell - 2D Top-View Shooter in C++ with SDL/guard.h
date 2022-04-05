#include"enemyobject.h"

class Guard : public EnemyObject {
private:
	void modifyBulletsBehavior();
	void initTextures(SDL_Renderer* renderer);
	void initBullets();
	void renderSpecial(SDL_Renderer* renderer, int cam_x, int cam_y);
	void clean();
	/* Special ability - highlight a shape on the ground - after a brief delay a character still
	   remaining in the area is hit (2 different shapes) */
	void highlightTerrain();						// Finds closest correct place to highlight and choose randomly shape
	SDL_Texture* tex_highlight_square;				// Texture for highlighting square shape
	SDL_Texture* tex_highlight_line;				// texture for highlighting line shape
	SDL_Texture* current_highlight;					// texture for currently highlighted shape
	SDL_Rect shape_dest;							// Where to render for highlight shape
	SDL_Rect shape_src;								// Frame to render for highlight shape
	unsigned int highlight_start;					// Counter for special ability
	bool highlight;									// flag if ability is active
	bool inRange(int min, int max, int val);		// Checks if there is place next to model to highlight
	/* Stats */
	const unsigned int highlight_delay = 2000;
	const int guard_bullet_size = 16;
	const int guard_moving_frames = 12;
	const int shape_square_size = 64;
	const int shape_line_width = 32;
	const int shape_line_height = 96;
	const int special_bullets_amount = 1;
	const int shoot_radius_cap = 200;
	const int shooting_time = 1500;
	const int shoot_radius_increase = 5;
	const int highlight_time = 1000;
	const int hp_amount = 12;

public:
	SDL_Rect* getSpecial();
	Guard(SDL_Renderer* renderer, Point position) : EnemyObject(renderer, position) {
		initTextures(renderer);
		initBullets();
	}
	~Guard() { clean(); }
};