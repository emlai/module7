#include "level.h"
#include <glm/geometric.hpp>
#include <SDL.h>

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

void updateLevel(Level* level, const uint8_t keyboardState[])
{
    if (vec2(level->playerPos) == level->playerRenderPos)
    {
        bool movedHorizontally = false;

        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            level->playerPos.x -= 1;
            movedHorizontally = true;
        }

        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            level->playerPos.x += 1;
            movedHorizontally = true;
        }

        if (!movedHorizontally && level->tiles[level->playerPos.x][level->playerPos.y + 1] == EmptyTile)
            level->playerPos.y++;
    }

    level->playerRenderPos = moveTowards(level->playerRenderPos, vec2(level->playerPos), 0.1f);
}
