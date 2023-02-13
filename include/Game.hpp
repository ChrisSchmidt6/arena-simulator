#pragma once

#include "Arena.hpp"
#include "Vendor.hpp"

struct Game {
    Game(const Game&) = delete;
    static Game& get() {
        static Game game_instance;
        return game_instance;
    }

    void start();
    bool is_running();
    void main_menu();
    void toggle_menu_reset();
    bool menu_status();
    
    void generate_inventories();
private:
    Game(): active(false), clear_menus(false) {}

    bool active;
    bool clear_menus;

    Arena arena;
    
    Vendor apothecary = Vendor(VenType::Apothecary);
    Vendor blacksmith = Vendor(VenType::Blacksmith);
    Vendor chef = Vendor(VenType::Chef);

    bool initiate_character();
};