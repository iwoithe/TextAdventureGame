#ifndef ENEMIES_ENEMYMANAGER_H
#define ENEMIES_ENEMYMANAGER_H

#include "ienemy.h"

#include <vector>

#include "global/igameobject.h"

#include "dispatcher/dispatcher.h"
#include "singleton/singletonmanager.h"

class EnemyManager : public IGameObject
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher)
public:
    EnemyManager();
    ~EnemyManager();
    void init() override;
    void deInit() override;

    void addEnemyToRoom(const RoomPos& roomPos);

    void attackInRoom(const RoomPos& roomPos);
    void defendInRoom(const RoomPos& roomPos);

private:
    std::vector<IEnemy*> m_enemies;
};

#endif // ENEMIES_ENEMYMANAGER_H
