#ifndef ITEMS_LAVABUCKETITEM_H
#define ITEMS_LAVABUCKETITEM_H

#include "iitem.h"

#include "dispatcher/dispatcher.h"
#include "singleton/singletonmanager.h"

class LavaBucketItem : public IItem
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher)
public:
    LavaBucketItem();
    ~LavaBucketItem() = default;
    const String& name() const override;
    const String& description() const override;
    void use() override;
private:
    String m_name;
    String m_description;
};

#endif // ITEMS_LAVABUCKETITEM_H
