#ifndef ISPRITE_H
#define ISPRITE_H

#include "../engine.h"

class SpriteBase {
protected:
    Direction direction = Direction::Down;
    sf::Sprite sprite;

    virtual void onImageSet();
    virtual void onDirectionSet();

public:
    virtual void draw(sf::RenderTarget& target, unsigned int movFrame);
    virtual void setPosition(float X, float Y);
    void setDirection(Direction dir);

    float getX();
    float getY();
    Direction getDirection();

    sf::Sprite* getSpriteRef();

    void setImage(unsigned int imageID);
};


#endif // ISPRITE_H
