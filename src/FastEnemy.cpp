#include "FastEnemy.h"

FastEnemy::FastEnemy()
    : Enemy(50, 0.75f)
{
}

float FastEnemy::getMovementSpeed() const
{
    return Enemy::getMovementSpeed() * 1.5f;
}
