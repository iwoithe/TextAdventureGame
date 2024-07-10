#ifndef ENEMIES_GOBLIN_H
#define ENEMIES_GOBLIN_H

#include "ienemy.h"

class Goblin : public IEnemy
{
public:
    Goblin();
    ~Goblin() = default;

    void init() override;
    void deInit() override;

    void attack() override;
    void defend() override;
};

#endif // ENEMIES_GOBLIN_H
