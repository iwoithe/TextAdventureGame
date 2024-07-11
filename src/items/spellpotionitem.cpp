#include "spellpotionitem.h"

#include "iwany.h"

SpellPotionItem::SpellPotionItem()
{
    m_name = String("Spell Potion");
    m_description = String("Drink to gain a new spell");
}

const String& SpellPotionItem::name() const
{
    return m_name;
}

const String& SpellPotionItem::description() const
{
    return m_description;
}

void SpellPotionItem::use(const RoomPos& roomPos)
{
    dispatcher()->dispatch("player-gain-random-spell", Parameters());
}
