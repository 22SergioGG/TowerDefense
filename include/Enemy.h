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

    int getHealth() const;
    float getDistanceToDestination() const;
    void setPosition(sf::Vector2f position);
    void setPath(std::vector<sf::Vector2f> newPath);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool hasReachedDestination() const;
    void takeDamage(int damage);
    bool isAlive() const;
    sf::Vector2f getPosition() const;

    bool operator<(const Enemy& other) const;
};