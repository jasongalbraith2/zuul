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

enum CommandType {
    CMD_GO,
    CMD_GRAB,
    CMD_QUIT,
    CMD_UNKNOWN
};

CommandType parse_command(const char* command) {
    if (strcmp(command, "go") == 0) return CMD_GO;
    if (strcmp(command, "grab") == 0) return CMD_GRAB;
    if (strcmp(command, "quit") == 0) return CMD_QUIT;
    return CMD_UNKNOWN;
}

void build_map(std::vector<Room*>& roomVector) {
    /* create all the rooms, add exits, assign items */

    /*Room* newRoom = new Room("Goofy ahh", "ahh goofy");
    roomVector.push_back(newRoom);*/

    /* Create each room */
    Room* shaftRoom = new Room(
        "Welcome to the starting Room!",
        "Starting room"
    );
    Room* hallway1 = new Room(
        "You hear people chanting. You're getting closer to something",
        "Hallway Section 1"
    );
    Room* hallway2 = new Room(
        "The people are louder!!! You're even closer",
        "Hallway Section 2"
    );
    Room* hallway3 = new Room(
        "Alright, you've confirmed it. We're under Times Square. We're conducting the ball drop!",
        "Hallway Section 3"
    );
    Room* winRoom = new Room(
        "You put together the levers, the ignition fuses, Adam Levine, and the big red button. You try to conduct the ball drop.... it works! Good work C++ TA",
        "Win Room!"
    );

    Room* ballRoomNorth = new Room(
        "Welcome to the Northern Ballroom. This is ballroom 1!",
        "Northern Ballroom"
    );

    Room* ballRoomSouth = new Room(
        "Welcome to the Southern Ballroom. This is ballroom 2",
        "Southern Ballroom"
    );

    Room* grid1LU = new Room(
        "*trumpets flare* Who let you in? This is the underground dance room!",
        "Underground Dance Floor (LU)"
    );
    Room* grid1LD = new Room(
        "*sound decreases to 70db* you think to yourself: finally, its quiet over here.",
        "Underground Seated Area (LD)"
    );
    Room* grid1RU = new Room(
        "*bass shakes your bones* you think to yourself: why did we enter the moshpit?",
        "Underground Moshpit (RU)"
    );
    Room* grid1RD = new Room(
        "*maroon 5 stares you down* what?? Why is Adam Levine here??",
        "Maroon 5's weird concert room (RD)"
    );

    Room* grid2LU = new Room(
        "Room full of fireworks. Decked to the brim. Clearly, this holiday party is insane.",
        "Firework Storage Room"
    );
    Room* grid2RU = new Room(
        "More. Fireworks. How? Are we under the New York ball drop?",
        "...More fireworks storage room..?"
    );
    Room* grid2LD = new Room(
        "We've been underground the whole time? Why can I see into times square??",
        "Times Square Lookout"
    );
    Room* grid2RD = new Room(
        "You scale 2000 floors to look out the Times Square's highest building. You are literally conducting the balldrop",
        "Times Square's Tallest Building!"
    );

    /* Add exits/turns */
    shaftRoom->add_exit("NORTH", ballRoomNorth);
    shaftRoom->add_exit("SOUTH", ballRoomSouth);
    shaftRoom->add_exit("EAST", hallway1);

    hallway1->add_exit("EAST", hallway2);
    hallway1->add_exit("WEST", shaftRoom);
    
    hallway2->add_exit("EAST", hallway3);
    hallway2->add_exit("WEST", hallway1);

    hallway3->add_exit("UHH", winRoom);
    hallway3->add_exit("WEST", hallway2);

    ballRoomNorth->add_exit("SOUTH", shaftRoom);
    ballRoomNorth->add_exit("DOWNSTAIRS", grid1LU);

    ballRoomSouth->add_exit("NORTH", shaftRoom);
    ballRoomSouth->add_exit("STORAGE", grid2LU);

    grid1LU->add_exit("UPSTAIRS", ballRoomNorth);
    grid1LU->add_exit("EAST", grid1RU);
    grid1LU->add_exit("SOUTH", grid1LD);

    grid1LD->add_exit("NORTH", grid1LU);
    grid1LD->add_exit("EAST", grid1RD);

    grid1RD->add_exit("NORTH", grid1RU);
    grid1RD->add_exit("WEST", grid1LD);

    grid1RU->add_exit("SOUTH", grid1RD);
    grid1RU->add_exit("WEST", grid1LU);

    grid2LU->add_exit("EAST", grid2RU);
    grid2LU->add_exit("UP", grid2LD);

    grid2LD->add_exit("DOWN", grid2LU);
    grid2LD->add_exit("DOOR", grid1LU);

    grid2RU->add_exit("WEST", grid2LU);
    grid2RU->add_exit("UP", grid2RD);

    grid2RD->add_exit("DOWN", grid2RU);
    grid2RD->add_exit("DOOR", grid1RU);

    /* Add items */
    Item* adamLevine = new Item("ADAMLEVINE");
    Item* levers = new Item("LEVERS");
    Item* redButton = new Item("REDBUTTON");
    Item* ignitionFuse1 = new Item("FUSE");
    Item* ignitionFuse2 = new Item("FUSE");

    grid1RD->add_item(adamLevine);
    shaftRoom->add_item(levers);
    grid1RU->add_item(redButton);
    grid2LU->add_item(ignitionFuse1);
    grid2RU->add_item(ignitionFuse2);

    /* Add all to vector */
    roomVector = {
        shaftRoom,
        ballRoomNorth,
        ballRoomSouth,
    };
}

int main() {
    /* Player variables */
    Room* currentRoom = nullptr;
    std::vector<Item*> playerItems;

    /* Game variables */
    bool running = true;
    char buffer[32];
    char word1[16];
    char word2[16];
    int count;

    /* Build map */
    std::vector<Room*> rooms;
    build_map(rooms);
    currentRoom = rooms[0];

    /* Main loop */
    currentRoom->print_desc();
    while (running) {
        /* Ask for input */
        std::cout << "> ";
        std::cin.getline(buffer, 32);
        count = sscanf(buffer, "%15s %15s", word1, word2);
        
        switch (parse_command(word1)) {
            case CMD_GO: {
                for (auto& pair : currentRoom->get_exits()) {
                    if (strcmp(word2, pair.first) == 0) {
                        if (strcmp(word2, "UHH") == 0) {
                            if (playerItems.size() == 5) {
                                currentRoom = pair.second;
                                currentRoom->print_desc();
                                std::cout << "Congratulations! You've won!. Type quit to end\n";
                            }
                            else {
                                std::cout << "Can't travel there, pal. You need all 5 items. You currently have: " << playerItems.size() << '\n';
                            }
                        }
                        else {
                            currentRoom = pair.second;
                            currentRoom->print_desc();
                        }
                    }
                }
                break;
            }
            case CMD_GRAB: {
                if (currentRoom->has_items()) {
                    playerItems.push_back(currentRoom->get_item());
                }
                else {
                    std::cout << "No items.\n";
                }
                break;
            }
            case CMD_QUIT: {
                running = false;
                break;
            }
            default: {
                break;
            }
        }
    }

    /* Deallocate memory */
    for (Room* r : rooms) {
        delete r;
    }
    rooms.clear();
    for (Item* i : playerItems) {
        delete i;
    }
    playerItems.clear();

    return 0;
}