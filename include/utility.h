#pragma once

#include <functional>
#include <string>
#include <vector>
#include <utility>

void print_separator();
bool print_menu(std::vector<std::pair<std::string, std::function<void()>>> menu_items);

void save_to_file();
bool load_save_file();
bool create_save_file();