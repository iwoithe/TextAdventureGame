#include "enemymanager.h"

#include "enemies/enemies.h"

#include "global/delete.h"
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
