#include "Config.h"
#include "Map.h"
#include "Enemy.h"
#include "FastEnemy.h"
#include "BruiserEnemy.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>
#include <utility>

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    float gameTime = 0.f;
    float spawnTimer = 0.f;
    float nextSpawnTime = 1.f + static_cast<float>(rand()) / RAND_MAX * 3.f;

    try
    {
        sf::RenderWindow window(
            sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }),
            "Tower Defense"
        );

        Map map;

        std::vector<std::unique_ptr<Enemy>> enemies;

        sf::Clock clock;

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
                   
            }

            float deltaTime = clock.restart().asSeconds();
            spawnTimer += deltaTime;
            gameTime += deltaTime;

            if (spawnTimer >= nextSpawnTime)
            {
                std::unique_ptr<Enemy> enemy;

                int enemyType = rand() % 10;

                if (enemyType >=0 && enemyType <= 4)
                {
                    enemy = std::make_unique<Enemy>();
                }
                else if (enemyType >= 5 && enemyType <= 6)
                {
                    enemy = std::make_unique<BruiserEnemy>();
                }
                else 
                {
                    enemy = std::make_unique<FastEnemy>();
                }

                enemy->setPosition(map.getSpawnerPosition());
                enemy->setPath(map.findPath());

                enemies.push_back(std::move(enemy));

                spawnTimer = 0.f;
                float maxSpawnTime = 4.f - static_cast<int>(gameTime / 20.f) * 0.25f;
                if (maxSpawnTime < 1.f)
                {
                    maxSpawnTime = 1.f;
                }
                    
                nextSpawnTime = 1.f + static_cast<float>(rand()) / RAND_MAX * (maxSpawnTime - 1.f);

            }

            for (auto& enemy : enemies)
            {
                enemy->update(deltaTime);
            }

            enemies.erase(
                std::remove_if(
                    enemies.begin(),
                    enemies.end(),
                    [](const std::unique_ptr<Enemy>& enemy)
                    {
                        return enemy->hasReachedDestination();
                    }
                ),
                enemies.end()
            );

            window.clear();
            map.draw(window);

            for (const auto& enemy : enemies)
            {
                enemy->draw(window);
            }

            window.display();
        }
    }

    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
