#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "File.h"
#include "Player.h"
#include "Vendor.h"

struct Game {
    inline static Vendor apothecary = Vendor("Sandra", 1, VenType::Apothecary);
    inline static Vendor blacksmith = Vendor("Bob", 1, VenType::Blacksmith);
    inline static Vendor chef = Vendor("Emeril", 1, VenType::Chef);
    
    inline static void start() {
        std::cout << "Welcome to Arena Simulator!\n\n";
        active = initiate_character();
    };

    inline static bool is_running() {
        return active;
    };

    inline static void main_menu() {
        int choice;
        while(true) {
            std::cout << "[Main Menu]\n";
            std::cout << "Please enter a corresponding number for the following menu options.\n";
            std::cout << "(0) Exit\n";
            std::cout << "(1) Enter combat\n";
            std::cout << "(2) Go to vendors\n";
            std::cout << "(3) Display statistics\n";
            std::cout << "(4) Display inventory\n";
            std::cout << "(5) Save character\n";

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
                active = false;
                break;
            case 1: {
                std::cout << "Entering combat!\n\n";
                break;
            }
            case 2: {
                std::cout << "Going to vendors...\n\n";
                vendor_menu();
                break;
            }
            case 3:
                Player::display_stats();
                std::cout << "\n";
                break;
            case 4:
                Player::inventory_menu();
                break;
            case 5:
                save_to_file();
                std::cout << "Saved your character.\n";
                break;
            default:
                std::cout << "Please enter a valid option.\n\n";
                break;
        }
    };

    inline static void vendor_menu() {
        int choice = -1;
        while(choice != 0) {
            while(true) {
                std::cout << "[Vendor Select Menu]\n";
                std::cout << "Please enter a corresponding number for the following menu options.\n";
                std::cout << "(0) Go back\n";
                std::cout << "(1) Apothecary\n";
                std::cout << "(2) Blacksmith\n";
                std::cout << "(3) Chef\n";
                std::cout << "(4) Quit game\n";

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
                    apothecary.buy_menu();
                    break;
                case 2:
                    blacksmith.buy_menu();
                    break;
                case 3:
                    chef.buy_menu();
                    break;
                case 4:
                    exit(-1);
                    break;
                default:
                    break;
            }
        }
    };
private:
    inline static bool active = false;

    inline static bool initiate_character() {
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
                std::cout << "\n";

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
                    std::getline(std::cin, Player::name);
                    std::cout << "\n";
                    if(load_save_file()) return true;
                    break;
                case 2:
                    std::cout << "Please enter the name of your new character: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, Player::name);
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
};