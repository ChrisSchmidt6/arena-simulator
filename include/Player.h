#pragma once

#include "Item.h"
#include "assets.h"

struct Player {
    Player(const Player&) = delete;
    static Player& get() {
        static Player player_instance;
        return player_instance;
    }

    std::string name;

    void insert_item(Item* item);
    bool remove_item(Item* item);
    int has_item(Item* item);
    bool buy_item(Item* item);
    void equip_weapon(Item* weapon);
    void display_stats();
    void inventory_menu();
    void weapon_menu();
    std::string get_save_data();
    bool load_save_data(std::string &save_data);
private:
    Player() {}
    
    unsigned int max_health = 10; // save line 1
    unsigned int health = 10; // Save line 2
    unsigned int attack = 1; // Save line 3
    unsigned int defense = 1; // Save line 4
    unsigned int level = 1; // Save line 5
    unsigned int experience = 0; // Save line 6
    unsigned int gold = 10; // Save line 7
    Item* weapon_slot = get_item(200); // Save line 8
    std::vector<Item*> inventory; // Save line 9+
};