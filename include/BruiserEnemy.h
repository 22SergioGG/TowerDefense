#pragma once

#include "Enemy.h"

class BruiserEnemy : public Enemy
{
protected:
    float getMovementSpeed() const override;

public:
    BruiserEnemy();
};
