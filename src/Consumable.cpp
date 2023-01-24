#include <iostream>
#include <limits>

#include "Consumable.h"
#include "Player.h"

void Consumable::display_item_options() {
    int choice;
    while(true) {
        std::cout << "[Consumable Options Menu]\n";
        std::cout << "What would you like to do with your " << ITEM_NAME << "?\n";
        std::cout << "Please enter a corresponding number for the following menu options.\n";
        std::cout << "(0) Go back\n";
        std::cout << "(1) DISPOSE OF " << ITEM_NAME << "\n";
        std::cout << "(2) Quit game\n";

        std::cout << "Choice: ";
        std::cin >> choice;
        std::cout << "\n";

        if(!std::cin.fail()) break;
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid integer.\n\n";
    }

    switch (choice) {
        case 0:
            return;
        case 1:
            while(true) {
                std::cout << "[Confirmation Menu]\n";
                std::cout << "Are you SURE you want to DISPOSE OF " << ITEM_NAME << "?\n";
                std::cout << "(0) No\n";
                std::cout << "(1) What was I thinking?!\n";
                std::cout << "(2) Yes\n";

                std::cout << "Choice: ";
                std::cin >> choice;
                std::cout << "\n";

                if(!std::cin.fail()) break;
                
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter a valid integer.\n\n";
            }
            
            if(choice != 2) return;
            if(Player::get().remove_item(this)) {
                std::cout << "You disposed of your " << ITEM_NAME << "\n";
            } else {
                std::cout << "Could not locate " << ITEM_NAME << "\n";
            }
            break;
        case 2:
            exit(-1);
        default:
            std::cout << "Please enter a valid option.\n\n";
            display_item_options();
    }
}