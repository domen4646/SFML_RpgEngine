#ifndef SPRITESET_H
#define SPRITESET_H

#include "engine.h"

class Spriteset
{   
public:
    Spriteset();
    static sf::IntRect* splitTexture(sf::Texture& texture, unsigned int* tileNumber, unsigned int* pw, unsigned int* ph);
    static void splitInto(sf::Texture& texture, unsigned int rows, unsigned int cols, sf::IntRect* target);
    static void splitPtrInto(sf::Texture* texture, unsigned int rows, unsigned int cols, sf::IntRect* target);
    static void splitInto2D(sf::Texture& texture, unsigned int rows, unsigned int cols, sf::IntRect** target);
    static void splitPtrInto2D(sf::Texture* texture, unsigned int rows, unsigned int cols, sf::IntRect** target);
};

#endif // SPRITESET_H
