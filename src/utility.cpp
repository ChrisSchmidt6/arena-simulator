#include <filesystem>
#include <iostream>
#include <fstream>
#include <limits>

#include "utility.hpp"
#include "Game.hpp"
#include "Player.hpp"

void print_separator() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

bool print_menu(pairVec menu_items, bool print_plain) {
    Game& game = Game::get();

    int choice = -1;
    while(true) {
        std::cout << "Please enter a corresponding number for the following menu options.\n";

        if(!print_plain) std::cout << "(0) Go back\n";
        for(int i = 0; i < menu_items.size(); i++) {
            // Allow for blank menu options
            if(menu_items[i].first == "Blank") continue;
            int option = print_plain ? i : i + 1;
            std::cout << "(" << (option) << ") " << menu_items[i].first << "\n";
        }
        if(!print_plain) std::cout << "(" << menu_items.size() + 1 << ") Main Menu\n";

        std::cout << "Choice: ";
        std::cin >> choice;
        print_separator();

        if(!std::cin.fail()) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid integer.\n\n";
    }

    if(choice >= 0 && choice < menu_items.size() && menu_items[choice].first == "Blank") {
        std::cout << "Please enter a valid option.\n\n";
        return true;
    }

    if(print_plain) {
        if(choice >= 0 && choice < menu_items.size()) {
            // Call function associated with menu choice
            menu_items[choice].second();
        } else {
            std::cout << "Please enter a valid option.\n\n";
        }
    } else {
        if(choice > 0 && choice <= menu_items.size()) {
            // Call function associated with menu choice
            menu_items[choice - 1].second();
        } else if(choice == menu_items.size() + 1) {
            game.toggle_menu_reset();
        } else if(choice == 0) {
            return false;
        } else {
            std::cout << "Please enter a valid option.\n\n";
        }
    }

    return game.menu_status();
}

void confirmation_menu(std::string question, std::function<void()> action) {
    pairVec menu_items;
    bool return_early;

    do {
        std::cout << question << "\n\n";
        std::cout << "[Confirmation Menu]\n";

        menu_items.clear();

        menu_items.push_back(std::make_pair("Blank", []() -> void {}));

        menu_items.push_back(std::make_pair("Yes", [action, &return_early]() -> void {
            action();
            return_early = true;
        }));

        menu_items.push_back(std::make_pair("No", [&return_early]() -> void {
            return_early = true;
        }));
    } while(print_menu(menu_items, true) && !return_early);
}

void pause_until_enter() {
    std::cout << "Press Enter to continue ...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(std::cin.peek() != '\n') { std::cin.get(); }
    print_separator();
}

std::string directory = "saves/";

void save_to_file() {
    std::fstream save_file;
    save_file.open(directory + Player::get().name + ".txt", std::fstream::out);
    save_file << Player::get().get_save_data();
    save_file.close();
}

bool load_save_file() {
    std::fstream save_file;

    save_file.open(directory + Player::get().name + ".txt");

    if(!save_file.is_open()) {
        std::cout << "That character does not exist.\n\n";
        return false;
    } else {
        std::string save_file_data;
        std::string line;

        while(std::getline(save_file, line)) {
            save_file_data.append(line + '\n');
        }
        save_file.close();
        
        bool loadSuccess = Player::get().load_save_data(save_file_data);
        if(loadSuccess) {
            std::cout << "You have successfully loaded character: " << Player::get().name << "\n\n";
            return true;
        } else {
            std::cout << "Could not load the character. Corrupted save data.\n\n";
            return false;
        }
    }
}

bool create_save_file() {
    std::filesystem::create_directory("saves");
    std::fstream save_file;
    save_file.open(directory + Player::get().name + ".txt");

    if(save_file.is_open()) {
        save_file.close();
        std::cout << "That character already exists.\n\n";
        return false;
    } else {
        Player::get().reset_player_data();
        save_to_file();

        std::cout << "You have created a new character: " << Player::get().name << "\n\n";
        return true;
    }
}