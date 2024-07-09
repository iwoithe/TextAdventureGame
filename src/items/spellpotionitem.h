#ifndef ITEMS_SPELLPOTIONITEM_H
#define ITEMS_SPELLPOTIONITEM_H

#include "iitem.h"

#include "dispatcher/dispatcher.h"
#include "singleton/singletonmanager.h"

class SpellPotionItem : public IItem
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher)
public:
    SpellPotionItem();
    ~SpellPotionItem() = default;
    const String& name() const override;
    const String& description() const override;
    void use() override;
private:
    String m_name;
    String m_description;
};

#endif // ITEMS_SPELLPOTIONITEM_H
