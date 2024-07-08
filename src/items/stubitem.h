#ifndef STUBITEM_H
#define STUBITEM_H

#include "iitem.h"

class StubItem : public IItem
{
public:
    StubItem() {};
    ~StubItem() {};
    const String& name() const override { return m_name; };
    const String& description() const override { return m_description; };
    void use() override {};
private:
    String m_name;
    String m_description;
};

#endif // STUBITEM_H
