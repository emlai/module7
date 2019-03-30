#include <algorithm>
#include <stdio.h>
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

void Level::save()
{
    FILE* file = fopen("level001.dat", "wb");
    fwrite(objects.data(), sizeof(Object), objects.size(), file);
    fclose(file);
}

void Level::load()
{
    FILE* file = fopen("level001.dat", "rb");

    if (!file)
    {
        addObject(ivec2(0, 0), Player);
        return;
    }

    fseek(file, 0, SEEK_END);
    auto size = ftell(file);
    fseek(file, 0, SEEK_SET);
    auto count = size / sizeof(Object);
    objects.resize(count);
    fread(objects.data(), sizeof(Object), count, file);
    fclose(file);
}
