#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SpriteBase.h"

class AnimatedSprite : public SpriteBase
{
private:
    sf::IntRect** imageFrames = NULL;

protected:
    virtual void onImageSet() override;

public:

    virtual void draw(sf::RenderTarget& target, unsigned int movFrame) override;
    void setAsRpgSprite();

    AnimatedSprite();
    ~AnimatedSprite();
};

#endif // ANIMATEDSPRITE_H
