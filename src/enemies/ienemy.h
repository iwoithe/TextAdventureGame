#ifndef ENEMIES_IENEMY_H
#define ENEMIES_IENEMY_H

#include "iwstring.h"

#include "global/igameobject.h"
#include "global/structs.h"

using namespace iw;

class IEnemy : public IGameObject
{
public:
    const String& name() const { return m_name; }
    const String& description() const { return m_description; }

    virtual void attack() = 0;
    virtual void defend() = 0;

    const RoomPos& roomPos() const { return m_roomPos; }
    void setRoomPos(const RoomPos& rp) { m_roomPos = rp; }
protected:
    String m_name;
    String m_description;

    RoomPos m_roomPos;
};

#endif // ENEMIES_IENEMY_H
