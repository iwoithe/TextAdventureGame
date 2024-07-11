#include "appleitem.h"

#include "iwany.h"
#include "iwstring.h"

AppleItem::AppleItem()
{
    m_healAmount = 1;
    m_name = String("Apple");
    m_description = String("Heals ").append(m_healAmount).append(" health upon eating");
}

const String& AppleItem::name() const
{
    return m_name;
}

const String& AppleItem::description() const
{
    return m_description;
}

void AppleItem::use(const RoomPos& roomPos)
{
    dispatcher()->dispatch("player-heal", Parameters({ Any(m_healAmount) }));
    String("Player healed by ").append(m_healAmount).append(" health").writeToConsole();
}
