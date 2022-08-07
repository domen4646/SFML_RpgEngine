#ifndef TILESET_H
#define TILESET_H

#include "engine.h"
#include "tiledata.h"

class Tileset
{
private:
    unsigned int width;
    unsigned int height;

    TileData* tileData;
    sf::IntRect* tileRectangles;
    unsigned int tilesetTextureID;
    unsigned int tileNumber;
    sf::Texture tilesetTexture;

public:
    Tileset(unsigned int _tilesetTextureID);

    sf::Sprite getTileSprite(int tile, int X, int Y);
    TileData* getTileData(int tile);
    TileData getCopyOfTileData(int tile);
    unsigned int getWidth();
    unsigned int getHeight();
};

#endif // TILESET_H
