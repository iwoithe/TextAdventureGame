#include "killspell.h"

KillSpell::KillSpell()
{
    m_name = String("Kill");
    m_description = String("Kill a random entity in the current room");
}

void KillSpell::cast()
{
    String("Kill spell casted").writeToConsole();
}
