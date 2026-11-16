#include <SFML/Graphics.hpp>

int main()
{
    constexpr unsigned int width = 1920;
    constexpr unsigned int height = 1080;

    sf::RenderWindow window(
        sf::VideoMode({ width, height }),
        "White Window"
    );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}