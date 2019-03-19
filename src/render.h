#pragma once

struct SDL_Renderer;
struct SDL_Point;
struct Level;

extern SDL_Renderer* renderer;

void renderLevel(Level* level);
SDL_Point getMousePos();
