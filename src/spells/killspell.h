#ifndef SPELLS_KILLSPELL_H
#define SPELLS_KILLSPELL_H

#include "ispell.h"

#include "dispatcher/dispatcher.h"
#include "singleton/singletonmanager.h"

class KillSpell : public ISpell
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher)
public:
    KillSpell();
    ~KillSpell() = default;
    void cast(const RoomPos& roomPos) override;
};

#endif // SPELLS_KILLSPELL_H
