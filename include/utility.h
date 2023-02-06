#pragma once

#include <functional>
#include <string>
#include <vector>
#include <utility>

typedef std::vector<std::pair<std::string, std::function<void()>>> pairVec;

void print_separator();
bool print_menu(pairVec menu_items, bool print_plain = false);
void pause_until_enter();

void save_to_file();
bool load_save_file();
bool create_save_file();