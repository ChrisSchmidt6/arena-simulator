#pragma once

#include "Vendor.h"

struct Game {
    Game(const Game&) = delete;
    static Game& get() {
        static Game game_instance;
        return game_instance;
    }
    
    Vendor apothecary = Vendor("Sandra", 1, VenType::Apothecary);
    Vendor blacksmith = Vendor("Bob", 1, VenType::Blacksmith);
    Vendor chef = Vendor("Emeril", 1, VenType::Chef);

    void start();
    bool is_running();
    void main_menu();
    void vendor_menu();
private:
    Game() {}

    bool active = false;

    bool initiate_character();
};