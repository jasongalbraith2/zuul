#ifndef ITEM_H
#define ITEM_H

#include <cstring>

class Item {
    private:
        char* itemName;
    
    public:
        Item(const char* name);
        ~Item();
};

#endif