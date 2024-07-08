#include "player.h"

#include "global/log.h"

std::ostream& operator<<(std::ostream& os, const PlayerData& playerData) {
    return os << "currentRoom: (" << playerData.currentRoom.x << ", " << playerData.currentRoom.y << ")" << std::endl;
}

Player::Player()
{
    m_playerData = PlayerData(RoomId(0, 0));
}

void Player::init()
{
    dispatcher()->reg("player-move-room", [&](Parameters p) {
        moveRoom(p[0].get<Direction>());
    });
}

void Player::deInit() {}

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

    DEBUG(m_playerData);
}
