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

void updateLevel(Level* level, const uint8_t keyboardState[], float deltaTime)
{
    bool onTile = level->tiles[level->playerPos.x][level->playerPos.y + 1] != EmptyTile;
    bool left = keyboardState[SDL_SCANCODE_LEFT];
    bool right = keyboardState[SDL_SCANCODE_RIGHT];

    if (onTile && left && !right && level->playerPos.x >= level->playerRenderPos.x)
        level->playerPos.x--;

    if (onTile && !left && right && level->playerPos.x <= level->playerRenderPos.x)
        level->playerPos.x++;

    if (!onTile && vec2(level->playerPos) == level->playerRenderPos)
        level->playerPos.y++;

    level->playerRenderPos = moveTowards(level->playerRenderPos, vec2(level->playerPos), 5 * deltaTime);
}
