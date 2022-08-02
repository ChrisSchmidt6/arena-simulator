#pragma once

#include <iostream>

#include "Item.h"

struct Weapon : Item {
    const unsigned int ATTACK_MOD;

    Weapon(unsigned int id, std::string item_name, unsigned int price,
        unsigned int tier, Rarity rarity, bool can_drop, bool vendor_item,
        unsigned int attack_mod): 
        Item(id, item_name, price, tier, rarity, can_drop, vendor_item),
        ATTACK_MOD(attack_mod) {};
    
    void display_item_options() override;
};