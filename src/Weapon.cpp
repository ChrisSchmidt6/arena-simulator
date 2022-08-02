#include "Weapon.h"
#include "Player.h"

void Weapon::display_item_options() {
    std::cout << "What would you like to do with your " << ITEM_NAME << "?\n";
    std::cout << "Please enter a corresponding number for the following menu options.\n";
    std::cout << "(0) Go back\n";
    std::cout << "(1) Equip " << ITEM_NAME << "\n";
    std::cout << "(2) DISPOSE OF " << ITEM_NAME << "\n";

    std::cout << "Choice: ";
    int choice;
    std::cin >> choice;
    std::cout << "\n";

    switch (choice) {
        case 0:
            return;
        case 1:
            Player::equip_weapon(this);
            std::cout << "You are now wielding your " << ITEM_NAME << "!\n";
            break;
        case 2:
            std::cout << "Are you SURE you want to DISPOSE OF " << ITEM_NAME << "?\n";
            std::cout << "(0) No\n";
            std::cout << "(1) What was I thinking?!\n";
            std::cout << "(2) Yes\n";
            std::cout << "Choice: ";
            std::cin >> choice;
            std::cout << "\n";
            
            if(choice != 2) return;
            if(Player::remove_item(this)) {
                std::cout << "You disposed of your " << ITEM_NAME << "\n";
            } else {
                std::cout << "Could not locate " << ITEM_NAME << "\n";
            }
            break;
        default:
            break;
    }
}