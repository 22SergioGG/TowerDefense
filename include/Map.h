#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map
{
private:
    std::vector<std::string> mapLayout;

    sf::Texture grassTexture;
    sf::Texture pathTexture;
    sf::Texture spawnerTexture;
    sf::Texture destinationTexture;

    sf::Vector2i findTile(char tile) const;
    sf::Vector2f tileToWorldCenter(sf::Vector2i tile) const;

public:
    Map();

    void draw(sf::RenderWindow& window);
    std::vector<sf::Vector2f> findPath() const;
    sf::Vector2f getSpawnerPosition() const;
    bool canPlaceTurret(sf::Vector2i tile) const;
};