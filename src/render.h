#pragma once

struct SDL_Renderer;
struct Level;

extern SDL_Renderer* renderer;

void renderLevel(Level* level);
