#ifndef DIRECTIONALSPRITE_H
#define DIRECTIONALSPRITE_H

#include "SpriteBase.h"

class DirectionalSprite : public SpriteBase
{
private:
    sf::IntRect spriteRectange[4];

protected:
    virtual void onImageSet() override;
    virtual void onDirectionSet() override;

public:
    DirectionalSprite();
};

#endif // DIRECTIONALSPRITE_H
