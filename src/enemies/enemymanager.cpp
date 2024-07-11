#include "enemymanager.h"

#include "enemies/enemies.h"

#include "global/delete.h"
#include "global/random.h"
#include "global/structs.h"

EnemyManager::EnemyManager() {}

EnemyManager::~EnemyManager()
{
    DEL_STD_VEC(m_enemies);
}

void EnemyManager::init()
{
    dispatcher()->reg("enemy-manager-add-enemy-to-room", [&](Parameters params) {
        addEnemyToRoom(params[0].get<RoomPos>());
    });

    dispatcher()->reg("remove-all-enemies-from-room", [&](Parameters params) {
        removeAllEnemiesFromRoom(params[0].get<RoomPos>());
    });

    dispatcher()->reg("remove-random-enemy-from-room", [&](Parameters params) {
        removeRandomEnemyFromRoom(params[0].get<RoomPos>());
    });

    dispatcher()->reg("enemy-manager-attack-in-room", [&](Parameters params) {
        attackInRoom(params[0].get<RoomPos>());
    });

    dispatcher()->reg("enemy-manager-defend-in-room", [&](Parameters params) {
        defendInRoom(params[0].get<RoomPos>());
    });
}

void EnemyManager::deInit() {}

void EnemyManager::addEnemyToRoom(const RoomPos& roomPos)
{
    IEnemy* e = createRandomEnemy(roomPos);
    m_enemies.push_back(e);
}

void EnemyManager::attackInRoom(const RoomPos& roomPos)
{
    for (IEnemy* enemy : m_enemies) {
        if (enemy->roomPos().x == roomPos.x && enemy->roomPos().y == roomPos.y) {
            enemy->attack();
        }
    }
}

void EnemyManager::defendInRoom(const RoomPos& roomPos)
{
    for (IEnemy* enemy : m_enemies) {
        if (enemy->roomPos().x == roomPos.x && enemy->roomPos().y == roomPos.y) {
            enemy->defend();
        }
    }
}

void EnemyManager::removeAllEnemiesFromRoom(const RoomPos& roomPos)
{
    std::erase_if(m_enemies, [&](IEnemy* e) {
        bool shouldDelete = (e->roomPos().x == roomPos.x && e->roomPos().y == roomPos.y);
        if (shouldDelete) {
            delete e;
            e = nullptr;
        }

        return shouldDelete;
    });
}

void EnemyManager::removeRandomEnemyFromRoom(const RoomPos& roomPos)
{
    std::vector<IEnemy*> enemiesInRoom;
    for (int i = 0; i < m_enemies.size(); i++) {
        IEnemy* e = m_enemies[i];
        if (e->roomPos().x == roomPos.x && e->roomPos().y == roomPos.y) {
            enemiesInRoom.push_back(e);
        }

        e = nullptr;
    }

    switch (enemiesInRoom.size()) {
        case 0:
            break;
        case 1:
            delete enemiesInRoom[0];
            break;
        default:
            IEnemy* e = enemiesInRoom[randRange(0, enemiesInRoom.size() - 1)];
            delete e;
            e = nullptr;
            break;
    }
}
