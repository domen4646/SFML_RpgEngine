#include "utils.h"
#include "../tiledata.h"

sf::IntRect **utils::alloc_rects_2d(unsigned int w, unsigned int h)
{
    sf::IntRect** irect = new sf::IntRect*[h];
    for (int i=0; i<h; i++) {
        irect[i] = new sf::IntRect[w];
    }
    return irect;
}

void utils::free_rects_2d(sf::IntRect **arr, unsigned int h)
{
    for (int i=0; i<h; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

sf::Sprite **utils::alloc_sprites_2d(unsigned int w, unsigned int h)
{
    sf::Sprite** sprts = new sf::Sprite*[w];
    for (int i=0; i<w; i++) {
        sprts[i] = new sf::Sprite[h];
    }
    return sprts;
}

void utils::free_sprites_2d(sf::Sprite **arr, unsigned int h)
{
    for (int i=0; i<h; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

TileData **utils::alloc_tiledata_2d(unsigned int w, unsigned int h)
{
    TileData** tiledatas = new TileData*[w];
    for (int i=0; i<w; i++) {
        tiledatas[i] = new TileData[h];
    }
    return tiledatas;
}

void utils::free_tiledata_2d(TileData **arr, unsigned int h)
{
    for (int i=0; i<h; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

void utils::animate_rectangle_shape(YIELD_SINK &sink, sf::RectangleShape *shape, float X, float Y, unsigned int W, unsigned int H, unsigned int speed)
{
    float oldX = shape->getPosition().x;
    float oldY = shape->getPosition().y;
    unsigned int oldW = shape->getSize().x;
    unsigned int oldH = shape->getSize().y;

    float curX = oldX;
    float curY = oldY;
    unsigned int curW = oldW;
    unsigned int curH = oldH;

    float part;
    for (int i=1; i<=speed; i++) {
        part = ((float)i / (float)speed);
        curX = oldX + (X - oldX) * part;
        curY = oldY + (Y - oldY) * part;
        curW = oldW + ((int)W - (int)oldW) * part;
        curH = oldH + ((int)H - (int)oldH) * part;

        shape->setPosition(curX, curY);
        shape->setSize(sf::Vector2f(curW, curH));
        sink();
    }
}

void utils::animate_rectangle_color(YIELD_SINK &sink, sf::RectangleShape *shape, sf::Color color, unsigned int speed)
{
    sf::Color oldColor = shape->getFillColor();
    sf::Color curColor = oldColor;

    float part;
    for (int i=1; i<=speed; i++) {
        part = ((float)i / (float)speed);
        curColor.r = (sf::Uint8)((int)oldColor.r + ((int)color.r - (int)oldColor.r) * part);
        curColor.g = (sf::Uint8)((int)oldColor.g + ((int)color.g - (int)oldColor.g) * part);
        curColor.b = (sf::Uint8)((int)oldColor.b + ((int)color.b - (int)oldColor.b) * part);
        curColor.a = (sf::Uint8)((int)oldColor.a + ((int)color.a - (int)oldColor.a) * part);

        shape->setFillColor(curColor);
        sink();
    }
}
