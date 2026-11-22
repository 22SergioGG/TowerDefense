#pragma once

namespace Config
{
    constexpr int TILE_SIZE = 48;

    constexpr int MAP_WIDTH = 30;
    constexpr int MAP_HEIGHT = 15;

    constexpr int ENEMY_SIZE = 36;
    constexpr int TOWER_SIZE = 48;
    constexpr int PROJECTILE_SIZE = 12;

    constexpr int WINDOW_WIDTH = MAP_WIDTH * TILE_SIZE;
    constexpr int WINDOW_HEIGHT = MAP_HEIGHT * TILE_SIZE;

}