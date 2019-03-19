#include "level.h"

Tile& Level::getTile(ivec2 pos)
{
    return tiles[pos.x][pos.y];
}
