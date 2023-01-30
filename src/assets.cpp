#include "assets.h"

Item* get_item(const unsigned int ID) {
    for(int i = 0; i < item_container.size(); i++) {
        if(item_container[i]->ID == ID) return item_container[i];
    }
    return item_container[0];
}