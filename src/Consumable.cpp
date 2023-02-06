#include <iostream>
#include <limits>

#include "Consumable.h"
#include "Player.h"
#include "utility.h"

void Consumable::display_item_options() {
    pairVec menu_items;
    // Return early if item is disposed of
    bool return_early = false;

    do {
        // If this menu should be exited early, return
        if(return_early) return;

        std::cout << "What would you like to do with your " << ITEM_NAME << "?\n\n";
        std::cout << "[Weapon Options Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("DISPOSE OF " + ITEM_NAME, [this, &return_early]() -> void {
            int choice = -1;
            while(true) {
                std::cout << "Are you SURE you want to DISPOSE OF " << ITEM_NAME << "?\n\n";
                std::cout << "[Confirmation Menu]\n";
                std::cout << "(0) No\n";
                std::cout << "(1) What was I thinking?!\n";
                std::cout << "(2) Yes\n";

                std::cout << "Choice: ";
                std::cin >> choice;
                print_separator();

                if(!std::cin.fail()) break;
                
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter a valid integer.\n\n";
            }
            
            if(choice != 2) return;
            if(Player::get().remove_item(this)) {
                std::cout << "You disposed of your " << ITEM_NAME << "\n";
                return_early = true;
                pause_until_enter();
            } else {
                std::cout << "Could not locate " << ITEM_NAME << "\n";
            }
        }));
    } while(print_menu(menu_items));
}