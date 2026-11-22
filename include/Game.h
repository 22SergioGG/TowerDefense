#pragma once

#include "Map.h"
#include "Enemy.h"
#include "Turret.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Game
{
private:
    sf::RenderWindow window;
    std::unique_ptr<sf::Font> font;

    Map map;

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Turret>> turrets;

    sf::Clock clock;

    int playerHealth;
    int playerGold;
    int turretCost;
    int destroyedEnemies;

    bool gameOver;

    float gameTime;
    float spawnTimer;
    float nextSpawnTime;

    sf::Text healthText;
    sf::Text goldText;
    sf::Text turretCostText;
    sf::Text gameOverText;
    sf::Text destroyedText;
    sf::Text restartText;

    void handleEvents();
    void update(float deltaTime);
    void render();
    void restart();

public:
    Game();
    void run();
};
