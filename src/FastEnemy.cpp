#include "FastEnemy.h"

FastEnemy::FastEnemy(int health)
    : Enemy(static_cast<int>(health * 0.75f), 0.75f)
{
}

float FastEnemy::getMovementSpeed() const
{
    return Enemy::getMovementSpeed() * 1.5f;
}
