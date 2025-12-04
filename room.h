#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <vector>
#include <cstring>
#include "item.h"

class Room {
    private:
        std::map<int, Room*> exits;
        std::vector<Item*> items;
        char* fullDescription;
        char* shortDescription;
        int exitCount;

    public:
        Room(const char* fDesc, const char* sDesc);
        ~Room();

        std::vector<Room*> get_exits();
        void add_exit(Room* r);
};

#endif