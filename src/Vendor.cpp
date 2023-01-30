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
    int choice = -1;
    while(choice != 0) {
        while(true) {
            std::cout << "[Vendor Select Menu]\n";
            std::cout << "Please enter a corresponding number for the following menu options.\n";
            std::cout << "(0) Go back\n";
            std::cout << "(1) Apothecary\n";
            std::cout << "(2) Blacksmith\n";
            std::cout << "(3) Chef\n";
            std::cout << "(4) Quit game\n";

            std::cout << "Choice: ";
            std::cin >> choice;
            print_separator();

            if(!std::cin.fail()) break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid integer.\n\n";
        }

        switch(choice) {
            case 0:
                return;
            case 1:
                apothecary.buy_menu();
                break;
            case 2:
                blacksmith.buy_menu();
                break;
            case 3:
                chef.buy_menu();
                break;
            case 4:
                exit(-1);
                break;
            default:
                break;
        }
    }
}

void Vendor::buy_menu() {
    int choice = -1;
    while(choice != 0) {
        while(true) {
            std::cout << "[Vendor Purchase Menu]\n";
            std::cout << "Please enter a corresponding number for the following menu options.\n";
            std::cout << "(0) Leave\n";
            for(int i = 0; i < inventory.size(); i++) {
                Item* item = inventory[i];
                std::cout << "(" << (i + 1) << ") Buy " << item->ITEM_NAME << ": " << item->PRICE << " gold pieces\n";
            }
            std::cout << "(" << inventory.size() + 1 << ") Quit game\n";

            std::cout << "Choice: ";
            std::cin >> choice;
            print_separator();

            if(!std::cin.fail()) break;
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid integer.\n\n";
        }

        if(choice > 0 && choice <= inventory.size()) {
            int item_location = choice - 1;
            Item* chosen_item = inventory[item_location];

            if(Player::get().buy_item(chosen_item)) {
                remove_item(item_location);
            } else {
                std::cout << "You do not have enough gold pieces for that item.\n\n";
            }
        } else if(choice == inventory.size() + 1) {
            exit(-1);
        } else if(choice != 0) {
            std::cout << "Please enter a valid option.\n\n";
        }
    }
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