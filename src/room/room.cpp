#include "room.h"

#include "items/stubitem.h"

Room::Room()
{
    m_description = String("");
    m_item = new StubItem();
    m_pos = RoomPos(0, 0);
}

Room::Room(const String& description)
{
    m_description = description;
    m_item = new StubItem();
    m_pos = RoomPos(0, 0);
}

Room::Room(IItem* item)
{
    m_description = String("");
    m_item = item;
    m_pos = RoomPos(0, 0);
}

Room::Room(const RoomPos& roomPos)
{
    m_description = String("");
    m_item = new StubItem();
    m_pos = roomPos;
}

Room::Room(const String& description, IItem* item, const RoomPos& roomPos)
{
    m_description = description;
    m_item = item;
    m_pos = roomPos;
}

Room::~Room()
{
    if (m_item != nullptr) {
        delete m_item;
    }
}

IItem* Room::item() const
{
    return m_item;
}

const bool Room::isEmpty() const
{
    return (m_item == nullptr);
}

void Room::removeItem()
{
    // Basically when the item is picked up by the player
    // Don't delete the pointer, ownership transferred to the player class
    // But this does mean be careful using this method as it doesn't delete the pointer
    m_item = nullptr;
}

const RoomPos& Room::roomPos() const
{
    return m_pos;
}

void Room::setRoomPos(const RoomPos& roomPos)
{
    m_pos = roomPos;
}
