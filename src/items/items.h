#ifndef ITEMS_ITEMS_H
#define ITEMS_ITEMS_H

#include <vector>

#include "iitem.h"

#include "appleitem.h"

#define ITEM_TYPES_LENGTH 1
enum ItemTypes {
    Apple
};

IItem* getRandomItem();

#endif // ITEMS_ITEMS_H
