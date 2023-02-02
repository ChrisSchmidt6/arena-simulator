#include <iostream>

#include "arena.h"
#include "utility.h"
#include "Enemy.h"

void arena_menu() {
    pairVec menu_items;

    do {
        std::cout << "Welcome to the arena! You can expect formidable foes if you dare to fight.\n\n";
        std::cout << "[Arena Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Fight", []() -> void {
            Enemy::generate_enemy();
            std::cout << "The fight starts!\n";
        }));

        menu_items.push_back(std::make_pair("Train", []() -> void {
            std::cout << "You will have to pay gold to train.\n";
        }));

    } while(print_menu(menu_items));
}