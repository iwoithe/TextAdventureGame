#include "enemies.h"

#include "goblinenemy.h"

#include <cstdlib>

IEnemy* createRandomEnemy()
{
    int lowerLimit = 0;
    int upperLimit = ENEMY_TYPE_LENGTH;
    int randInt = rand() % (upperLimit - lowerLimit) + lowerLimit;

    IEnemy* e = nullptr;

    switch (randInt) {
        case EnemyType::Goblin:
        {
            e = new GoblinEnemy();
            e->setRoomPos(RoomPos(0, 0));
        }
    }

    return e;
}

IEnemy* createRandomEnemy(const RoomPos& roomPos)
{
    int lowerLimit = 0;
    int upperLimit = ENEMY_TYPE_LENGTH;
    int randInt = rand() % (upperLimit - lowerLimit) + lowerLimit;

    IEnemy* e = nullptr;
    switch (randInt) {
        case EnemyType::Goblin:
        {
            e = new GoblinEnemy();
            e->setRoomPos(roomPos);
            break;
        }
    }

    return e;
}
