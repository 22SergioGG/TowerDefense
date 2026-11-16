#include "Map.h"
#include "Config.h"

Map::Map()
    : mapLayout
    {
        "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
        "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
        "SPPPPPPPPPPPPPPPPPPPPPPGGGGGGG",
        "GGGGGGGGGGGGGGGGGGGGGGPGGGGGGG",
        "GGGGGGGGGGGGGGGGGGGGGGPGGGGGGG",
        "GGGGGGGGGGGGGGGGGGGGGGPGGGGGGG",
        "GGGGGGPPPPPPPPPPPPPPPPPGGGGGGG",
        "GGGGGGPGGGGGGGGGGGGGGGGGGGGGGG",
        "GGGGGGPGGGGGGGGGGGGGGGGGGGGGGG",
        "GGGGGGPGGGGGGGGGGGGGGGGGGGGGGG",
        "GGGGGGPGGGGGGGGGGGGGGGGGGGGGGG",
        "GGGGGGPPPPPPPPPPPPPPPPPPPPPPPD",
        "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
        "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
        "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
    }
{
    grassTexture.loadFromFile("assets/grass.png");
    pathTexture.loadFromFile("assets/path.png");
    spawnerTexture.loadFromFile("assets/spawner.png");
    destinationTexture.loadFromFile("assets/destination.png");
}

void Map::draw(sf::RenderWindow& window)
{
    sf::Sprite sprite(grassTexture);

    for (int y = 0; y < Config::MAP_HEIGHT; y++)
    {
        for (int x = 0; x < Config::MAP_WIDTH; x++)
        {
            char tile = mapLayout[y][x];

            switch (tile)
            {
            case 'G':
                sprite.setTexture(grassTexture);
                break;

            case 'P':
                sprite.setTexture(pathTexture);
                break;

            case 'S':
                sprite.setTexture(spawnerTexture);
                break;

            case 'D':
                sprite.setTexture(destinationTexture);
                break;
            }

            sprite.setPosition(sf::Vector2f(
                static_cast<float>(x * Config::TILE_SIZE),
                static_cast<float>(y * Config::TILE_SIZE)
            ));

            window.draw(sprite);
        }
    }
}
