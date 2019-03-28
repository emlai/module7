#include "render.h"
#include "level.h"
#include <SDL.h>

SDL_Renderer* renderer;

void renderLevel(Level* level)
{
    SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
    SDL_RenderFillRect(renderer, nullptr);

    for (auto& object : level->objects)
    {
        switch (object.type)
        {
            case WallTile:
                SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0xff);
                break;
            case BoxTile:
                SDL_SetRenderDrawColor(renderer, 0x44, 0x44, 0x44, 0xff);
                break;
            case Player:
                SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xff);
                break;
        }

        SDL_Rect rect = { int(object.renderPos.x * tileSize), int(object.renderPos.y * tileSize), tileSize, tileSize };

        if (object.type == Player)
        {
            rect.x += tileSize / 4;
            rect.y += tileSize / 4;
            rect.w /= 2;
            rect.h -= tileSize / 4;
        }

        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    SDL_Rect rect = { mouse.x / tileSize * tileSize, mouse.y / tileSize * tileSize, tileSize, tileSize };
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderDrawRect(renderer, &rect);
}
