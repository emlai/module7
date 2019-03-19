#pragma once

const int tileSize = 32;

enum Tile
{
    EmptyTile,
    WallTile
};

struct Level
{
    static const int width = 128;
    static const int height = 128;
    Tile tiles[width][height];
    int playerX;
    int playerY;
};
