#include"World.h"
#include<Windows.h>

int main() {
	World world(25,25);
	world.makeEntities();
	while (world.isPlayerAlive()) { // Game loop
		world.Draw();
		world.nextTurn();
		system("CLS");
	}
	return 0;
}