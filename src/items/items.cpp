#include "items.h"

#include "appleitem.h"
#include "breaditem.h"
#include "lavabucketitem.h"
#include "spellpotionitem.h"
#include "stubitem.h"

#include <cstdlib>

IItem* getRandomItem()
{
    int lowerLimit = 0;
    int upperLimit = ITEM_TYPE_LENGTH;
    int randInt = rand() % (upperLimit - lowerLimit) + lowerLimit;

    switch (randInt) {
        case ItemType::Apple:
            return new AppleItem();
        case ItemType::Bread:
            return new BreadItem();
        case ItemType::LavaBucket:
            return new LavaBucketItem();
        case ItemType::SpellPotion:
            return new SpellPotionItem();
        case ItemType::None:
            return nullptr;
        default:
            return new StubItem();
    }
}
