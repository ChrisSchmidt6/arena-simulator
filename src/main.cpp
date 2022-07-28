#include "Game.h"

int main() {
	Game::start();
	
	while(Game::is_running()) {
		// Logic
		Game::main_menu();
	}

	return 0;
}