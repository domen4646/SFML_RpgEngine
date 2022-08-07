#include "spriteset.h"

Spriteset::Spriteset()
{

}

// Splits texture into multiple subimages
sf::IntRect *Spriteset::splitTexture(sf::Texture &texture, unsigned int* tileNumber, unsigned int* pw, unsigned int* ph)
{
    int w = texture.getSize().x / 32;
    int h = texture.getSize().y / 32;
    *pw = w;
    *ph = h;
    *tileNumber = w * h;

    sf::IntRect* rects = new sf::IntRect[w * h];
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            rects[i * w + j] = sf::IntRect(j * 32, i * 32, 32, 32);
        }
    }
    return rects;
}

void Spriteset::splitInto(sf::Texture &texture, unsigned int rows, unsigned int cols, sf::IntRect *target)
{
    unsigned int w = texture.getSize().x / cols;
    unsigned int h = texture.getSize().y / rows;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            target[i * cols + j] = sf::IntRect(j * w, i * h, w, h);
        }
    }
}

void Spriteset::splitPtrInto(sf::Texture *texture, unsigned int rows, unsigned int cols, sf::IntRect *target)
{
    unsigned int w = texture->getSize().x / cols;
    unsigned int h = texture->getSize().y / rows;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            target[i * cols + j] = sf::IntRect(j * w, i * h, w, h);
        }
    }
}

void Spriteset::splitInto2D(sf::Texture &texture, unsigned int rows, unsigned int cols, sf::IntRect **target)
{
    unsigned int w = texture.getSize().x / cols;
    unsigned int h = texture.getSize().y / rows;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            target[i][j] = sf::IntRect(j * w, i * h, w, h);
        }
    }
}

void Spriteset::splitPtrInto2D(sf::Texture* texture, unsigned int rows, unsigned int cols, sf::IntRect **target)
{
    unsigned int w = texture->getSize().x / cols;
    unsigned int h = texture->getSize().y / rows;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            target[i][j] = sf::IntRect(j * w, i * h, w, h);
        }
    }
}
