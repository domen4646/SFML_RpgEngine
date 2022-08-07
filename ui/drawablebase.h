#ifndef DRAWABLEBASE_H
#define DRAWABLEBASE_H

#include "../engine.h"

class DrawableBase
{
public:
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual bool acceptsInput();
    virtual void handleInput(sf::Keyboard::Key key);
};

#endif // DRAWABLEBASE_H
