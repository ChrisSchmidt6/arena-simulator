#include <iostream>
#include <limits>
#include <random>

#include "Vendor.hpp"
#include "Player.hpp"
#include "assets.hpp"
#include "utility.hpp"

Vendor::Vendor(VenType type): TYPE(type) {
    switch(TYPE) {
        case VenType::Apothecary:
            vendor_type = "Apothecary";
            break;
        case VenType::Blacksmith:
            vendor_type = "Blacksmith";
            break;
        case VenType::Chef:
            vendor_type = "Chef";
            break;
        case VenType::None:
            vendor_type = "Unknown";
            break;
    };
};

void Vendor::main_menu(Vendor& apothecary, Vendor& blacksmith, Vendor& chef) {
    pairVec menu_items;

    do {
        std::cout << "[Vendor Select Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Apothecary", [&apothecary]() -> void {
            apothecary.business_menu();
        }));
        menu_items.push_back(std::make_pair("Blacksmith", [&blacksmith]() -> void {
            blacksmith.business_menu();
        }));
        menu_items.push_back(std::make_pair("Chef", [&chef]() -> void {
            chef.business_menu();
        }));
    } while(print_menu(menu_items));
};

void Vendor::business_menu() {
    pairVec menu_items;

    do {
        std::cout << "What kind of business would you like to do?\n\n";
        std::cout << "[" << vendor_type << " Type of Business Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Please show me what you have for sale.", [this]() -> void {
            buy_menu();
        }));

        menu_items.push_back(std::make_pair("Are you interested in any of my goods?", [this]() -> void {
            sell_menu();
        }));
    } while(print_menu(menu_items));
};

void Vendor::buy_menu() {
    pairVec menu_items;

    do {
        std::cout << "You have " << Player::get().get_stat("Gold") << " gold to spend.\n\n";
        std::cout << "[" << vendor_type << " Inventory Menu]\n";

        menu_items.clear();

        for(int i = 0; i < inventory.size(); i++) {
            Item* item = inventory[i];
            menu_items.push_back(std::make_pair(
                "Buy " + item->ITEM_NAME + ": " + std::to_string(item->PRICE) + " gold",
                [this, item, i]() -> void {
                    if(Player::get().get_stat("Gold") < item->PRICE) {
                        std::cout << "You do not have enough gold for that item.\n";
                        pause_until_enter();
                    } else {
                        confirmation_menu(
                            "Purchase " + item->ITEM_NAME + " for " + std::to_string(item->PRICE) + " gold?",
                            [this, item, i]() -> void {
                                Player::get().buy_item(item);
                                remove_item(i);

                                std::cout << "You have purchased the " << item->ITEM_NAME<< " for "
                                    << item->PRICE << " gold.\n";
                                save_to_file();
                                pause_until_enter();
                            }
                        );
                    }
                }
            ));
        }
    } while(print_menu(menu_items));
};

void Vendor::sell_menu() {
    std::vector<Item*> sale_goods = Player::get().get_items_by_type(TYPE);

    if(sale_goods.size() == 0) {
        std::cout << "Sorry, you do not seem to have anything of interest to me.\n";
        pause_until_enter();
        return;
    }

    pairVec menu_items;

    do {
        sale_goods = Player::get().get_items_by_type(TYPE);
        if(sale_goods.size() == 0) {
            std::cout << "It looks like you no longer have anything of interest to me. Come back any time.\n";
            pause_until_enter();
            return;
        }

        std::cout << "You have " << Player::get().get_stat("Gold") << " gold.\n\n";
        std::cout << "[" << vendor_type << " Purchase Menu]\n";

        menu_items.clear();

        for(int i = 0; i < sale_goods.size(); i++) {
            Item* item = sale_goods[i];
            int sale_price = item->PRICE * SALE_PERCENT;
            sale_price = sale_price < 1 ? 1 : sale_price;

            menu_items.push_back(std::make_pair(
                "Sell " + item->ITEM_NAME + ": " + std::to_string(sale_price) + " gold",
                [this, item, sale_price]() -> void {
                    confirmation_menu(
                        "Sell your " + item->ITEM_NAME + " for " + std::to_string(sale_price) + " gold?",
                        [this, item, sale_price]() -> void {
                            Player::get().remove_item(item);
                            Player::get().increase_gold(sale_price);

                            // If space for item, add to vendor's inventory
                            if(inventory.size() < 4) inventory.push_back(item);

                            std::cout << "You have sold your " << item->ITEM_NAME << " for " <<
                                std::to_string(sale_price) << " gold.\n";
                            save_to_file();
                            pause_until_enter();
                        }
                    );
                }
            ));
        }
    } while(print_menu(menu_items));
};

void Vendor::remove_item(int location) {
    inventory.erase(inventory.begin() + location);
};

void Vendor::generate_inventory() {
    inventory.clear();
    std::vector<Item*> inventory_options;
    for(int i = 0; i < item_container.size(); i++) {
        Item* item = item_container[i];
        if(item->TYPE == TYPE && item->TIER <= Player::get().get_stat("Level")) {
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
};