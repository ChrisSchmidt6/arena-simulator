#pragma once

#include "Item.h"

struct Consumable : Item {
    const unsigned int ATTACK_MOD;
    const unsigned int DEFENSE_MOD;
    const unsigned int HEALTH_REGEN;

    Consumable(unsigned int id, std::string item_name, unsigned int price,
        unsigned int tier, Rarity rarity, bool can_drop, bool vendor_item,
        unsigned int attack_mod, unsigned int defense_mod,
        unsigned int health_regen): 
        Item(id, item_name, price, tier, rarity, can_drop, vendor_item),
        ATTACK_MOD{attack_mod}, DEFENSE_MOD(defense_mod),
        HEALTH_REGEN(health_regen) {};
    
    void display_item_options() override;
};