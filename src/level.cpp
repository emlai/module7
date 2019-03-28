#include "level.h"

Tile& Level::getTile(ivec2 pos)
{
    return tiles[pos.x][pos.y];
}

void Level::setTile(ivec2 pos, Tile tile)
{
    tiles[pos.x][pos.y] = tile;
}
