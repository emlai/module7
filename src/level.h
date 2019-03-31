#pragma once
#include <vector>
#include <glm/vec2.hpp>

using namespace glm;

const int tileSize = 16;

enum Tile
{
    WallTile,
    BoxTile,
    Player
};

struct Object
{
    Tile type;
    ivec2 pos;
    vec2 renderPos;
};

struct Level
{
    std::vector<Object> objects;

    void addObject(ivec2 pos, Tile type);
    void removeObject(ivec2 pos);
    Object* getTile(ivec2 pos);
    void save();
    void load();
};
