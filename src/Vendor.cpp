#include "Vendor.h"

void Vendor::buy_menu() {
    display_greeting();
    
    int choice;
    std::cout << "Please enter a corresponding number for the following menu options.\n";

    std::cout << "(0) Leave\n";
    for(int i = 0; i < inventory.size(); i++) {
        Item* item = inventory[i];
        std::cout << "(" << (i + 1) << ") Buy " << item->ITEM_NAME << ": " << item->PRICE << " gold pieces\n";
    }
    std::cout << "(" << inventory.size() + 1 << ") Quit game\n";

    std::cout << "Choice: ";
    std::cin >> choice;
    std::cout << "\n";

    if(choice == 0) {
        return;
    } else if(choice > 0 && choice <= inventory.size()) {
        int item_location = choice - 1;
        Item* chosen_item = inventory[item_location];

        if(Player::buy_item(chosen_item)) {
            remove_item(item_location);
        } else {
            std::cout << "You do not have enough gold pieces for that item.\n\n";
        }
    } else if(choice == inventory.size() + 1) {
        exit(-1);
    } else {
        std::cout << "That was not an option.\n\n";
    }
}

void Vendor::sell_menu() {
    std::cout << "Let's see what you've got!\n\n";
}

void Vendor::remove_item(int location) {
    inventory.erase(inventory.begin() + location);
}