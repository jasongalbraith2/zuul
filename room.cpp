#include <iostream>
#include <map>
#include <vector>
#include <cstring>

#include "room.h"

Room::Room(const char* fDesc, const char* sDesc) {
    fullDescription = new char[strlen(fDesc) + 1];
    shortDescription = new char[strlen(sDesc) + 1];

    strcpy(fullDescription, fDesc);
    strcpy(shortDescription, sDesc);
}

Room::~Room() {
    for (auto& pair : exits) {
        delete[] pair.first;
    }
    exits.clear();

    delete[] fullDescription;
    delete[] shortDescription;
}

void Room::add_exit(const char* exitName, Room* r) {
    char* temp = new char[strlen(exitName) + 1];
    strcpy(temp, exitName);

    exits.insert({temp, r});
}

void Room::add_item(Item* i) {
    items.push_back(i);
}

void Room::print_desc() {
    std::cout << fullDescription << "\nEXITS:\n";
    for (auto& pair : exits) {
        std::cout << pair.first << " --- " << pair.second->get_sdesc() << '\n';
    }
    std::cout << "ITEMS:\n";
    for (Item* item : items) {
        std::cout << item->get_name() << "\n";
    }
}

bool Room::has_items() {
    return !items.empty();
}

Item* Room::get_item() {
    Item* grabbed = items.front();
    items.erase(items.begin());

    return grabbed;
}

std::map<const char*, Room*>& Room::get_exits() {
    return exits;
}

const char* Room::get_sdesc() {
    return shortDescription;
}