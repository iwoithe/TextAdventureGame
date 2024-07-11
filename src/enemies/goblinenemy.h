#ifndef ENEMIES_GOBLIN_H
#define ENEMIES_GOBLIN_H

#include "ienemy.h"

#include "dispatcher/dispatcher.h"
#include "singleton/singletonmanager.h"

class GoblinEnemy : public IEnemy
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher)
public:
    GoblinEnemy();
    ~GoblinEnemy() = default;

    void init() override;
    void deInit() override;

    void attack() override;
    void defend() override;
private:
    int m_damage;
};

#endif // ENEMIES_GOBLIN_H
