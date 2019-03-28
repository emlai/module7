#pragma once
#include <glm/vec2.hpp>

using namespace glm;

const int tileSize = 16;

enum Tile
{
    EmptyTile,
    WallTile,
    BoxTile
};

struct Level
{
    static const int width = 128;
    static const int height = 128;
    Tile tiles[width][height];
    vec2 playerRenderPos;
    ivec2 playerPos;

    Tile& getTile(ivec2 pos);
};
