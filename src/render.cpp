#include "render.h"
#include "level.h"
#include <SDL.h>

SDL_Renderer* renderer;

void renderLevel(Level* level)
{
    SDL_Point mouse = getMousePos();

    for (int x = 0; x < level->width; x++)
    {
        for (int y = 0; y < level->height; y++)
        {
            SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };

            switch (level->tiles[x][y])
            {
                case EmptyTile:
                    SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
                    break;
                case WallTile:
                    SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0xff);
                    break;
            }

            SDL_RenderFillRect(renderer, &rect);

            if (SDL_PointInRect(&mouse, &rect))
            {
                SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

SDL_Point getMousePos()
{
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    return mouse;
}
