#include "spells.h"

#include "killspell.h"

#include <cstdlib>

ISpell* getRandomSpell()
{
    // TODO: Stop the player from getting the same spell twice (one instance is enough)
    int lowerLimit = 0;
    int upperLimit = SPELL_TYPE_LENGTH;
    int randInt = rand() % (upperLimit - lowerLimit) + lowerLimit;

    switch (randInt) {
        case SpellType::Kill:
            return new KillSpell();
        default:
            return nullptr;
    }
}
