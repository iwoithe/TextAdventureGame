#include "goblinenemy.h"

GoblinEnemy::GoblinEnemy()
{
    m_damage = 2;
    m_name = String("Goblin");
    m_description = String("Attacks the player, gives ").append(m_damage).append(" damage");
}

void GoblinEnemy::init() {}

void GoblinEnemy::deInit() {}

void GoblinEnemy::attack()
{
    String().appendColor(Color::Red, ColorLayer::Foreground).append("A goblin has attacked you").appendColor(Color::Default, ColorLayer::Foreground).writeToConsole();
    dispatcher()->dispatch("player-hurt", Parameters({ Any(m_damage) }));
}

void GoblinEnemy::defend()
{
    String().appendColor(Color::Red, ColorLayer::Foreground).append("A goblin has defended itself").appendColor(Color::Default, ColorLayer::Foreground).writeToConsole();
}

