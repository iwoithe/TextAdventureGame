#ifndef STUBITEM_H
#define STUBITEM_H

#include "iitem.h"

class StubItem : public IItem
{
public:
    StubItem() { m_name = "Stub Item"; m_description = "A stub item"; };
    ~StubItem() {};
    const String& name() const override { return m_name; };
    const String& description() const override { return m_description; };
    void use() override {};
private:
    String m_name;
    String m_description;
};

#endif // STUBITEM_H
