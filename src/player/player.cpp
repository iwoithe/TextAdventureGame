#include "player.h"

#include "iwstring.h"

#include "global/algorithms.h"
#include "global/delete.h"
#include "global/log.h"

#include "spells/spells.h"

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

    DEL_STD_VEC(m_spells);
}

void Player::init()
{
    dispatcher()->reg("player-add-item-to-inventory", [&](Parameters params) {
        addItemToInventory(params[0].get<IItem*>());
    });

    dispatcher()->reg("player-list-spells", [&](Parameters params) {
        listSpells();
    });

    dispatcher()->reg("player-cast-spell", [&](Parameters params) {
        castSpell(params[0].get<int>());
    });

    dispatcher()->reg("player-list-inventory", [&](Parameters params) {
        listInventory();
    });

    dispatcher()->reg("player-use-inventory-item", [&](Parameters params) {
        useInventoryItem(params[0].get<int>());
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

    dispatcher()->reg("player-gain-random-spell", [&](Parameters params) {
        gainRandomSpell();
    });

    dispatcher()->reg("player-hurt", [&](Parameters params) {
        hurt(params[0].get<int>());
    });
}

void Player::deInit() {}

void Player::heal(const int& amount)
{
    m_playerData.health += amount;
    if (m_playerData.health > m_playerData.maxHealth) {
        // Clamp health to maximum health
        m_playerData.health = m_playerData.maxHealth;
    }

    String("Health: ").append(m_playerData.health).writeToConsole();
}

void Player::hurt(const int& amount)
{
    m_playerData.health -= amount;
    if (m_playerData.health <= 0) {
        m_playerData.health = 0;
        m_died.notify();
    }
}

async::Notification Player::died()
{
    return m_died;
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
    if (item == nullptr) {
        return;
    }

    m_inventory.push_back(InventoryItem(m_itemId++, item));
    m_inventorySizeChanged.send(m_inventory.size());
}

void Player::listInventory()
{
    for (int i = 0; i < m_inventory.size(); i++) {
        String inventoryText;
        inventoryText.appendColor(Color::Blue, ColorLayer::Foreground);
        // Listed 1-based, not 0-index
        InventoryItem item = m_inventory[i];
        inventoryText.append(i + 1).append(":");
        inventoryText.appendColor(Color::Default, ColorLayer::Foreground);
        inventoryText.append(" ").append(item.item->name()).append(" ");
        inventoryText.appendColor(Color::Yellow, ColorLayer::Foreground);
        inventoryText.append(item.item->description());
        inventoryText.appendColor(Color::Default, ColorLayer::Foreground);
        inventoryText.writeToConsole();
    }
}

void Player::displayStats() const
{
    String stats;
    stats.appendColor(Color::Cyan, ColorLayer::Foreground);
    stats.append("Player Stats:\n");
    stats.append("Current Room: (").append(m_playerData.currentRoom.x).append(", ").append(m_playerData.currentRoom.y).append(")\n");
    stats.append("Health: ").append(m_playerData.health);
    stats.appendColor(Color::Default, ColorLayer::Foreground);
    stats.writeToConsole();
}

void Player::useInventoryItem(const int& index)
{
    InventoryItem item = inventoryItemFromIndex(index);
    if (item.item == nullptr) {
        return;
    }

    item.item->use();
    delete item.item;
    m_inventory.erase(m_inventory.begin() + index);
    m_inventorySizeChanged.send(m_inventory.size());
}

int Player::inventorySize() const
{
    return m_inventory.size();
}

async::Channel<int> Player::inventorySizeChanged()
{
    return m_inventorySizeChanged;
}

int Player::spellSize() const
{
    return m_spells.size();
}

async::Channel<int> Player::spellSizeChanged()
{
    return m_spellSizeChanged;
}

InventoryItem Player::inventoryItemFromIndex(const int& index)
{
    if (index < 0 || index >= m_inventory.size()) {
        return InventoryItem();
    }

    return m_inventory[index];
}

InventoryItem Player::inventoryItemFromId(const int& id)
{
    for (int i = 0; i < m_inventory.size(); i++) {
        if (m_inventory[i].id == id) {
            return m_inventory[i];
        }
    }

    return InventoryItem();
}

void Player::addSpell(ISpell* spell)
{
    if (spell == nullptr) {
        return;
    }

    m_spells.push_back(spell);
    m_spellSizeChanged.send(m_spells.size());
}

int Player::findSpellByName(const String& name)
{
    return binarySearch<ISpell*, String>(m_spells, name);
}

void Player::castSpell(int index)
{
    if (index < 0 || index >= m_spells.size()) {
        return;
    }

    m_spells[index]->cast(RoomPos(m_playerData.currentRoom.x, m_playerData.currentRoom.y));
}

void Player::listSpells() const
{
    for (int i = 0; i < m_spells.size(); i++) {
        String spellStr;
        spellStr.appendColor(Color::Blue, ColorLayer::Foreground);
        spellStr.append(i + 1);
        spellStr.append(":");
        spellStr.appendColor(Color::Default, ColorLayer::Foreground);
        spellStr.append(" ").append(m_spells[i]->name()).append(" ");
        spellStr.appendColor(Color::Yellow, ColorLayer::Foreground);
        spellStr.append(m_spells[i]->description());
        spellStr.appendColor(Color::Default, ColorLayer::Foreground);
        spellStr.writeToConsole();
    }
}

void Player::gainRandomSpell()
{
    ISpell* newSpell = getRandomSpell();
    addSpell(newSpell);
}
