#include "Game.h"
#include "Config.h"
#include "FastEnemy.h"
#include "BruiserEnemy.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <optional>

Game::Game()
    : window(
        sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }),
        "Tower Defense"
    ),
    font(std::make_unique<sf::Font>("assets/Roboto-Regular.ttf")),
    healthText(*font),
    goldText(*font),
    turretCostText(*font),
    gameOverText(*font),
    destroyedText(*font),
    restartText(*font)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    restart();

    healthText.setCharacterSize(30);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition({ Config::WINDOW_WIDTH - 250.f, 10.f });
    healthText.setString("Health: " + std::to_string(playerHealth));

    goldText.setCharacterSize(30);
    goldText.setFillColor(sf::Color::White);
    goldText.setPosition({ Config::WINDOW_WIDTH - 250.f, 58.f });
    goldText.setString("Gold: " + std::to_string(playerGold));

    turretCostText.setCharacterSize(30);
    turretCostText.setFillColor(sf::Color::White);
    turretCostText.setPosition({ Config::WINDOW_WIDTH - 250.f, 106.f });
    turretCostText.setString("Turret cost: " + std::to_string(turretCost));

    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({ 500.f, 250.f });

    destroyedText.setCharacterSize(30);
    destroyedText.setFillColor(sf::Color::White);
    destroyedText.setPosition({ 500.f, 330.f });

    restartText.setString("Press R to restart");
    restartText.setCharacterSize(25);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition({ 530.f, 390.f });
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();

        float deltaTime = clock.restart().asSeconds();

        update(deltaTime);
        render();
    }
}

void Game::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::R && gameOver)
            {
                restart();
            }
        }

        if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButton->button == sf::Mouse::Button::Left)
            {
                sf::Vector2i tile(
                    mouseButton->position.x / Config::TILE_SIZE,
                    mouseButton->position.y / Config::TILE_SIZE
                );

                if (!gameOver && map.canPlaceTurret(tile) && playerGold >= turretCost)
                {
                    auto newTurret = std::make_unique<Turret>(tile);

                    bool occupied = false;

                    for (const auto& turret : turrets)
                    {
                        if (*turret == *newTurret)
                        {
                            occupied = true;
                            break;
                        }
                    }

                    if (!occupied)
                    {
                        turrets.push_back(std::move(newTurret));

                        playerGold -= turretCost;
                        turretCost += 20;

                        goldText.setString("Gold: " + std::to_string(playerGold));
                        turretCostText.setString("Turret cost: " + std::to_string(turretCost));
                    }
                }
            }
        }
    }
}

void Game::update(float deltaTime)
{
    if (gameOver)
    {
        return;
    }

    spawnTimer += deltaTime;
    gameTime += deltaTime;

    if (spawnTimer >= nextSpawnTime)
    {
        std::unique_ptr<Enemy> enemy;

        int enemyType = rand() % 100 + 1;
        int enemyHealth = 100 + static_cast<int>(gameTime / 15.f) * 25;

        if (enemyType <= 50)
        {
            enemy = std::make_unique<Enemy>(enemyHealth, 1.0f);
        }
        else if (enemyType > 50 && enemyType <= 75)
        {
            enemy = std::make_unique<BruiserEnemy>(enemyHealth);
        }
        else if (enemyType > 75 && enemyType <= 100)
        {
            enemy = std::make_unique<FastEnemy>(enemyHealth);
        }

        enemy->setPosition(map.getSpawnerPosition());
        enemy->setPath(map.findPath());

        enemies.push_back(std::move(enemy));

        spawnTimer = 0.f;

        float maxSpawnTime = 4.0f - static_cast<int>(gameTime / 15.f) * 0.25f;

        if (maxSpawnTime < 1.0f)
        {
            maxSpawnTime = 1.0f;
        }

        nextSpawnTime = 1.0f + static_cast<float>(rand()) / RAND_MAX * (maxSpawnTime - 1.0f);
    }

    for (auto& enemy : enemies)
    {
        enemy->update(deltaTime);
    }

    for (auto& turret : turrets)
    {
        turret->update(deltaTime, enemies);
    }

    for (const auto& enemy : enemies)
    {
        if (enemy->hasReachedDestination())
        {
            playerHealth--;

            healthText.setString("Health: " + std::to_string(playerHealth));

            if (playerHealth <= 0)
            {
                gameOver = true;
            }
        }
        else if (!enemy->isAlive())
        {
            playerGold += 10;
            destroyedEnemies++;

            goldText.setString("Gold: " + std::to_string(playerGold));
        }
    }

    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [](const std::unique_ptr<Enemy>& enemy)
            {
                return enemy->hasReachedDestination() || !enemy->isAlive();
            }
        ),
        enemies.end()
    );
}

void Game::render()
{
    window.clear();

    map.draw(window);

    window.draw(healthText);
    window.draw(goldText);
    window.draw(turretCostText);

    for (const auto& enemy : enemies)
    {
        enemy->draw(window);
    }

    for (const auto& turret : turrets)
    {
        turret->draw(window);
    }

    if (gameOver)
    {
        destroyedText.setString(
            "Destroyed enemies: " + std::to_string(destroyedEnemies)
        );

        window.draw(gameOverText);
        window.draw(destroyedText);
        window.draw(restartText);
    }

    window.display();
}

void Game::restart()
{
    playerHealth = 3;
    playerGold = 100;
    turretCost = 40;
    destroyedEnemies = 0;

    gameTime = 0.f;
    spawnTimer = 0.f;
    nextSpawnTime = 1.0f + static_cast<float>(rand()) / RAND_MAX * 3.f;

    enemies.clear();
    turrets.clear();

    gameOver = false;

    healthText.setString("Health: " + std::to_string(playerHealth));
    goldText.setString("Gold: " + std::to_string(playerGold));
    turretCostText.setString("Turret cost: " + std::to_string(turretCost));

    clock.restart();
}