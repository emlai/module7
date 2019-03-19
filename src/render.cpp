#include "render.h"
#include "level.h"
#include <SDL.h>

SDL_Renderer* renderer;

void renderLevel(Level* level)
{
    for (int x = 0; x < level->width; x++)
    {
        for (int y = 0; y < level->height; y++)
        {
            switch (level->tiles[x][y])
            {
                case EmptyTile:
                    SDL_SetRenderDrawColor(renderer, 0xcc, 0xcc, 0xcc, 0xff);
                    break;
                case WallTile:
                    SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0xff);
                    break;
            }

            SDL_Rect rect = { x, y, level->width, level->height };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
