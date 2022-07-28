#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "Player.h"
#include "File.h"
#include "Enemy.h"
#include "Vendor.h"

struct Game {
    inline static int choice = -1;
    inline static Vendor bob = Vendor("Bob");
    inline static Enemy sauron = Enemy("Sauron", );

    inline static void start() {
        std::cout << "Welcome to RPG simulator!" << std::endl << std::endl;
        active = initiate_character();
    };

    inline static bool is_running() {
        return active;
    };

    inline static bool initiate_character() {
        std::cout << "Please enter a corresponding number for the following menu options." << std::endl;
        std::cout << "(0) Exit" << std::endl;
        std::cout << "(1) Load character" << std::endl;
        std::cout << "(2) Create character" << std::endl;
        
        while(true) {
            std::cout << "Choice: ";
            try {
                std::cin >> choice;
            } catch(std::exception e) {
                std::cout << "Please enter a number." << std::endl;
                std::cout << std::endl;
                continue;
            }

            try {
                switch(choice) {
                    case 0:
                        return false;
                    case 1:
                        std::cout << "Please enter the name of the character you'd like to load: ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(std::cin, Player::name);
                        std::cout << std::endl;
                        return load_save_file();
                    case 2:
                        std::cout << "Please enter the name of a new character: ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(std::cin, Player::name);
                        std::cout << std::endl;
                        return create_save_file();
                    default:
                        std::cout << "That was not an option." << std::endl;
                        break;
                }
            } catch(std::exception e) {
                std::cout << "Could not initiate character!" << std::endl;
                return false;
            }
        }
    };

    inline static void main_menu() {
        choice = -1;
        std::cout << "Please enter a corresponding number for the following menu options." << std::endl;
        std::cout << "(0) Exit" << std::endl;
        std::cout << "(1) Enter combat" << std::endl;
        std::cout << "(2) Go to vendors" << std::endl;
        std::cout << "(3) Display statistics" << std::endl;
        std::cout << "(4) Display inventory" << std::endl;
        std::cout << "(5) Save character" << std::endl;

        std::cout << "Choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch(choice) {
            case 0:
                active = false;
                break;
            case 1: {
                std::cout << "Entering combat!" << std::endl;
                sauron.display_stats();
                std::cout << std::endl;
                break;
            }
            case 2: {
                std::cout << "Going to vendors..." << std::endl << std::endl;
                bob.display_greeting();
                bob.buy_item();
                break;
            }
            case 3:
                Player::display_stats();
                std::cout << std::endl;
                break;
            case 4:
                Player::display_inventory();
                std::cout << std::endl;
                break;
            case 5:
                save_to_file();
                std::cout << "Saved your character." << std::endl;
                break;
            default:
                std::cout << "That was not an option." << std::endl;
                break;
        }
    };
private:
    inline static bool active = false;
};