#ifndef ROOM_H
#define ROOM_H

#include "iwstring.h"
#include "items/iitem.h"

using namespace iw;

struct RoomPos
{
    int x;
    int y;
};

class Room
{
public:
    Room();
    Room(const String& description);
    Room(IItem* item);
    Room(const RoomPos& roomPos);
    Room(const String& description, IItem* item, const RoomPos& roomPos);
    ~Room();

    IItem* item() const;
    const bool isEmpty() const;
    void removeItem();

    const RoomPos& roomPos() const;
    void setRoomPos(const RoomPos& roomPos);

private:
    String m_description;
    IItem* m_item;
    RoomPos m_pos;
};

#endif // ROOM_H
