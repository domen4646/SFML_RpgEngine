#include "tilemap.h"
#include "tileset.h"
#include "tiledata.h"
#include "utils/utils.h"
#include <iostream>

#ifdef __linux__ 
#include <byteswap.h>
#elif _WIN32
#define bswap_16 _byteswap_ushort
#define bswap_32 _byteswap_ulong
#else
#error "Unsupported OS!"
#endif

// Load tilemap from file and apply tileset
Tilemap::Tilemap(FILE *tilemapFile, Tileset *_t)
{
    tileset = _t;
    unsigned int fourcc;
    size_t res = fread((void*) &fourcc, 4, 1, tilemapFile);
    std::cout << "res " << res << std::endl;
    fourcc = bswap_32(fourcc);

    if (fourcc != HEADER_CHECK) {
        //valid = false;
        std::cout << "Header is invalid!" << std::endl;
        //return;
    }
    res = fread((void*) &w, 2, 1, tilemapFile);
    if (res < 1) {
        valid = false;
        return;
    }
    res = fread((void*) &h, 2, 1, tilemapFile);
    if (res < 1) {
        valid = false;
        return;
    }

    w = bswap_16(w);
    h = bswap_16(h);
    std::cout << "w " << w << " h " << h << std::endl;

    length = w * h;
    map = utils::alloc_tiledata_2d(w, h);
    tileSprites = utils::alloc_sprites_2d(w, h);
    std::cout << "checkpoint" << std::endl;

    unsigned short tileID;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            res = fread((void*) &tileID, 2, 1, tilemapFile);
            if (res < 1) {
                perror("fread");
                valid = false;
                return;
            }
            tileID = bswap_16(tileID);

            map[j][i] = tileset->getCopyOfTileData(tileID);
            tileSprites[j][i] = tileset->getTileSprite(tileID, j, i);
        }
    }
}

Tilemap::~Tilemap()
{
    if (map != NULL) {
        utils::free_tiledata_2d(map, w);
    }
    if (tileSprites != NULL) {
        utils::free_sprites_2d(tileSprites, w);
    }
}

bool Tilemap::isValid()
{
    return valid;
}

unsigned int Tilemap::getTileCount()
{
    return length;
}

void Tilemap::drawTiles(sf::RenderTarget &target)
{
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            target.draw(tileSprites[i][j]);
        }
    }
}

// check if field is out of map first!
bool Tilemap::isFieldPassable(int X, int Y, Direction direction)
{
    return map[X][Y].getCanMoveTo(direction);
}

bool Tilemap::isFieldOutOfMap(int X, int Y)
{
    return (X < 0 || X >= w || Y < 0 || Y >= h);
}
