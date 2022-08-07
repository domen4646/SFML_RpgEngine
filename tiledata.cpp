#include "tiledata.h"

bool TileData::getCanMove(Direction direction)
{
    return passage4dir[direction];
}

bool TileData::getCanMoveTo(Direction from)
{
    return passage && getCanMove(reverse_direction(from));
}

TileData::TileData()
{
    passage = true;
    //passage4dir = {true, true, true, true};
    passage4dir[0] = true;
    passage4dir[1] = true;
    passage4dir[2] = true;
    passage4dir[3] = true;
    ladder = false;
    bush = false;
    counter = false;
    damageFloor = 0;
    terrainTag = 0;
}
