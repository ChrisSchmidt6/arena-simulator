#include "GameLoop.hpp"

void GameLoop::start_game() {
    while(!close_game) {
        game.start();
        while(game.is_running()) {
            game.main_menu();
        }
    }
};

void GameLoop::stop_game() {
    close_game = true;
};