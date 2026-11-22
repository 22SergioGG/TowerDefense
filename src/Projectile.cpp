#include "Projectile.h"

#include <cmath>

Projectile::Projectile(sf::Vector2f startPosition, sf::Vector2f targetPosition)
    : projectileTexture("assets/projectile.png"),
    projectileSprite(projectileTexture),
    speed(1500.f),
    damage(25)
{
    projectileSprite.setPosition(startPosition);

    sf::Vector2f difference = targetPosition - startPosition;

    float distance = std::hypot(difference.x, difference.y);

    if (distance != 0.f)
    {
        direction = difference / distance;
    }
    else
    {
        direction = { 0.f, 0.f };
    }
}

void Projectile::update(float deltaTime)
{
    projectileSprite.move(direction * speed * deltaTime);
}

void Projectile::draw(sf::RenderWindow& window) const
{
    window.draw(projectileSprite);
}

sf::Vector2f Projectile::getPosition() const
{
    return projectileSprite.getPosition();
}

int Projectile::getDamage() const
{
    return damage;
}