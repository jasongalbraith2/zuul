#include <cstring>

#include "item.h"

Item::Item(const char* name) {
    itemName = new char[strlen(name) + 1];
    strcpy(itemName, name);
}

Item::~Item() {
    delete[] itemName;
}