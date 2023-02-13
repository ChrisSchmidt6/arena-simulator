#pragma once

#include <vector>

#include "Item.hpp"
#include "Weapon.hpp"
#include "Consumable.hpp"

inline std::vector<Item*> item_container {
    // Misc
    new Item(000, "Bjarne Stroustrup Action Figure", VenType::None, 0, 0, Rarity::Mythic, false),

    // Consumable potions
    new Consumable(100, "Small Attack Potion", VenType::Apothecary, 5, 1, Rarity::Common, false, 2, 0, 0, 0),
    new Consumable(101, "Small Accuracy Potion", VenType::Apothecary, 5, 1, Rarity::Common, false, 0, 2, 0, 0),
    new Consumable(102, "Small Defense Potion", VenType::Apothecary, 5, 1, Rarity::Common, false, 0, 0, 2, 0),
    new Consumable(103, "Small Health Potion", VenType::Apothecary, 6, 2, Rarity::Common, false, 0, 0, 0, 3),
    new Consumable(104, "Small Combat Potion", VenType::Apothecary, 10, 3, Rarity::Common, false, 1, 1, 1, 0),
    new Consumable(105, "Attack Potion", VenType::Apothecary, 12, 4, Rarity::Common, false, 4, 0, 0, 0),
    new Consumable(106, "Accuracy Potion", VenType::Apothecary, 12, 4, Rarity::Common, false, 0, 4, 0, 0),
    new Consumable(107, "Defense Potion", VenType::Apothecary, 12, 4, Rarity::Common, false, 0, 0, 4, 0),
    new Consumable(108, "Health Potion", VenType::Apothecary, 15, 5, Rarity::Common, false, 0, 0, 0, 6),
    new Consumable(109, "Combat Potion", VenType::Apothecary, 25, 6, Rarity::Uncommon, false, 2, 2, 2, 0),
    new Consumable(110, "Large Attack Potion", VenType::Apothecary, 20, 7, Rarity::Uncommon, false, 5, 0, 0, 0),
    new Consumable(111, "Large Accuracy Potion", VenType::Apothecary, 20, 7, Rarity::Uncommon, false, 0, 5, 0, 0),
    new Consumable(112, "Large Defense Potion", VenType::Apothecary, 20, 7, Rarity::Uncommon, false, 0, 0, 5, 0),
    new Consumable(113, "Large Health Potion", VenType::Apothecary, 25, 8, Rarity::Uncommon, false, 0, 0, 0, 10),
    new Consumable(114, "Large Combat Potion", VenType::Apothecary, 40, 9, Rarity::Uncommon, false, 3, 3, 3, 0),

    // Consumable food
    new Consumable(150, "Stale Bread", VenType::Chef, 3, 1, Rarity::Common, true, 0, 0, 0, 4),
    new Consumable(151, "Chunky Stew", VenType::Chef, 3, 1, Rarity::Common, true, 0, 0, 0, 4),
    new Consumable(152, "Assorted Berries", VenType::Chef, 3, 1, Rarity::Common, true, 0, 0, 0, 4),
    new Consumable(153, "Fresh Bread", VenType::Chef, 5, 1, Rarity::Common, false, 0, 0, 0, 6),
    new Consumable(154, "Steamed Veggies", VenType::Chef, 5, 1, Rarity::Common, false, 0, 0, 0, 6),
    new Consumable(155, "Meaty Sandwich", VenType::Chef, 6, 2, Rarity::Common, false, 0, 0, 0, 7),
    new Consumable(156, "Blackberry Pie", VenType::Chef, 10, 2, Rarity::Common, false, 0, 0, 0, 9),
    new Consumable(157, "Chocolate Pastry", VenType::Chef, 10, 2, Rarity::Common, false, 0, 0, 0, 9),
    new Consumable(158, "Banana Muffin", VenType::Chef, 12, 3, Rarity::Common, false, 0, 0, 0, 10),
    new Consumable(159, "Lean Venison", VenType::Chef, 12, 3, Rarity::Common, false, 0, 0, 0, 10),
    new Consumable(160, "Cooked Fish", VenType::Chef, 15, 4, Rarity::Uncommon, false, 0, 0, 0, 12),
    new Consumable(161, "Boiled Eggs", VenType::Chef, 15, 4, Rarity::Uncommon, false, 0, 0, 0, 12),
    new Consumable(162, "Cooked Lamb", VenType::Chef, 15, 4, Rarity::Uncommon, false, 0, 0, 0, 12),
    new Consumable(163, "Smoked Salmon", VenType::Chef, 18, 5, Rarity::Uncommon, false, 0, 0, 0, 14),

    // Weapons
    new Weapon(200, "Glorious Fists", VenType::None, 0, 0, Rarity::Common, false, 0),
    new Weapon(201, "Wooden Dagger", VenType::Blacksmith, 10, 1, Rarity::Common, true, 5),
    new Weapon(202, "Wooden Spear", VenType::Blacksmith, 12, 1, Rarity::Common, true, 6),
    new Weapon(203, "Wooden Sword", VenType::Blacksmith, 12, 1, Rarity::Common, true, 6),
    new Weapon(204, "Wooden Mace", VenType::Blacksmith, 12, 1, Rarity::Common, true, 6),
    new Weapon(205, "Spiked Club", VenType::Blacksmith, 15, 1, Rarity::Uncommon, true, 7),
    new Weapon(206, "Flint Dagger", VenType::Blacksmith, 13, 2, Rarity::Common, true, 7),
    new Weapon(207, "Flint Spear", VenType::Blacksmith, 20, 3, Rarity::Common, true, 8),
    new Weapon(208, "Stone Hammer", VenType::Blacksmith, 20, 3, Rarity::Uncommon, true, 8),
    new Weapon(209, "Bronze Sword", VenType::Blacksmith, 25, 3, Rarity::Uncommon, true, 10),
    new Weapon(210, "Spiked Flail", VenType::Blacksmith, 25, 3, Rarity::Uncommon, true, 10),
    new Weapon(211, "Iron Chain", VenType::Blacksmith, 23, 4, Rarity::Uncommon, true, 10),
    new Weapon(212, "Iron Dagger", VenType::Blacksmith, 23, 4, Rarity::Uncommon, true, 10),
    new Weapon(213, "Iron Spear", VenType::Blacksmith, 30, 5, Rarity::Uncommon, true, 12),
    new Weapon(214, "Iron Sword", VenType::Blacksmith, 30, 5, Rarity::Uncommon, true, 12),
    new Weapon(215, "Bonecrusher", VenType::Blacksmith, 32, 5, Rarity::Uncommon, true, 13),
    new Weapon(216, "Iron Rapier", VenType::Blacksmith, 35, 5, Rarity::Rare, true, 14),
    new Weapon(217, "Glowing Dagger", VenType::Blacksmith, 33, 6, Rarity::Uncommon, true, 14),
    new Weapon(218, "Glowing Mace", VenType::Blacksmith, 36, 7, Rarity::Uncommon, true, 15),
    new Weapon(219, "Glowing Scimitar", VenType::Blacksmith, 36, 7, Rarity::Uncommon, true, 15),
    new Weapon(220, "Glowing Hatchet", VenType::Blacksmith, 36, 7, Rarity::Uncommon, true, 15),
    new Weapon(221, "Carved Wand", VenType::Blacksmith, 42, 7, Rarity::Rare, true, 16),
    new Weapon(222, "Serrated Dagger", VenType::Blacksmith, 40, 8, Rarity::Rare, true, 16),
    new Weapon(223, "Flaming Spear", VenType::Blacksmith, 45, 9, Rarity::Rare, true, 17),
    new Weapon(224, "Cursed Whip", VenType::Blacksmith, 45, 9, Rarity::Rare, true, 17),
    new Weapon(225, "Spiked Nunchucks", VenType::Blacksmith, 45, 9, Rarity::Rare, true, 17),
    new Weapon(226, "Death Whisper", VenType::Blacksmith, 50, 9, Rarity::Rare, true, 18),
    new Weapon(227, "Dragon's Tooth", VenType::Blacksmith, 48, 10, Rarity::Rare, true, 18),
    new Weapon(228, "Dragontooth Sword", VenType::Blacksmith, 55, 11, Rarity::Rare, true, 19),
    new Weapon(229, "Dragontooth Spear", VenType::Blacksmith, 55, 11, Rarity::Rare, true, 19),
    new Weapon(230, "Dragontooth Scimitar", VenType::Blacksmith, 55, 11, Rarity::Rare, true, 19),
    new Weapon(231, "Mysterious Crossbow", VenType::Blacksmith, 70, 11, Rarity::Mythic, true, 20),
    new Weapon(232, "Blessed Wand", VenType::Blacksmith, 65, 12, Rarity::Rare, true, 20),
    new Weapon(233, "Archaic Sword", VenType::Blacksmith, 75, 13, Rarity::Rare, true, 21),
    new Weapon(234, "Archaic Spear", VenType::Blacksmith, 75, 13, Rarity::Rare, true, 21),
    new Weapon(235, "Archaic Bow", VenType::Blacksmith, 75, 13, Rarity::Rare, true, 21),
    new Weapon(236, "Book of Secrets", VenType::Blacksmith, 85, 13, Rarity::Mythic, true, 22),
    new Weapon(237, "Sacred Wand", VenType::Blacksmith, 80, 14, Rarity::Mythic, true, 22),
    new Weapon(238, "Staff of Nature", VenType::Blacksmith, 92, 15, Rarity::Mythic, true, 23),
    new Weapon(239, "Staff of Life", VenType::Blacksmith, 92, 15, Rarity::Mythic, true, 23),
    new Weapon(240, "Staff of Energy", VenType::Blacksmith, 92, 15, Rarity::Mythic, true, 23),
    new Weapon(241, "Chaotic Tome", VenType::Blacksmith, 100, 15, Rarity::Mythic, true, 24),
};

inline std::vector<std::string> enemy_names {
    "Glorg", "Xandra", "Schmop", "Liev", "Treck", "Youp",
    "Enh", "Wamza", "Egbert", "Bob", "Barmalpath", "Chaz"
};

Item* get_item(const unsigned int ID);
