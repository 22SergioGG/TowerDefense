#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Enemy
{
private:
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;

    int health;
    float speed;

    std::vector<sf::Vector2f> path;
    int currentPoint;

protected:
    virtual float getMovementSpeed() const;

public:
    Enemy();
    Enemy(int health, float spriteSize);

    virtual ~Enemy() = default;

    void setPosition(sf::Vector2f position);
    void setPath(std::vector<sf::Vector2f> newPath);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool hasReachedDestination() const;
};