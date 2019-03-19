#include "level.h"
#include <glm/geometric.hpp>

vec2 moveTowards(vec2 current, vec2 target, float maxDistance)
{
    vec2 diff = target - current;
    float magnitude = length(diff);
    if (magnitude <= maxDistance || magnitude == 0)
    {
        return target;
    }
    return current + diff / magnitude * maxDistance;
}

void updateLevel(Level* level)
{
    if (vec2(level->playerPos) == level->playerRenderPos && level->tiles[level->playerPos.x][level->playerPos.y + 1] == EmptyTile)
        level->playerPos.y++;

    level->playerRenderPos = moveTowards(level->playerRenderPos, vec2(level->playerPos), 0.1f);
}
