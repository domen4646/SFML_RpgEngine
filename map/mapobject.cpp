#include "mapobject.h"
#include "../rendering/SpriteBase.h"
#include "../scenes/scenemap.h"
#include "../map/gamemap.h"
#include "../physics/movementprocessor.h"
#include <boost/bind.hpp>

MapObject::MapObject()
{
    printf("MapObject %p\n", this);
    mX = 0;
    mY = 0;
    moveProc = new MovementProcessor(this);
    movementCoroutine = new boost::coroutines2::coroutine<void>::pull_type(boost::bind(&MovementProcessor::update, moveProc, _1));
}

MapObject::~MapObject()
{
    delete movementCoroutine;
    delete moveProc;
}

void MapObject::draw(sf::RenderTarget &target)
{
    if (!visible) {
        return;
    }
    if (!getMovementProcessor()->isMoving()) {
        sprite->draw(target, 1);
        return;
    }
    sprite->draw(target, (getMovementProcessor()->getFrame() - 1) / getFactor());
}

int MapObject::getMovementSpeed()
{
    return moveSpeed;
}

int MapObject::getFactor()
{
    if (getMovementSpeed() / 4 == 0) {
        return 1;
    }
    return getMovementSpeed() / 4;
}

bool MapObject::canGoThrough()
{
    return through;
}

bool MapObject::isOnCoordinate(int _mX, int _mY)
{
    return (mX == _mX && mY == _mY);
}

void MapObject::setMapPositon(int X, int Y)
{
    mX = X;
    mY = Y;
    setPosition(X * 32, Y * 32);
    if (moveProc != NULL) {
        moveProc->setCoordinates(X * 32, Y * 32);
    }
}

MovementProcessor *MapObject::getMovementProcessor()
{
    return moveProc;
}

Direction MapObject::getDirection()
{
    return direction;
}

void MapObject::setPosition(float X, float Y)
{
    if (sprite != NULL) {
        sprite->setPosition(X, Y);
    }
}

sf::Vector2f MapObject::getPosition()
{
    sprite->getSpriteRef()->getPosition();
}

void MapObject::setReferenceScene(SceneMap *smap)
{
    mapRef = smap;
}

void MapObject::setDirection(Direction dir)
{
    direction = dir;
    if (sprite != NULL) {
        sprite->setDirection(direction);
    }
}

void MapObject::setSprite(SpriteBase *spr)
{
    if (sprite == NULL) {
        sprite = spr;
        return;
    }
    float X = sprite->getX();
    float Y = sprite->getY();
    sprite = spr;
    sprite->setPosition(X, Y);
}

bool MapObject::canMoveTo(int X, int Y, Direction dir)
{
    if (mapRef->getMap()->isOutOfMap(X, Y)) {
        return false;
    }
    if (through) {
        return true;
    }
    if (!mapRef->getMap()->canMoveTo(X, Y, dir)) {
        return false;
    }
    return !mapRef->getMap()->isCollisonWithEvent(X, Y, dir, this);
}

void MapObject::getMapCoordinates(int *p_mX, int *p_mY)
{
    *p_mX = mX;
    *p_mY = mY;
}

void MapObject::getCoordsInFrontOfObject(int* p_mX, int* p_mY)
{
    int X = mX;
    int Y = mY;
    if (direction == Direction::Up) {
        Y--;
    }
    else if (direction == Direction::Right) {
        X++;
    }
    else if (direction == Direction::Down) {
        Y++;
    }
    else if (direction == Direction::Left) {
        X--;
    }
    *p_mX = X;
    *p_mY = Y;
}

void MapObject::onMovementFinished() {}

void MapObject::update()
{
    movementCoroutine->operator ()();
}

