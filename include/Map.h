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

public:
    Map();
    void draw(sf::RenderWindow& window);
};