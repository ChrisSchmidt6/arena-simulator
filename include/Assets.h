#pragma once

#include <vector>
#include <unordered_map>

#include "Item.h"
#include "Weapon.h"

inline std::vector<Item*> item_container {
    new Item(000, "Bjarne Stroustrup Action Figure", 0, 0, Rarity::Mythic, false, false),
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