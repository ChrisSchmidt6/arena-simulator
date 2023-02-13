#include "Game.hpp"

int main() {
	Game& game = Game::get();

	game.start();
	
	while(game.is_running()) {
		game.main_menu();
	}

	return 0;
}