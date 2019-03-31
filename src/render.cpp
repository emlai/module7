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
        SDL_Rect rect = { int(object.renderPos.x * tileSize), int(object.renderPos.y * tileSize), tileSize, tileSize };

        switch (object.type)
        {
            case WallTile:
                SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0xff);
                SDL_RenderFillRect(renderer, &rect);
                break;

            case BoxTile:
                SDL_SetRenderDrawColor(renderer, 0x44, 0x44, 0x44, 0xff);
                SDL_RenderFillRect(renderer, &rect);
                rect.x += 1;
                rect.y += 1;
                rect.w -= 2;
                rect.h -= 2;
                SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xff);
                SDL_RenderFillRect(renderer, &rect);
                break;

            case Player:
                SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xff);
                rect.x += tileSize / 4;
                rect.y += tileSize / 4;
                rect.w /= 2;
                rect.h -= tileSize / 4;
                SDL_RenderFillRect(renderer, &rect);
                break;
        }
    }

    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    SDL_Rect rect = { mouse.x / tileSize * tileSize, mouse.y / tileSize * tileSize, tileSize, tileSize };
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderDrawRect(renderer, &rect);
}
