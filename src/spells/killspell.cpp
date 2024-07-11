#include "killspell.h"

KillSpell::KillSpell()
{
    m_name = String("Kill");
    m_description = String("Kill a random entity in the current room");
}

void KillSpell::cast(const RoomPos& roomPos)
{
    dispatcher()->dispatch("remove-random-enemy-from-room", Parameters({ Any(roomPos) }));
    String("Kill spell casted").writeToConsole();
}
