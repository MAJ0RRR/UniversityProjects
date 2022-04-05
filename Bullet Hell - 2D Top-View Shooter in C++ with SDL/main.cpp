#include"game.h"

int main(int argc, char** argv) { 
	Game* g = new Game(); // Create game instance
	/* Time/FPS setting up */
	const int frame_delay = 1000 / FPS_CAP; // Ideal duration of frame
	Uint32 frame_start, worldtime = 0;
	int frame_time; // Actual duration of frame
	/* GAME LOOP */
	while (!g->isRunning()) {
		frame_start = SDL_GetTicks(); // Start timer

		g->handleEvents();
		g->update();
		g->render();

		frame_time = SDL_GetTicks() - frame_start; // Calculate how much time has passed 

		if (frame_delay > frame_time) { // If the actual frame took less time than it should then delay it
			SDL_Delay(frame_delay - frame_time); 
		}
		if (g->getDisplay() == GAME) {
			worldtime += SDL_GetTicks() - frame_start; // Calculate time 
			g->setTime(worldtime);
		}
	}
	return 0;
};

