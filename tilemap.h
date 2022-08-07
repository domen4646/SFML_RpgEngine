#ifndef TILEMAP_H
#define TILEMAP_H


#include "engine.h"

#define HEADER_CHECK 1619778187

class Tileset;
struct TileData;

class Tilemap
{
private:
    TileData** map = NULL;
    sf::Sprite** tileSprites = NULL;
    bool valid = true;

    Tileset* tileset;
    unsigned short w;
    unsigned short h;

    unsigned int length;

public:
    Tilemap(FILE* tilemapFile, Tileset* _t);
    ~Tilemap();
    bool isValid();
    unsigned int getTileCount();
    void drawTiles(sf::RenderTarget& target);
    bool isFieldPassable(int X, int Y, Direction direction);
    bool isFieldOutOfMap(int X, int Y);
};

#endif // TILEMAP_H
