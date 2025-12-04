/*

main zuul program
to compile on windows lmao:
g++ main.cpp room.cpp item.cpp -o program.exe
or
g++ *.cpp -o program.exe
^^^

good luck!

notes:
current comments are NOT good, do not use
work on main loop
15 rooms. 15 rooms. bruh.

*/

#include <iostream>
#include <vector>
#include <cstring>

#include "room.h"
#include "item.h"

void build_map(std::vector<Room*>& roomVector) {
    /* create all the rooms, add exits, assign items */

    Room* newRoom = new Room("Goofy ahh", "ahh goofy");
    roomVector.push_back(newRoom);
}

int main() {
    /* Player variables */
    Room* currentRoom = nullptr;
    std::vector<Item*> playerItems;

    /* Game variables */
    bool running = true;

    /* Build map */
    std::vector<Room*> rooms;
    build_map(rooms);

    /* Main loop */
    while (running) {
        ;
    }

    /* Deallocate memory */
    for (Room* r : rooms) {
        delete r;
    }
    rooms.clear();

    return 0;
}