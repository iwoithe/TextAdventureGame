#ifndef ENEMIES_GOBLIN_H
#define ENEMIES_GOBLIN_H

#include "ienemy.h"

class GoblinEnemy : public IEnemy
{
public:
    GoblinEnemy();
    ~GoblinEnemy() = default;

    void init() override;
    void deInit() override;

    void attack() override;
    void defend() override;
};

#endif // ENEMIES_GOBLIN_H
