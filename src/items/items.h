#ifndef ITEMS_ITEMS_H
#define ITEMS_ITEMS_H

#include <vector>

#include "iitem.h"

#define ITEM_TYPES_LENGTH 3
enum ItemType {
    Apple,
    Bread,
    None
};

IItem* getRandomItem();

#endif // ITEMS_ITEMS_H
