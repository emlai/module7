#include <SDL.h>
#include <glm/geometric.hpp>
#include "level.h"
#include "render.h"

vec2 moveTowards(vec2 current, vec2 target, float maxDistance)
{
    vec2 diff = target - current;
    float magnitude = length(diff);

    if (magnitude <= maxDistance || magnitude == 0)
        return target;

    return current + diff / magnitude * maxDistance;
}

void update(Level* level, const uint8_t* keyboardState, float deltaTime)
{
    bool onTile = level->getTile(level->playerPos + ivec2(0, 1)) != EmptyTile;
    bool left = keyboardState[SDL_SCANCODE_LEFT];
    bool right = keyboardState[SDL_SCANCODE_RIGHT];

    if (onTile && left && !right && level->playerPos.x >= level->playerRenderPos.x && level->getTile(level->playerPos + ivec2(-1, 0)) == EmptyTile)
        level->playerPos.x--;

    if (onTile && !left && right && level->playerPos.x <= level->playerRenderPos.x && level->getTile(level->playerPos + ivec2(1, 0)) == EmptyTile)
        level->playerPos.x++;

    if (!onTile && vec2(level->playerPos) == level->playerRenderPos)
        level->playerPos.y++;

    level->playerRenderPos = moveTowards(level->playerRenderPos, vec2(level->playerPos), 5 * deltaTime);
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Cannot initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Module7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    if (!window)
    {
        SDL_Log("Cannot create window: %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        SDL_Log("Cannot create renderer: %s", SDL_GetError());
        return 1;
    }

    SDL_Event event;
    auto keyboardState = SDL_GetKeyboardState(nullptr);
    bool running = true;
    uint64_t previousTime = 0;
    uint64_t currentTime = 0;

    Level level = {};

    while (running)
    {
        previousTime = currentTime;
        currentTime = SDL_GetPerformanceCounter();
        float deltaTime = float(currentTime - previousTime) / SDL_GetPerformanceFrequency();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                {
                    auto mouse = getMousePos();
                    auto tile = &level.tiles[mouse.x / tileSize][mouse.y / tileSize];

                    if (*tile == EmptyTile)
                        *tile = WallTile;
                    else
                        *tile = EmptyTile;

                    break;
                }
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_RenderClear(renderer);
        renderLevel(&level);
        SDL_RenderPresent(renderer);

        update(&level, keyboardState, deltaTime);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
