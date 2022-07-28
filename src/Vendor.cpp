#include "Vendor.h"

Vendor::Vendor(std::string name) {
    this->name = name;
    inventory.push_back(get_item(201));
    inventory.push_back(get_item(202));
    inventory.push_back(get_item(203));
    inventory.push_back(get_item(204));
}

void Vendor::display_greeting() {
    std::cout << "Welcome to " << name << "'s shop. I've got many wares!" << std::endl;
}

void Vendor::buy_menu() {
    display_greeting();
    
    int choice;
    std::cout << "Please enter a corresponding number for the following menu options." << std::endl;

    std::cout << "(0) Leave" << std::endl;
    for(int i = 0; i < inventory.size(); i++) {
        Item* item = inventory[i];
        std::cout << "(" << (i + 1) << ") Buy " << item->ITEM_NAME << ": " << item->get_price() << " gold pieces" << std::endl;
    }
    std::cout << "(" << inventory.size() + 1 << ") Quit game" << std::endl;

    std::cout << "Choice: ";
    std::cin >> choice;
    std::cout << std::endl;

    if(choice == 0) {
        std::cout << "Thanks for visiting my shop!\n" << std::endl;
    } else if(choice > 0 && choice <= inventory.size()) {
        int item_location = choice - 1;
        Item* chosen_item = inventory[item_location];

        if(Player::buy_item(chosen_item)) {
            remove_item(item_location);
        } else {
            std::cout << "You do not have enough gold pieces for that item.\n" << std::endl;
        }
    } else if(choice == inventory.size() + 1) {
        exit(-1);
    } else {
        std::cout << "That was not an option.\n" << std::endl;
    }
}

void Vendor::sell_menu() {
    std::cout << "Let's see what you've got!\n" << std::endl;
}

void Vendor::remove_item(int location) {
    inventory.erase(inventory.begin() + location);
}