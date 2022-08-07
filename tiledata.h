#ifndef TILEDATA_H
#define TILEDATA_H

#include "engine.h"

struct TileData
{
    bool passage;
    bool passage4dir[4];

    bool ladder;
    bool bush;
    bool counter;
    unsigned char damageFloor;
    unsigned char terrainTag;

    bool getCanMove(Direction direction);
    bool getCanMoveTo(Direction from);

    TileData();
};


#endif // TILEDATA_H
