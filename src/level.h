#pragma once
#include <glm/vec2.hpp>

using namespace glm;

const int tileSize = 32;

enum Tile
{
    EmptyTile,
    WallTile
};

struct Level
{
    static const int width = 128;
    static const int height = 128;
    Tile tiles[width][height];
    vec2 playerRenderPos;
    ivec2 playerPos;

    Tile getTile(ivec2 pos);
};
