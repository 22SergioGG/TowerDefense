#include "Map.h"
#include "Config.h"

#include <stdexcept>
#include <queue>
#include <algorithm>
#include <vector>

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
    int spawnerCount = 0;
    int destinationCount = 0;

    for (const auto& row : mapLayout)
    {
        for (char tile : row)
        {
            if (tile == 'S')
            {
                spawnerCount++;
            }
                
            if (tile == 'D')
            {
                destinationCount++;
            }
               
        }
    }

    if (spawnerCount != 1)
    {
        throw std::runtime_error("Map must contain only ONE spawner!");
    }
        
    if (destinationCount != 1)
    {
        throw std::runtime_error("Map must contain only ONE destination!");
    }
        
    grassTexture.loadFromFile("assets/grass.png");
    pathTexture.loadFromFile("assets/path.png");
    spawnerTexture.loadFromFile("assets/spawner.png");
    destinationTexture.loadFromFile("assets/destination.png");
}

sf::Vector2i Map::findTile(char tile) const
{
    for (int y = 0; y < Config::MAP_HEIGHT; y++)
    {
        for (int x = 0; x < Config::MAP_WIDTH; x++)
        {
            if (mapLayout[y][x] == tile)
            {
                return { x, y };
            }
                
        }
    }

    throw std::runtime_error("Tile not found!");
}

sf::Vector2f Map::tileToWorldCenter(sf::Vector2i tile) const
{
    return sf::Vector2f(
        tile.x * Config::TILE_SIZE + Config::TILE_SIZE / 2.f,
        tile.y * Config::TILE_SIZE + Config::TILE_SIZE / 2.f
    );
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

std::vector<sf::Vector2f> Map::findPath() const
{
    sf::Vector2i start = findTile('S');
    sf::Vector2i destination = findTile('D');

    std::queue<sf::Vector2i> queue;
    std::vector<std::vector<sf::Vector2i>> previous(
        Config::MAP_HEIGHT,
        std::vector<sf::Vector2i>(Config::MAP_WIDTH, { -1, -1 })
    );

    queue.push(start);
    previous[start.y][start.x] = start;

    const sf::Vector2i directions[] =
    {
        { 0, -1 },
        { 0, 1 },
        { -1, 0 },
        { 1, 0 }
    };

    while (!queue.empty())
    {
        sf::Vector2i current = queue.front();
        queue.pop();

        if (current == destination)
        {
            break;
        }
           

        for (const auto& direction : directions)
        {
            sf::Vector2i next = current + direction;

            if (next.x < 0 || next.x >= Config::MAP_WIDTH || next.y < 0 || next.y >= Config::MAP_HEIGHT)
            {
                continue;
            }
                
            if (previous[next.y][next.x].x != -1)
            {
                continue;
            }

            char tile = mapLayout[next.y][next.x];

            if (tile != 'P' && tile != 'D')
            {
                continue;
            }

            previous[next.y][next.x] = current;
            queue.push(next);
        }
    }

    if (previous[destination.y][destination.x].x == -1)
    {
        throw std::runtime_error("No path to destination!");
    }
        
    std::vector<sf::Vector2f> path;

    sf::Vector2i current = destination;

    while (current != start)
    {
        path.push_back(tileToWorldCenter(current));
        current = previous[current.y][current.x];
    }

    std::reverse(path.begin(), path.end());

    return path;
}

sf::Vector2f Map::getSpawnerPosition() const
{
    sf::Vector2i spawner = findTile('S');

    return tileToWorldCenter(spawner);
}
