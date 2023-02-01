#include <iostream>
#include <limits>
#include <random>

#include "Vendor.h"
#include "Player.h"
#include "assets.h"
#include "utility.h"

Vendor::Vendor(std::string name, unsigned int tier, VenType type):
    NAME(name), TIER(tier), TYPE(type) {
        generate_inventory();
}

void Vendor::main_menu(Vendor& apothecary, Vendor& blacksmith, Vendor& chef) {
    std::vector<std::pair<std::string, std::function<void()>>> menu_items;

    do {
        std::cout << "[Vendor Select Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Apothecary", [&apothecary]() -> void {
            apothecary.buy_menu();
        }));
        menu_items.push_back(std::make_pair("Blacksmith", [&blacksmith]() -> void {
            blacksmith.buy_menu();
        }));
        menu_items.push_back(std::make_pair("Chef", [&chef]() -> void {
            chef.buy_menu();
        }));
    } while(print_menu(menu_items));
}

void Vendor::buy_menu() {
    std::vector<std::pair<std::string, std::function<void()>>> menu_items;

    do {
        std::cout << "[Vendor Purchase Menu]\n";

        menu_items.clear();

        for(int i = 0; i < inventory.size(); i++) {
            Item* item = inventory[i];
            menu_items.push_back(std::make_pair(
                "Buy " + item->ITEM_NAME + ": " + std::to_string(item->PRICE) + " gold pieces",
                [item, this, i]() -> void {
                    if(Player::get().buy_item(item)) {
                        remove_item(i);
                    } else {
                        std::cout << "You do not have enough gold pieces for that item.\n\n";
                    }
                }));
        }
    } while(print_menu(menu_items));
}

void Vendor::sell_menu() {
    std::cout << "Let's see what you've got!\n\n";
}

void Vendor::remove_item(int location) {
    inventory.erase(inventory.begin() + location);
}

void Vendor::generate_inventory() {
    std::vector<Item*> inventory_options;
    for(int i = 0; i < item_container.size(); i++) {
        Item* item = item_container[i];
        if(item->TYPE == TYPE && item->TIER <= TIER) {
            inventory_options.push_back(item);
        }
    }

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> hundred_distribution(0, 100);

    // Set inventory size to 4 or smaller based on options
    int inventory_size = 4;
    if(inventory_options.size() < inventory_size) inventory_size = inventory_options.size();

    for(int i = 0; i < inventory_size; i++) {
        std::uniform_int_distribution<int> inv_distribution(0, inventory_options.size() - 1);
        int random_index = inv_distribution(mt);
        Item* item = inventory_options[random_index];

        bool validItem = false;
        switch(item->RARITY) {
            case Rarity::Common:
                if(hundred_distribution(mt) < 80) validItem = true;
                break;
            case Rarity::Uncommon:
                if(hundred_distribution(mt) < 50) validItem = true;
                break;
            case Rarity::Rare:
                if(hundred_distribution(mt) < 25) validItem = true;
                break;
            case Rarity::Mythic:
                if(hundred_distribution(mt) < 10) validItem = true;
                break;
            default:
                std::cout << "Item should have rarity\n";
                break;
        }

        if(validItem) {
            inventory.push_back(item);
            inventory_options.erase(inventory_options.begin() + random_index);
        } else {
            i -= 1;
        }
    }
}