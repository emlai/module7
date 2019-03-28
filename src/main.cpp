#include <SDL.h>
#include <glm/geometric.hpp>
#include "level.h"
#include "render.h"

constexpr float playerSpeed = 10;

vec2 moveTowards(vec2 current, vec2 target, float maxDistance)
{
    vec2 diff = target - current;
    float magnitude = length(diff);

    if (magnitude <= maxDistance || magnitude == 0)
        return target;

    return current + diff / magnitude * maxDistance;
}

struct GameState
{
    Level level;
    Tile brush = WallTile;
};

bool attemptMove(Level* level, ivec2 dir)
{
    auto pos = level->playerPos + dir;
    auto tile = level->getTile(pos);

    switch (tile)
    {
        case EmptyTile:
            return true;
        case WallTile:
            return false;
        case BoxTile:
            if (level->getTile(pos + dir) == EmptyTile)
            {
                level->setTile(pos + dir, tile);
                level->setTile(pos, EmptyTile);
                return true;
            }
            return false;
    }
}

void update(GameState* state, const uint8_t* keyboardState, float deltaTime)
{
    auto level = &state->level;
    bool onTile = level->playerPos.y == level->playerRenderPos.y && level->getTile(level->playerPos + ivec2(0, 1)) != EmptyTile;
    bool left = keyboardState[SDL_SCANCODE_LEFT];
    bool right = keyboardState[SDL_SCANCODE_RIGHT];

    if (onTile && left && !right && level->playerPos.x >= level->playerRenderPos.x && attemptMove(level, ivec2(-1, 0)))
        level->playerPos.x--;

    if (onTile && !left && right && level->playerPos.x <= level->playerRenderPos.x && attemptMove(level, ivec2(1, 0)))
        level->playerPos.x++;

    if (!onTile && vec2(level->playerPos) == level->playerRenderPos)
        level->playerPos.y++;

    level->playerRenderPos = moveTowards(level->playerRenderPos, vec2(level->playerPos), playerSpeed * deltaTime);

    ivec2 mousePos;
    auto buttons = SDL_GetMouseState(&mousePos.x, &mousePos.y);

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        level->getTile(mousePos / tileSize) = state->brush;
    else if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
        level->getTile(mousePos / tileSize) = EmptyTile;
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

    GameState state;

    while (running)
    {
        previousTime = currentTime;
        currentTime = SDL_GetPerformanceCounter();
        float deltaTime = float(currentTime - previousTime) / SDL_GetPerformanceFrequency();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_1:
                            state.brush = WallTile;
                            break;
                        case SDLK_2:
                            state.brush = BoxTile;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_RenderClear(renderer);
        renderLevel(&state.level);
        SDL_RenderPresent(renderer);

        update(&state, keyboardState, deltaTime);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
