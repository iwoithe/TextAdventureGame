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
            if (enemy != nullptr) {
                enemy->attack();
            }
        }
    }
}

void EnemyManager::defendInRoom(const RoomPos& roomPos)
{
    for (IEnemy* enemy : m_enemies) {
        if (enemy->roomPos().x == roomPos.x && enemy->roomPos().y == roomPos.y) {
            if (enemy != nullptr) {
                enemy->defend();
            }
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
    std::vector<int> enemiesInRoomIndexes;
    for (int i = 0; i < m_enemies.size(); i++) {
        if (m_enemies[i]->roomPos().x == roomPos.x && m_enemies[i]->roomPos().y == roomPos.y) {
            enemiesInRoomIndexes.push_back(i);
        }
    }

    switch (enemiesInRoomIndexes.size()) {
        case 0:
            break;
        case 1:
            delete m_enemies[0];
            m_enemies.clear();
            break;
        default:
            int index = enemiesInRoomIndexes[randRange(0, enemiesInRoomIndexes.size() - 1)];
            IEnemy* e = m_enemies[index];
            delete e;
            e = nullptr;
            m_enemies.erase(m_enemies.begin() + index);
            break;
    }
}
