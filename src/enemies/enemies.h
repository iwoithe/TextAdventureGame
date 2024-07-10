#ifndef ENEMIES_ENEMIES_H
#define ENEMIES_ENEMIES_H

#include "ienemy.h"

#include "global/structs.h"

#define ENEMY_TYPE_LENGTH 1

enum EnemyType {
    Goblin
};

// IEnemy* createRandomEnemy();
IEnemy* createRandomEnemy(const RoomPos& roomPos);

#endif // ENEMIES_ENEMIES_H
