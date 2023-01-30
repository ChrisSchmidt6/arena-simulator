#include <filesystem>
#include <iostream>
#include <fstream>

#include "Player.h"
#include "utility.h"

void print_separator() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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
            std::cout << "Could not load the character. Corrupted save data.\n";
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
        save_to_file();

        std::cout << "You have created a new character: " << Player::get().name << "\n\n";
        return true;
    }
}