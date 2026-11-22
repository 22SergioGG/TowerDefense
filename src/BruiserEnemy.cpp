#include "BruiserEnemy.h"

BruiserEnemy::BruiserEnemy(int health)
    : Enemy(static_cast<int>(health * 1.25f), 1.25f)
{
}

float BruiserEnemy::getMovementSpeed() const
{
    return Enemy::getMovementSpeed() * 0.8f;
}
