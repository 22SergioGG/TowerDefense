#pragma once

#include <SFML/Graphics.hpp>

class Projectile
{
private:
    sf::Texture projectileTexture;
    sf::Sprite projectileSprite;

    sf::Vector2f direction;

    float speed;
    int damage;

public:
    Projectile(sf::Vector2f startPosition, sf::Vector2f targetPosition);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    int getDamage() const;
};