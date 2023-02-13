#include "GameLoop.hpp"

int main() {
	GameLoop& game_loop = GameLoop::get();

	game_loop.start_game();

	return 0;
}