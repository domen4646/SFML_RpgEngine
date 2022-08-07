#include "animatedsprite.h"
#include "../utils/utils.h"
#include "../spriteset.h"

unsigned int walk_animation[] = {0, 1, 2, 1};

void AnimatedSprite::onImageSet()
{
    Spriteset::splitPtrInto2D((sf::Texture*) sprite.getTexture(), 4, 3, imageFrames);
}

// If needed, store last movFrame for optimization purposes
void AnimatedSprite::draw(sf::RenderTarget &target, unsigned int movFrame)
{
    sprite.setTextureRect(imageFrames[(int) direction][walk_animation[movFrame % SIZE(walk_animation)]]);
    target.draw(sprite);
}

void AnimatedSprite::setAsRpgSprite()
{
    sf::IntRect* downDir = imageFrames[(int) Direction::Down];
    sf::IntRect* upDir = imageFrames[(int) Direction::Up];
    sf::IntRect* leftDir = imageFrames[(int) Direction::Left];
    imageFrames[(int) Direction::Down] = leftDir;
    imageFrames[(int) Direction::Up] = downDir;
    imageFrames[(int) Direction::Left] = upDir;
}

AnimatedSprite::AnimatedSprite()
{
    imageFrames = utils::alloc_rects_2d(3, 4);
}

AnimatedSprite::~AnimatedSprite()
{
    utils::free_rects_2d(imageFrames, 4);
}
