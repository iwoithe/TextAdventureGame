#include "player.h"

#include "iwstring.h"

#include "global/delete.h"
#include "global/log.h"

std::ostream& operator<<(std::ostream& os, const PlayerData& playerData) {
    os << "currentRoom: (" << playerData.currentRoom.x << ", " << playerData.currentRoom.y << ")" << std::endl;
    os << "health: " << playerData.health << std::endl;
    os << "maxHealth: " << playerData.maxHealth << std::endl;
    return os;
}

Player::Player()
{
    m_itemId = 0;
    m_playerData = PlayerData(RoomId(0, 0));
    m_playerData.maxHealth = 20;
    m_playerData.health = m_playerData.maxHealth;
}

Player::~Player()
{
    for (InventoryItem item : m_inventory) {
        DEL_PTR_S(item.item);
    }
}

void Player::init()
{
    dispatcher()->reg("player-add-item-to-inventory", [&](Parameters params) {
        addItemToInventory(params[0].get<IItem*>());
    });

    dispatcher()->reg("player-display-inventory", [&](Parameters params) {
        displayInventory();
    });

    dispatcher()->reg("player-display-stats", [&](Parameters params) {
        displayStats();
    });

    dispatcher()->reg("player-heal", [&](Parameters params) {
        heal(params[0].get<int>());
    });

    dispatcher()->reg("player-move-room", [&](Parameters params) {
        moveRoom(params[0].get<Direction>());
    });
}

void Player::deInit() {}

void Player::heal(const int& amount)
{
    if (m_playerData.health + amount > m_playerData.maxHealth) {
        // Clamp health to maximum health
        m_playerData.health = m_playerData.maxHealth;
    }

    m_playerData.health += amount;
    String("Health: ").append(m_playerData.health).writeToConsole();
}

void Player::moveRoom(Direction dir)
{
    switch (dir) {
        case Direction::Left:
            m_playerData.currentRoom.x -= 1;
            break;
        case Direction::Up:
            m_playerData.currentRoom.y += 1;
            break;
        case Direction::Right:
            m_playerData.currentRoom.x += 1;
            break;
        case Direction::Down:
            m_playerData.currentRoom.y -= 1;
            break;
    }
}

void Player::addItemToInventory(IItem* item)
{
    if (item != nullptr) {
        m_inventory.push_back(InventoryItem(m_itemId++, item));
    }
}

void Player::displayInventory()
{
    for (InventoryItem item : m_inventory) {
        String("------").writeToConsole();
        String("Item ID: ").append(item.id).writeToConsole();
        if (item.item != nullptr) {
            String("Item Description: ").append(item.item->description()).writeToConsole();
        }
    }
}

void Player::displayStats() const
{
    String stats;
    stats.append("currentRoom: (").append(m_playerData.currentRoom.x).append(", ").append(m_playerData.currentRoom.y).append(")\n");
    stats.append("health: ").append(m_playerData.health).append("\n");
    stats.append("maxHealth: ").append(m_playerData.maxHealth);
    stats.writeToConsole();
}

InventoryItem Player::inventoryItemFromIndex(const int& index)
{
    if (index >= 0 && index < m_inventory.size()) {
        return InventoryItem();
    }

    return m_inventory[index];
}

InventoryItem Player::inventoryItemFromId(const int& id)
{
    for (int i = 0; i < m_inventory; i++) {
        if (m_inventory[i].id == id) {
            return m_inventory[i];
        }
    }

    return InventoryItem();
}
