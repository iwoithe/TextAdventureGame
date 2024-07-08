#ifndef PLAYER_PLAYER_H
#define PLAYER_PLAYER_H

#include "dispatcher/dispatcher.h"
#include "global/enums.h"
#include "global/igameobject.h"
#include "singleton/singletonmanager.h"

#include <ostream>

struct RoomId {
    int x;
    int y;
};

struct PlayerData {
    RoomId currentRoom;
};


std::ostream& operator<<(std::ostream& os, const PlayerData& playerData);

class Player : public IGameObject
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher);
public:
    Player();
    ~Player() = default;

    void init() override;
    void deInit() override;

    void moveRoom(Direction dir);
private:
    PlayerData m_playerData;
};

#endif // PLAYER_PLAYER_H
