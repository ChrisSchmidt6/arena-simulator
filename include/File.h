#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>

#include "Player.h"

std::string directory = "saves/";

void save_to_file() {
    std::fstream save_file;
    save_file.open(directory + Player::name + ".txt", std::fstream::out);
    save_file << Player::get_save_data();
    save_file.close();
}

bool load_save_file() {
    std::fstream save_file;

    save_file.open(directory + Player::name + ".txt");

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
        
        bool loadSuccess = Player::load_save_data(save_file_data);
        if(loadSuccess) {
            std::cout << "You have loaded the following character:\n";
            std::cout << "Name: " << Player::name << "\n";
            std::cout << Player::get_save_data() << "\n";
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
    save_file.open(directory + Player::name + ".txt");

    if(save_file.is_open()) {
        save_file.close();
        std::cout << "That character already exists.\n\n";
        return false;
    } else {
        save_to_file();

        std::cout << "You have created the following character:\n";
        std::cout << "Name: " << Player::name << "\n";
        std::cout << Player::get_save_data() << "\n";
        return true;
    }
}