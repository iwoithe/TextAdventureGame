#ifndef ITEMS_APPLEITEM_H
#define ITEMS_APPLEITEM_H

#include "iitem.h"

#include "iwany.h"
#include "dispatcher/dispatcher.h"
#include "singleton/singletonmanager.h"

class AppleItem : public IItem
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher)
public:
    AppleItem();
    ~AppleItem() = default;
    const String& name() const override;
    const String& description() const override;
    void use() override;
private:
    String m_name;
    String m_description;
    int m_healAmount;
};

#endif // ITEMS_APPLEITEM_H
