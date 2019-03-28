#include <algorithm>
#include "level.h"

Object* Level::getTile(ivec2 pos)
{
    for (auto& object : objects)
    {
        if (object.pos == pos)
            return &object;
    }

    return nullptr;
}

Object* Level::getPlayer()
{
    return &objects[0];
}

void Level::addObject(ivec2 pos, Tile type)
{
    if (getTile(pos))
        return;

    objects.push_back(Object { .type = type, .pos = pos, .renderPos = pos });
}

void Level::removeObject(ivec2 pos)
{
    objects.erase(std::remove_if(objects.begin(), objects.end(), [=](auto& object) { return object.pos == pos && object.type != Player; }),
                  objects.end());
}
