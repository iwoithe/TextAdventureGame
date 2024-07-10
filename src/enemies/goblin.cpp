#include "goblin.h"

Goblin::Goblin()
{
    m_name = String("Goblin");
    m_description = String("Attacks the player");
}

void Goblin::init() {}

void Goblin::deInit() {}

void Goblin::attack()
{
    String("Goblin attack").writeToConsole();
}

void Goblin::defend()
{
    String("Goblin defend").writeToConsole();
}

