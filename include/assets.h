#pragma once

#include <vector>

#include "Item.h"
#include "Weapon.h"
#include "Consumable.h"

inline std::vector<Item*> item_container {
    // Misc
    new Item(000, "Bjarne Stroustrup Action Figure", VenType::None, 0, 0, Rarity::Mythic, false),

    // Consumable
    new Consumable(100, "Weak Attack Potion", VenType::Apothecary, 5, 1, Rarity::Common, false, 2, 0, 0),
    new Consumable(101, "Weak Defense Potion", VenType::Apothecary, 5, 1, Rarity::Common, false, 0, 2, 0),
    new Consumable(102, "Weak Health Potion", VenType::Apothecary, 5, 1, Rarity::Common, false, 0, 0, 2),
    new Consumable(103, "Attack Potion", VenType::Apothecary, 12, 2, Rarity::Common, false, 4, 0, 0),
    new Consumable(104, "Defense Potion", VenType::Apothecary, 12, 2, Rarity::Common, false, 0, 4, 0),
    new Consumable(105, "Health Potion", VenType::Apothecary, 12, 2, Rarity::Common, false, 0, 0, 4),
    new Consumable(106, "Stale Bread", VenType::Chef, 12, 1, Rarity::Common, true, 0, 0, 4),
    new Consumable(107, "Chunky Stew", VenType::Chef, 12, 1, Rarity::Common, true, 0, 0, 4),
    new Consumable(108, "Assorted Berries", VenType::Chef, 12, 1, Rarity::Common, true, 0, 0, 4),
    new Consumable(109, "Fresh Bread", VenType::Chef, 15, 2, Rarity::Common, false, 0, 0, 6),
    new Consumable(110, "Meaty Sandwich", VenType::Chef, 18, 2, Rarity::Uncommon, false, 0, 0, 7),
    new Consumable(111, "Steamed Veggies", VenType::Chef, 15, 2, Rarity::Common, false, 0, 0, 6),

    // Weapons
    new Weapon(200, "Glorious Fists", VenType::None, 0, 0, Rarity::Common, false, 0),
    new Weapon(201, "Wooden Dagger", VenType::Blacksmith, 10, 1, Rarity::Common, true, 5),
    new Weapon(202, "Wooden Spear", VenType::Blacksmith, 12, 1, Rarity::Common, true, 6),
    new Weapon(203, "Wooden Sword", VenType::Blacksmith, 12, 1, Rarity::Common, true, 6),
    new Weapon(204, "Wooden Mace", VenType::Blacksmith, 12, 1, Rarity::Common, true, 6),
    new Weapon(205, "Spiked Club", VenType::Blacksmith, 15, 1, Rarity::Uncommon, true, 7),
    new Weapon(206, "Flint Dagger", VenType::Blacksmith, 13, 2, Rarity::Common, true, 7),
    new Weapon(207, "Flint Spear", VenType::Blacksmith, 20, 2, Rarity::Common, true, 8),
    new Weapon(208, "Stone Hammer", VenType::Blacksmith, 20, 2, Rarity::Uncommon, true, 8),
    new Weapon(209, "Bronze Sword", VenType::Blacksmith, 25, 2, Rarity::Uncommon, true, 10),
    new Weapon(210, "Spiked Flail", VenType::Blacksmith, 25, 2, Rarity::Uncommon, true, 10),
    new Weapon(211, "Iron Chain", VenType::Blacksmith, 23, 3, Rarity::Uncommon, true, 10),
    new Weapon(212, "Iron Dagger", VenType::Blacksmith, 23, 3, Rarity::Uncommon, true, 10),
    new Weapon(213, "Iron Spear", VenType::Blacksmith, 30, 3, Rarity::Uncommon, true, 12),
    new Weapon(214, "Iron Sword", VenType::Blacksmith, 30, 3, Rarity::Uncommon, true, 12),
    new Weapon(215, "Bonecrusher", VenType::Blacksmith, 32, 3, Rarity::Uncommon, true, 13),
    new Weapon(216, "Iron Rapier", VenType::Blacksmith, 35, 3, Rarity::Rare, true, 14),
    new Weapon(217, "Glowing Dagger", VenType::Blacksmith, 33, 4, Rarity::Uncommon, true, 14),
    new Weapon(218, "Glowing Mace", VenType::Blacksmith, 36, 4, Rarity::Uncommon, true, 15),
    new Weapon(219, "Glowing Scimitar", VenType::Blacksmith, 36, 4, Rarity::Uncommon, true, 15),
    new Weapon(220, "Glowing Hatchet", VenType::Blacksmith, 36, 4, Rarity::Uncommon, true, 15),
    new Weapon(221, "Carved Wand", VenType::Blacksmith, 42, 4, Rarity::Rare, true, 16),
    new Weapon(222, "Serrated Dagger", VenType::Blacksmith, 40, 5, Rarity::Rare, true, 16),
    new Weapon(223, "Flaming Spear", VenType::Blacksmith, 45, 5, Rarity::Rare, true, 17),
    new Weapon(224, "Cursed Whip", VenType::Blacksmith, 45, 5, Rarity::Rare, true, 17),
    new Weapon(225, "Spiked Nunchucks", VenType::Blacksmith, 45, 5, Rarity::Rare, true, 17),
    new Weapon(226, "Death Whisper", VenType::Blacksmith, 50, 5, Rarity::Rare, true, 18),
    new Weapon(227, "Dragon's Tooth", VenType::Blacksmith, 48, 6, Rarity::Rare, true, 18),
    new Weapon(228, "Dragontooth Sword", VenType::Blacksmith, 55, 6, Rarity::Rare, true, 19),
    new Weapon(229, "Dragontooth Spear", VenType::Blacksmith, 55, 6, Rarity::Rare, true, 19),
    new Weapon(230, "Dragontooth Scimitar", VenType::Blacksmith, 55, 6, Rarity::Rare, true, 19),
    new Weapon(231, "Mysterious Crossbow", VenType::Blacksmith, 70, 6, Rarity::Mythic, true, 20),
    new Weapon(232, "Blessed Wand", VenType::Blacksmith, 65, 7, Rarity::Rare, true, 20),
    new Weapon(233, "Archaic Sword", VenType::Blacksmith, 75, 7, Rarity::Rare, true, 21),
    new Weapon(234, "Archaic Spear", VenType::Blacksmith, 75, 7, Rarity::Rare, true, 21),
    new Weapon(235, "Archaic Bow", VenType::Blacksmith, 75, 7, Rarity::Rare, true, 21),
    new Weapon(236, "Book of Secrets", VenType::Blacksmith, 85, 7, Rarity::Mythic, true, 22),
    new Weapon(237, "Sacred Wand", VenType::Blacksmith, 80, 8, Rarity::Mythic, true, 22),
    new Weapon(238, "Book of Secrets", VenType::Blacksmith, 92, 8, Rarity::Mythic, true, 23),
    new Weapon(239, "Book of Secrets", VenType::Blacksmith, 92, 8, Rarity::Mythic, true, 23),
    new Weapon(240, "Book of Secrets", VenType::Blacksmith, 92, 8, Rarity::Mythic, true, 23),
    new Weapon(241, "Chaotic Tome", VenType::Blacksmith, 100, 8, Rarity::Mythic, true, 24),
};

inline std::vector<std::string> enemy_names {
    "Glorg", "Xandra", "Schmop", "Liev", "Treck", "Youp",
    "Enh", "Wamza", "Egbert", "Bob", "Barmalpath", "Chaz"
};

Item* get_item(const unsigned int ID);
