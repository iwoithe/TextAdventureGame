#ifndef SPELLS_SPELLS_H
#define SPELLS_SPELLS_H

#include "ispell.h"

#define SPELL_TYPE_LENGTH 1

enum SpellType {
    Kill
};

ISpell* getRandomSpell();

#endif //SPELLS_SPELLS_H
