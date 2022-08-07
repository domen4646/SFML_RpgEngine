#include "mapplayer.h"
#include "../rendering/animatedsprite.h"
#include "../physics/movementprocessor.h"
#include "../scenes/scenemap.h"
#include "../map/gamemap.h"

void MapPlayer::setPlayerTextureID(unsigned int tex)
{
    playerTexture = tex;
    sprite->setImage(tex);
    ((AnimatedSprite*) sprite)->setAsRpgSprite();
}

MapPlayer::MapPlayer(SceneMap *ref)
{
    printf("MapPlayer %p\n", this);
    setReferenceScene(ref);
    sprite = new AnimatedSprite();
    direction = Direction::Down;
    sprite->setDirection(direction);
    delete moveProc;
    moveProc = new MovementProcessor(this);
    //moveProc = new MovementProcessor(this);
}

void MapPlayer::update()
{
    MapObject::update();
    if (!getMovementProcessor()->isDone() || !SceneMap::getPlayerMovementEnabled() || mapRef->anyAction()) {
        return;
    }
    if (!checkArrowKeys()) {
        return;
    }
    sprite->setDirection(direction);
    getMovementProcessor()->enqueue_direction_as_movement(direction);
}

int MapPlayer::getMovementSpeed()
{
    return 16;
}

void MapPlayer::onMovementFinished()
{
    mapRef->getMap()->playerMoveInteraction();
}
/*
void MapPlayer::draw(sf::RenderTarget &target)
{
    if (!getMovementProcessor()->isMoving()) {
        sprite->draw(target, 0);
        return;
    }
    sprite->draw(target, (getMovementProcessor()->getFrame() - 1) / getFactor());
}
*/
bool MapPlayer::checkMovement()
{
    //return true;
    //printf("canMoveTo(%i, %i)\n", mX, mY);
    return canMoveTo(mX, mY, direction);
}

bool MapPlayer::checkArrowKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction = Direction::Left;
        mX--;
        if (!checkMovement()) {
            mX++;
            sprite->setDirection(direction);
            return false;
        }
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = Direction::Up;
        mY--;
        if (!checkMovement()) {
            mY++;
            sprite->setDirection(direction);
            return false;
        }
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction = Direction::Right;
        mX++;
        if (!checkMovement()) {
            mX--;
            sprite->setDirection(direction);
            return false;
        }
        return true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction = Direction::Down;
        mY++;
        if (!checkMovement()) {
            mY--;
            sprite->setDirection(direction);
            return false;
        }
        return true;
    }
    return false;
}
