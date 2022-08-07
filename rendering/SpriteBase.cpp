#include "SpriteBase.h"
#include "../gameresources.h"


void SpriteBase::onImageSet()
{

}

void SpriteBase::onDirectionSet()
{

}

void SpriteBase::draw(sf::RenderTarget &target, unsigned int movFrame)
{
    target.draw(sprite);
}

void SpriteBase::setPosition(float X, float Y)
{
    sprite.setPosition(X, Y);
}

void SpriteBase::setDirection(Direction dir)
{
    direction = dir;
    onDirectionSet();
}

float SpriteBase::getX()
{
    return sprite.getPosition().x;
}

float SpriteBase::getY()
{
    return sprite.getPosition().y;
}

Direction SpriteBase::getDirection()
{
    return direction;
}

sf::Sprite *SpriteBase::getSpriteRef()
{
    return &sprite;
}

void SpriteBase::setImage(unsigned int imageID)
{
    GameResources::setTextureTo(sprite, imageID);
    onImageSet();
}
