#include "appleitem.h"

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

void AppleItem::use()
{
    dispatcher()->dispatch("player-heal", Parameters({ Any(m_healAmount) }));
    String("Player healed by ").append(m_healAmount).append(" health").writeToConsole();
}
