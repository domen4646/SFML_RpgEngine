#include "tileset.h"
#include "gameresources.h"
#include "spriteset.h"
#include "tiledata.h"

sf::Sprite Tileset::getTileSprite(int tile, int X, int Y)
{
    sf::Sprite sprite;
    sprite.setTexture(tilesetTexture);
    sprite.setPosition(X * 32, Y * 32);
    sprite.setTextureRect(tileRectangles[tile]);
    return sprite;
}

TileData *Tileset::getTileData(int tile)
{
    return &tileData[tile];
}

TileData Tileset::getCopyOfTileData(int tile)
{
    return tileData[tile];
}

Tileset::Tileset(unsigned int _tilesetTextureID)
{
    tilesetTextureID = _tilesetTextureID;
    tilesetTexture = GameResources::retrieveTexture(tilesetTextureID);
    tileRectangles = Spriteset::splitTexture(tilesetTexture, &tileNumber, &width, &height);
    tileData = new TileData[width * height];
}

unsigned int Tileset::getWidth()
{
    return width;
}

unsigned int Tileset::getHeight()
{
    return height;
}
