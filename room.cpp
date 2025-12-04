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
        delete pair.second;
    }
    exits.clear();

    delete[] fullDescription;
    delete[] shortDescription;
}