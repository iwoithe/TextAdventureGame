#ifndef ITEMS_ITEMS_H
#define ITEMS_ITEMS_H

#include "iitem.h"

#define ITEM_TYPE_LENGTH 5

enum ItemType {
    Apple,
    Bread,
    LavaBucket,
    SpellPotion,
    None
};

IItem* getRandomItem();

#endif // ITEMS_ITEMS_H
