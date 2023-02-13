#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "Game.hpp"
#include "Player.hpp"
#include "utility.hpp"

void Game::start() {
    std::cout << "Welcome to Arena Simulator!\n\n";
    active = initiate_character();
    if(active) generate_inventories();
};

bool Game::is_running() {
    return active;
};

void Game::main_menu() {
    pairVec menu_items;
    // Return early if Quit game is selected
    bool return_early = false;
    
    do {
        std::cout << "[Main Menu]\n";
        menu_items.clear();

        menu_items.push_back(std::make_pair("Quit game", [this, &return_early]() -> void {
            active = false;
            return_early = true;
        }));

        menu_items.push_back(std::make_pair("Enter arena", [this]() -> void {
            arena.main_menu();
        }));

        menu_items.push_back(std::make_pair("Go to market", [this]() -> void {
            Vendor::main_menu(apothecary, blacksmith, chef);
        }));

        menu_items.push_back(std::make_pair("Display statistics", []() -> void {
            Player::get().display_stats();
            pause_until_enter();
        }));

        menu_items.push_back(std::make_pair("Display inventory", []() -> void {
            Player::get().inventory_menu();
        }));

        menu_items.push_back(std::make_pair("Save character", []() -> void {
            save_to_file();
            std::cout << "Your character has been saved.\n";
            pause_until_enter();
        }));
    } while(print_menu(menu_items, true) && !return_early);
};

void Game::generate_inventories() {
    apothecary.generate_inventory();
    blacksmith.generate_inventory();
    chef.generate_inventory();
};

bool Game::initiate_character() {
    pairVec menu_items;

    bool success_initiating = false;
    bool return_early = false;

    do {
        std::cout << "[Start Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Exit", [this, &return_early]() -> void {
            active = false;
            return_early = true;
        }));

        menu_items.push_back(std::make_pair("Create character", [&success_initiating]() -> void {
            std::cout << "Please enter the name of your new character: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, Player::get().name);
            std::cout << "\n";
            if (create_save_file()) success_initiating = true;
        }));

        menu_items.push_back(std::make_pair("Load character", [&success_initiating]() -> void {
            std::cout << "Please enter the name of the character you would like to load: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, Player::get().name);
            std::cout << "\n";
            if (load_save_file()) success_initiating = true;
        }));
    } while (print_menu(menu_items, true) && (!success_initiating && !return_early));

    return success_initiating;
};