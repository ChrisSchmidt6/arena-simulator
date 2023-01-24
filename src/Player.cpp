#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "Player.h"

void Player::insert_item(Item* item) {
    inventory.push_back(item);
};

bool Player::remove_item(Item* item) {
    for(int i = 0; i < inventory.size(); i++) {
        if(inventory[i] == item) {
            inventory.erase(inventory.begin() + i);
            return true;
        }
    }
    return false;
};

bool Player::buy_item(Item* item) {
    if(gold >= item->PRICE) {
        gold -= item->PRICE;
        inventory.push_back(item);
        return true;
    } else {
        return false;
    }
};

void Player::equip_weapon(Item* weapon) {
    int inventory_location;
    for(int i = 0; i < inventory.size(); i++) {
        if(inventory[i] == weapon) {
            inventory_location = i;
            break;
        }
    }
    Item* old_weapon = weapon_slot;
    weapon_slot = weapon;
    if(old_weapon->ID != 200) inventory[inventory_location] = old_weapon;
    else inventory.erase(inventory.begin() + inventory_location);
};

void Player::display_stats() {
    std::cout << "Max Health: " << max_health << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Attack: " << attack << "\n";
    std::cout << "Defense: " << defense << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Experience: " << experience << "\n";
};

void Player::inventory_menu() {
    int choice = -1;
    while(choice != 0) {
        while(true) {
            std::cout << "[Inventory Menu]\n";
            std::cout << "You have " << gold << " gold pieces.\n";
            std::cout << "Please enter a corresponding number for the following menu options.\n";
            std::cout << "(0) Go back\n";
            for(int i = 0; i < inventory.size(); i++) {
                std::cout << "(" << i + 1 << ") View options - ";
                std::cout << inventory[i]->ITEM_NAME << "\n";
            }
            std::cout << "(" << inventory.size() + 1 << ") View equipped " << weapon_slot->ITEM_NAME << "\n";
            std::cout << "(" << inventory.size() + 2 << ") Quit game\n";

            std::cout << "Choice: ";
            std::cin >> choice;
            std::cout << "\n";

            if(!std::cin.fail()) break;
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid integer.\n\n";
        }

        if(choice >= 1 && choice <= inventory.size()) {
            inventory[choice - 1]->display_item_options();
        } else if(choice == inventory.size() + 1) {
            if(weapon_slot->ID == 200) {
                std::cout << "There's no reason to stand around examining your fists.\n\n";
            } else {
                weapon_menu();
            }
        } else if(choice == inventory.size() + 2) {
            exit(-1);
        } else if(choice != 0) {
            std::cout << "Please enter a valid option.\n\n";
        }
    }
};

void Player::weapon_menu() {
    // This cannot fail as you're only able to equip weapons
    Weapon* weapon = static_cast<Weapon*>(weapon_slot);
    int choice;
    while(true) {
        std::cout << "[Equipped Weapon Menu]\n";
        std::cout << "Your " << weapon->ITEM_NAME << " has an attack modifier of " << weapon->ATTACK_MOD << "\n";
        std::cout << "Please enter a corresponding number for the following menu options.\n";
        std::cout << "(0) Go back\n";
        std::cout << "(1) Unequip " << weapon->ITEM_NAME << "\n";
        std::cout << "(2) Quit game\n";

        std::cout << "Choice: ";
        std::cin >> choice;
        std::cout << "\n";

        if(!std::cin.fail()) break;
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid integer.\n\n";
    }

    switch(choice) {
        case 0:
            return;
        case 1:
            if(weapon->ID == 200) {
                std::cout << "You try to remove your fists... but you fail. Congratulations, your fists are now sore.\n\n";
                return;
            } else {
                inventory.push_back(weapon_slot);
                weapon_slot = get_item(200);
                std::cout << "You are no longer wielding your " << weapon->ITEM_NAME << ".\n\n";
                return;
            }
            break;
        case 2:
            exit(-1);
        default:
            std::cout << "Please enter a valid option.\n\n";
            inventory_menu();
            break;
    }
};

std::string Player::get_save_data() {
    std::stringstream ss;

    ss << "Max Health: " << max_health << "\n";
    ss << "Health: " << health << "\n";
    ss << "Attack: " << attack << "\n";
    ss << "Defense: " << defense << "\n";
    ss << "Level: " << level << "\n";
    ss << "Experience: " << experience << "\n";
    ss << "Gold: " << gold << "\n";
    ss << "Weapon: " << weapon_slot->ID << "\n";
    ss << "Inventory: \n\t";

    for(int i = 0; i < inventory.size(); i++) {
        ss << inventory[i]->ID;
        (i == inventory.size() - 1) ? ss << "\n" : ss << ", ";
        if((i + 1) % 5 == 0 && i != inventory.size() - 1) ss << "\n\t";
    }

    return ss.str();
};

bool Player::load_save_data(std::string &save_data) {
    try {
        int pos = save_data.find(": ", 0) + 2;
        int len = save_data.find("\n", pos) - pos;
        int current_stat = 0;

        do {
            unsigned int parsed_stat = std::stoi(save_data.substr(pos, len));

            switch(current_stat) {
                case 0:
                    max_health = parsed_stat;
                    break;
                case 1:
                    health = parsed_stat;
                    break;
                case 2:
                    attack = parsed_stat;
                    break;
                case 3:
                    defense = parsed_stat;
                    break;
                case 4:
                    level = parsed_stat;
                    break;
                case 5:
                    experience = parsed_stat;
                    break;
                case 6:
                    gold = parsed_stat;
                    break;
                case 7:
                    weapon_slot = get_item(parsed_stat);
                    break;
                default:
                    std::cout << "Error occurred while loading player stats\n";
                    break;
            }

            pos = save_data.find(": ", pos) + 2;
            len = save_data.find("\n", pos) - pos;
            current_stat++;
        } while(save_data.find("Inventory: \n\t", pos) != std::string::npos);

        pos = save_data.find("Inventory: \n\t") + 13;
        int ogPos = pos;
        
        len = 0;
        while(len != std::string::npos && pos >= ogPos) {
            len = save_data.find(',', pos);
            (len == std::string::npos) ? len = save_data.find('\n', pos) - pos : len -= pos;
            if(len == 0) break;

            insert_item(get_item(stoi(save_data.substr(pos, len))));

            pos = save_data.find(',', pos + len) + 2;
            pos += (save_data[pos] == '\n') ? 1 : 0;
        }
    } catch(const std::exception & ex) {
        std::cout << ex.what() << "\n";
        return false;
    }

    return true;
};