#pragma once

#include "Enemy.h"

class FastEnemy : public Enemy
{
protected:
    float getMovementSpeed() const override;

public:
    FastEnemy(int health);
};
