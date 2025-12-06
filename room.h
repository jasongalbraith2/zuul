#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <vector>
#include <cstring>
#include "item.h"

class Room {
    private:
        std::map<const char*, Room*> exits;
        std::vector<Item*> items;
        char* fullDescription;
        char* shortDescription;

    public:
        Room(const char* fDesc, const char* sDesc);
        ~Room();

        void add_exit(const char* exitName, Room* r);
        void add_item(Item* i);
        void print_desc();
        bool has_items();
        Item* get_item();
        const char* get_sdesc();
        std::map<const char*, Room*>& get_exits();
};

#endif