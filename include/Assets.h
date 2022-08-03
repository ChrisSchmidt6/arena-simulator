#pragma once

#include <vector>
#include <unordered_map>

#include "Item.h"
#include "Weapon.h"
#include "Consumable.h"

inline std::vector<Item*> item_container {
    new Item(000, "Bjarne Stroustrup Action Figure", 0, 0, Rarity::Mythic, false, false),
    new Consumable(100, "Weak Attack Potion", 5, 1, Rarity::Common, false, true, 2, 0, 0),
    new Consumable(101, "Weak Defense Potion", 5, 1, Rarity::Common, false, true, 0, 2, 0),
    new Consumable(102, "Weak Health Potion", 5, 1, Rarity::Common, false, true, 0, 0, 2),
    new Consumable(103, "Attack Potion", 12, 2, Rarity::Common, false, true, 4, 0, 0),
    new Consumable(104, "Defense Potion", 12, 2, Rarity::Common, false, true, 0, 4, 0),
    new Consumable(105, "Health Potion", 12, 2, Rarity::Common, false, true, 0, 0, 4),
    new Weapon(200, "Glorious Fists", 0, 0, Rarity::Common, false, false, 0),
    new Weapon(201, "Wooden Dagger", 10, 1, Rarity::Common, true, true, 5),
    new Weapon(202, "Wooden Spear", 12, 1, Rarity::Common, true, true, 6),
    new Weapon(203, "Wooden Sword", 12, 1, Rarity::Common, true, true, 6),
    new Weapon(204, "Wooden Mace", 12, 1, Rarity::Common, true, true, 6),
    new Weapon(205, "Spiked Club", 15, 1, Rarity::Uncommon, true, true, 7),
    // More
};

inline Item* get_item(const unsigned int ID) {
    for(int i = 0; i < item_container.size(); i++) {
        if(item_container[i]->ID == ID) return item_container[i];
    }
    return item_container[0];
}