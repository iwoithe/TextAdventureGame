#include "items.h"
#include "appleitem.h"
#include "breaditem.h"
#include "stubitem.h"

#include <cstdlib>

IItem* getRandomItem()
{
    int lowerLimit = 0;
    int upperLimit = ITEM_TYPES_LENGTH;
    int randInt = rand() % (upperLimit - lowerLimit) + lowerLimit;

    switch (randInt) {
        case ItemType::Apple:
            return new AppleItem();
        case ItemType::Bread:
            return new BreadItem();
        case ItemType::None:
            return nullptr;
        default:
            return new StubItem();
    }
}
