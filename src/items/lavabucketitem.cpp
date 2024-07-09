#include "lavabucketitem.h"

#include "iwany.h"

LavaBucketItem::LavaBucketItem()
{
    m_name = String("Lava Bucket");
    m_description = String("Destroys all enemies in the current room");
}

const String& LavaBucketItem::name() const
{
    return m_name;
}

const String& LavaBucketItem::description() const
{
    return m_description;
}

void LavaBucketItem::use()
{
    dispatcher()->dispatch("use-lava-bucket", Parameters());
}
