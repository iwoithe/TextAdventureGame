#include "breaditem.h"

#include "iwany.h"
#include "iwstring.h"

BreadItem::BreadItem()
{
    m_healAmount = 3;
    m_name = String("Bread");
    m_description = String("Heals ").append(m_healAmount).append(" health upon eating");
}

const String& BreadItem::name() const
{
    return m_name;
}

const String& BreadItem::description() const
{
    return m_description;
}

void BreadItem::use(const RoomPos& roomPos)
{
    dispatcher()->dispatch("player-heal", Parameters({ Any(m_healAmount )}));
    String("Player healed by ").append(m_healAmount).append(" health").writeToConsole();
}
