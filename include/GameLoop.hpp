#pragma once

#include "Game.hpp"

struct GameLoop {
    GameLoop(const GameLoop&) = delete;
    static GameLoop& get() {
        static GameLoop gl_instance;
        return gl_instance;
    }

    void start_game();
    void stop_game();

private:
    GameLoop(void): close_game(false) {}

    Game &game = Game::get();

    bool close_game;
};