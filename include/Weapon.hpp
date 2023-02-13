#pragma once

#include "Item.hpp"

struct Weapon : Item {
    const unsigned int ATTACK_MOD;

    Weapon(unsigned int id, std::string item_name, VenType type,
        unsigned int price, unsigned int tier, Rarity rarity, bool can_drop,
        unsigned int attack_mod): 
        Item(id, item_name, type, price, tier, rarity, can_drop),
        ATTACK_MOD(attack_mod) {};
    
    void display_item_options() override;
};