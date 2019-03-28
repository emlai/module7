#include <optional>
#include <SDL.h>
#include <glm/geometric.hpp>
#include "level.h"
#include "render.h"

constexpr float objectSpeed = 10;

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
    std::optional<ivec2> lastClickedPos;
};

bool attemptMove(Level* level, ivec2 dir)
{
    auto pos = level->getPlayer()->pos + dir;
    auto object = level->getTile(pos);

    if (!object)
        return true;

    switch (object->type)
    {
        case WallTile:
            return false;
        case BoxTile:
            if (!level->getTile(pos + dir))
            {
                object->pos = pos + dir;
                return true;
            }
            return false;
        case Player:
            return false;
    }

    assert(false);
}

void update(GameState* state, const uint8_t* keyboardState, float deltaTime)
{
    auto level = &state->level;
    bool left = keyboardState[SDL_SCANCODE_LEFT];
    bool right = keyboardState[SDL_SCANCODE_RIGHT];

    for (auto& object : state->level.objects)
    {
        bool onTile = object.pos.y == object.renderPos.y && level->getTile(object.pos + ivec2(0, 1));

        if (object.type == Player)
        {
            if (onTile && left && !right && object.pos.x >= object.renderPos.x && attemptMove(level, ivec2(-1, 0)))
                object.pos.x--;

            if (onTile && !left && right && object.pos.x <= object.renderPos.x && attemptMove(level, ivec2(1, 0)))
                object.pos.x++;
        }

        if (object.type != WallTile && !onTile && vec2(object.pos) == object.renderPos)
            object.pos.y++;

        object.renderPos = moveTowards(object.renderPos, vec2(object.pos), objectSpeed * deltaTime);
    }

    ivec2 mousePos;
    auto buttons = SDL_GetMouseState(&mousePos.x, &mousePos.y);
    auto clickedTilePos = mousePos / tileSize;

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        if (state->lastClickedPos != clickedTilePos)
        {
            level->addObject(clickedTilePos, state->brush);
            state->lastClickedPos = clickedTilePos;
        }
    }
    else if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        if (state->lastClickedPos != clickedTilePos)
        {
            level->removeObject(clickedTilePos);
            state->lastClickedPos = clickedTilePos;
        }
    }
    else
    {
        state->lastClickedPos.reset();
    }
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
    state.level.addObject(ivec2(0, 0), Player);

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
