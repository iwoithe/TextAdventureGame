#ifndef PLAYER_PLAYER_H
#define PLAYER_PLAYER_H

#include <ostream>

#include "async/asyncable.h"
#include "async/channel.h"
#include "async/notification.h"

#include "dispatcher/dispatcher.h"
#include "global/enums.h"
#include "global/igameobject.h"
#include "singleton/singletonmanager.h"

#include "items/iitem.h"
#include "spells/ispell.h"

using namespace app;

struct RoomId {
    int x;
    int y;
};

struct PlayerData {
    RoomId currentRoom;
    int health;
    int maxHealth;
};

struct InventoryItem {
    int id;
    IItem* item;
};

std::ostream& operator<<(std::ostream& os, const PlayerData& playerData);

class Player : public IGameObject
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher);
public:
    Player();
    ~Player();

    void init() override;
    void deInit() override;

    void heal(const int& amount);
    void hurt(const int& amount);

    void moveRoom(Direction dir);

    void addItemToInventory(IItem* item);

    void listInventory();

    void displayStats() const;

    void useInventoryItem(const int& index);

    int inventorySize() const;
    async::Channel<int> inventorySizeChanged();

    int spellSize() const;
    async::Channel<int> spellSizeChanged();

    InventoryItem inventoryItemFromIndex(const int& index);
    InventoryItem inventoryItemFromId(const int& id);

    void addSpell(ISpell* spell);
    void castSpell(int index);
    int findSpellByName(const String& name);
    void listSpells() const;

    void gainRandomSpell();

    async::Notification died();

private:
    PlayerData m_playerData;

    std::vector<InventoryItem> m_inventory;

    int m_itemId;

    async::Channel<int> m_inventorySizeChanged;
    async::Channel<int> m_spellSizeChanged;

    // The known spells to the player
    std::vector<ISpell*> m_spells;

    async::Notification m_died;
};

#endif // PLAYER_PLAYER_H
