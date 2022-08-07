#include "directionalsprite.h"
#include "../spriteset.h"

void DirectionalSprite::onImageSet()
{
    Spriteset::splitPtrInto((sf::Texture*) sprite.getTexture(), 4, 1, spriteRectange);
    onDirectionSet();
}

void DirectionalSprite::onDirectionSet()
{
    sprite.setTextureRect(spriteRectange[(int) direction]);
}

DirectionalSprite::DirectionalSprite()
{

}
