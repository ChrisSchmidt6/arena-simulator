#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "Game.h"
#include "Player.h"
#include "utility.h"

void Game::start() {
    std::cout << "Welcome to Arena Simulator!\n\n";
    active = initiate_character();
};

bool Game::is_running() {
    return active;
};

void Game::main_menu() {
    int choice;
    while(true) {
        std::cout << "[Main Menu]\n";
        std::cout << "Please enter a corresponding number for the following menu options.\n";
        std::cout << "(0) Exit\n";
        std::cout << "(1) Enter arena\n";
        std::cout << "(2) Go to vendors\n";
        std::cout << "(3) Display statistics\n";
        std::cout << "(4) Display inventory\n";
        std::cout << "(5) Save character\n";

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
            active = false;
            break;
        case 1: {
            std::cout << "Entering combat!\n\n";
            break;
        }
        case 2: {
            Vendor::main_menu(apothecary, blacksmith, chef);
            break;
        }
        case 3:
            Player::get().display_stats();
            std::cout << "\n";
            break;
        case 4:
            Player::get().inventory_menu();
            break;
        case 5:
            save_to_file();
            std::cout << "Saved your character.\n\n";
            break;
        default:
            std::cout << "Please enter a valid option.\n\n";
            break;
    }
};

bool Game::initiate_character() {
    int choice = -1;
    while(choice != 0) {
        while(true) {
            std::cout << "[Start Menu]\n";
            std::cout << "Please enter a corresponding number for the following menu options.\n";
            std::cout << "(0) Exit\n";
            std::cout << "(1) Load character\n";
            std::cout << "(2) Create character\n";

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
                return false;
            case 1:
                std::cout << "Please enter the name of the character you'd like to load: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, Player::get().name);
                std::cout << "\n";
                if(load_save_file()) return true;
                break;
            case 2:
                std::cout << "Please enter the name of your new character: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, Player::get().name);
                std::cout << "\n";
                if(create_save_file()) return true;
                break;
            default:
                std::cout << "Please enter a valid option.\n\n";
                break;
        }
    }
    return false;
};