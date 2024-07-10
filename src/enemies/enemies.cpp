#include "enemies.h"

#include "goblin.h"

#include <cstdlib>

// IEnemy* createRandomEnemy()
// {
//     int lowerLimit = 0;
//     int upperLimit = ENEMY_TYPE_LENGTH;
//     int randInt = rand() % (upperLimit - lowerLimit) + lowerLimit;

//     switch (randInt) {
//         case EnemyType::Goblin:
//             return new Goblin();
//         default:
//             return nullptr;
//     }
// }

IEnemy* createRandomEnemy(const RoomPos& roomPos)
{
    int lowerLimit = 0;
    int upperLimit = ENEMY_TYPE_LENGTH;
    int randInt = rand() % (upperLimit - lowerLimit) + lowerLimit;

    IEnemy* e = nullptr;
    switch (randInt) {
        case EnemyType::GoblinT:
        {
            e = new Goblin();
            e->setRoomPos(roomPos);
            break;
        }
    }

    return e;
}
