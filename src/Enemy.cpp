#include "Enemy.h"

#include <cmath>

Enemy::Enemy()
    : Enemy(100, 1.0f)
{
}

Enemy::Enemy(int health, float spriteSize)
    : enemyTexture("assets/enemy.png"),
    enemySprite(enemyTexture),
    health(health),
    speed(100.f),
    currentPoint(0)
 
{
    enemySprite.setScale({ spriteSize, spriteSize });

    enemySprite.setOrigin(sf::Vector2f(
        enemyTexture.getSize().x / 2.f,
        enemyTexture.getSize().y / 2.f
    ));
}

void Enemy::setPosition(sf::Vector2f position)
{
    enemySprite.setPosition(position);
}

void Enemy::setPath(std::vector<sf::Vector2f> newPath)
{
    path = newPath;
    currentPoint = 0;
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(enemySprite);
}

float Enemy::getMovementSpeed() const
{
    return speed;
}

void Enemy::update(float deltaTime)
{
    if (currentPoint >= path.size())
    {
        return;
    }
        
    sf::Vector2f position = enemySprite.getPosition();
    sf::Vector2f target = path[currentPoint];

    sf::Vector2f direction = target - position;

    float distance = std::sqrt(
        direction.x * direction.x +
        direction.y * direction.y
    );

    float movement = getMovementSpeed() * deltaTime;

    if (distance <= movement)
    {
        enemySprite.setPosition(target);
        currentPoint++;
    }
    else
    {
        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
        enemySprite.setRotation(sf::degrees(angle));
        direction /= distance;
        enemySprite.move(direction * movement);
    }
}

bool Enemy::hasReachedDestination() const
{
    return !path.empty() && currentPoint >= static_cast<int>(path.size());
}