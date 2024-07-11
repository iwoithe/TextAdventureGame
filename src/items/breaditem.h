#ifndef ITEMS_BREADITEM_H
#define ITEMS_BREADITEM_H

#include "iitem.h"

#include "dispatcher/dispatcher.h"
#include "singleton/singletonmanager.h"

class BreadItem : public IItem
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher)
public:
    BreadItem();
    ~BreadItem() = default;
    const String& name() const override;
    const String& description() const override;
    void use(const RoomPos& roomPos) override;
private:
    String m_name;
    String m_description;
    int m_healAmount;
};

#endif //ITEMS_BREADITEM_H
