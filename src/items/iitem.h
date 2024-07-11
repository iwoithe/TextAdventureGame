#ifndef IITEM_H
#define IITEM_H

#include "iwstring.h"

#include "global/structs.h"

using namespace iw;

class IItem
{
public:
    virtual const String& name() const = 0;
    virtual const String& description() const = 0;
    virtual void use(const RoomPos& roomPos) = 0;
private:
    String m_name;
    String m_description;
};

#endif // IITEM_H
