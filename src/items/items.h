#ifndef ITEMS_ITEMS_H
#define ITEMS_ITEMS_H

#include <vector>

#include "iitem.h"

#define ITEM_TYPES_LENGTH 2
enum ItemTypes {
    Apple,
    Bread
};

IItem* getRandomItem();

#endif // ITEMS_ITEMS_H
