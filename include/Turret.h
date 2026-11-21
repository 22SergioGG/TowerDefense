#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Projectile.h"
#include "Enemy.h"

class Turret
{
private:
    sf::Texture turretBaseTexture;
    sf::Texture turretHeadTexture;

    sf::Sprite turretBaseSprite;
    sf::Sprite turretHeadSprite;

    sf::Vector2i tilePosition;

    float range;
    float fireRate;
    float fireTimer;

    std::vector<std::unique_ptr<Projectile>> projectiles;

public:
    Turret(sf::Vector2i tilePosition);

    void update(float deltaTime, std::vector<std::unique_ptr<Enemy>>& enemies);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

    bool operator==(const Turret& other) const;
};
