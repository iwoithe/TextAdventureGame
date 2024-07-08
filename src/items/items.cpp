#include "items.h"
#include "stubitem.h"

#include <cstdlib>

IItem* getRandomItem()
{
    int lowerLimit = 0;
    int upperLimit = ITEM_TYPES_LENGTH;
    int randInt = rand() % (upperLimit - lowerLimit + 1) + lowerLimit;

    switch (randInt) {
        case Apple:
            return new AppleItem();
        default:
            return new StubItem();
    }
}
