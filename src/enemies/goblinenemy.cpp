#include "goblinenemy.h"

GoblinEnemy::GoblinEnemy()
{
    m_name = String("Goblin");
    m_description = String("Attacks the player");
}

void GoblinEnemy::init() {}

void GoblinEnemy::deInit() {}

void GoblinEnemy::attack()
{
    String("Goblin attack").writeToConsole();
}

void GoblinEnemy::defend()
{
    String("Goblin defend").writeToConsole();
}

