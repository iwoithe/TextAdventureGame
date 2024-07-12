#include "killspell.h"

KillSpell::KillSpell()
{
    m_name = String("Kill");
    m_description = String("Kill a random entity in the current room");
}

void KillSpell::cast(const RoomPos& roomPos)
{
    dispatcher()->dispatch("remove-random-enemy-from-room", Parameters({ Any(roomPos) }));
    String().appendColor(Color::Blue, ColorLayer::Foreground).append("You casted the kill spell").appendColor(Color::Default, ColorLayer::Foreground).writeToConsole();
}
