#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Map.h"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT }),
        "Tower Defense"
    );

    Map map;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        map.draw(window);

        window.display();
    }

    return 0;
}
