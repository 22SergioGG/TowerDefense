#include "BruiserEnemy.h"

BruiserEnemy::BruiserEnemy()
    : Enemy(150, 1.5f)
{
}

float BruiserEnemy::getMovementSpeed() const
{
    return Enemy::getMovementSpeed() * 0.8f;
}
