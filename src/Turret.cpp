#include "Turret.h"
#include "Config.h"
#include "Projectile.h"

#include <algorithm>
#include <cmath>

Turret::Turret(sf::Vector2i tilePosition)
    : turretBaseTexture("assets/turret_base.png"),
    turretHeadTexture("assets/turret_head.png"),
    turretBaseSprite(turretBaseTexture),
    turretHeadSprite(turretHeadTexture),
    tilePosition(tilePosition),
    range(360.f),
    fireRate(0.9f),
    fireTimer(0.f)
{
    sf::Vector2f position(
        tilePosition.x * Config::TILE_SIZE + Config::TILE_SIZE / 2.f,
        tilePosition.y * Config::TILE_SIZE + Config::TILE_SIZE / 2.f
    );

    turretBaseSprite.setOrigin(sf::Vector2f(
        turretBaseTexture.getSize().x / 2.f,
        turretBaseTexture.getSize().y / 2.f
    ));

    turretHeadSprite.setOrigin(sf::Vector2f(
        turretHeadTexture.getSize().x / 2.f,
        turretHeadTexture.getSize().y / 2.f
    ));

    turretBaseSprite.setPosition(position);
    turretHeadSprite.setPosition(position);
}

sf::Vector2f Turret::getPosition() const
{
    return turretBaseSprite.getPosition();
}

bool Turret::operator==(const Turret& other) const
{
    return tilePosition == other.tilePosition;
}

void Turret::update(float deltaTime, std::vector<std::unique_ptr<Enemy>>& enemies)
{
    Enemy* target = nullptr;

    for (const auto& enemy : enemies)
    {
        if (!enemy->isAlive() || enemy->hasReachedDestination())
        {
            continue;
        }

        sf::Vector2f difference = enemy->getPosition() - getPosition();

        float distance = std::hypot(difference.x, difference.y);

        if (distance > range)
        {
            continue;
        }

        if (target == nullptr || *enemy < *target)
        {
            target = enemy.get();
        }
    }

    if (target != nullptr)
    {
        sf::Vector2f direction = target->getPosition() - getPosition();

        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;

        turretHeadSprite.setRotation(sf::degrees(angle + 90.f));

        fireTimer += deltaTime;

        if (fireTimer >= fireRate)
        {
            projectiles.emplace_back(
                std::make_unique<Projectile>(getPosition(), target->getPosition())
            );

            fireTimer = 0.f;
        }
    }

    for (auto& projectile : projectiles)
    {
        projectile->update(deltaTime);
    }

    projectiles.erase(
        std::remove_if(
            projectiles.begin(),
            projectiles.end(),
            [&enemies](const std::unique_ptr<Projectile>& projectile)
            {
                sf::Vector2f position = projectile->getPosition();

                if (position.x < 0.f || position.x >= Config::WINDOW_WIDTH ||
                    position.y < 0.f || position.y >= Config::WINDOW_HEIGHT)
                {
                    return true;
                }

                for (auto& enemy : enemies)
                {
                    if (!enemy->isAlive())
                    {
                        continue;
                    }

                    sf::Vector2f difference =
                        enemy->getPosition() - position;

                    float distance = std::hypot(difference.x, difference.y);

                    if (distance < 25.0f)
                    {
                        enemy->takeDamage(projectile->getDamage());
                        return true;
                    }
                }

                return false;
            }
        ),
        projectiles.end()
    );
}

void Turret::draw(sf::RenderWindow& window)
{
    window.draw(turretBaseSprite);
    window.draw(turretHeadSprite);

    for (const auto& projectile : projectiles)
    {
        projectile->draw(window);
    }
}
