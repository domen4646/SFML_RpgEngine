#ifndef UTILS_H
#define UTILS_H

#include "../engine.h"

struct TileData;

namespace utils {

    sf::IntRect** alloc_rects_2d(unsigned int w, unsigned int h);
    void free_rects_2d(sf::IntRect** arr, unsigned int h);

    sf::Sprite** alloc_sprites_2d(unsigned int w, unsigned int h);
    void free_sprites_2d(sf::Sprite** arr, unsigned int h);

    TileData** alloc_tiledata_2d(unsigned int w, unsigned int h);
    void free_tiledata_2d(TileData** arr, unsigned int h);


    // speed is in frames
    void animate_rectangle_shape(YIELD_SINK &sink, sf::RectangleShape* shape, float X, float Y, unsigned int W, unsigned int H, unsigned int speed);

    void animate_rectangle_color(YIELD_SINK &sink, sf::RectangleShape* shape, sf::Color color, unsigned int speed);
}

#endif // UTILS_H
