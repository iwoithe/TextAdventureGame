#include "appleitem.h"

AppleItem::AppleItem()
{
    m_healAmount = 1;
    m_description = String("An apple. Heals ").append(m_healAmount).append(" health upon eating");
}

const String& AppleItem::description() const
{
    return m_description;
}

void AppleItem::use()
{
    dispatcher()->dispatch("player-heal", Parameters({ Any(m_healAmount) }));
}
