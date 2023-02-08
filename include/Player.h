#pragma once

#include "Combat.h"
#include "Item.h"
#include "assets.h"

struct Player : Combat {
    Player(const Player&) = delete;
    static Player& get() {
        static Player player_instance;
        return player_instance;
    }

    std::string name;

    std::string get_name() override;
    int get_stat(std::string stat) override;
    void display_stats() override;

    void insert_item(Item* item);
    bool remove_item(Item* item);
    bool buy_item(Item* item);
    int has_item(Item* item); // returns position of item in inventory, -1 if not found
    void equip_weapon(Item* weapon);
    void remove_weapon();
    int weapon_drop_chance();
    void increase_gold(int amount);
    void decrease_gold(int amount);
    void gain_experience(int amount);
    void inventory_menu();
    void weapon_menu();
    void reset_health();

    std::string get_save_data();
    bool load_save_data(std::string &save_data);
private:
    Player() {}
    
    int experience = 0;
    const int lose_weapon_chance = 10;
    std::vector<Item*> inventory;
};