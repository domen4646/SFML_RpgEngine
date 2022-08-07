#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include "../engine.h"

class SceneMap;
class SpriteBase;
class MovementProcessor;

class MapObject
{
protected:
    SpriteBase* sprite = NULL;
    SceneMap* mapRef = NULL;
    Direction direction = Direction::Down;
    int moveSpeed = 8;
    bool through = false;


    MovementProcessor* moveProc = NULL;
    boost::coroutines2::coroutine<void>::pull_type* movementCoroutine = NULL;

    // Map coordinate X and Y
    int mX;
    int mY;

public:
    MapObject();
    ~MapObject();

    bool visible = true;

    virtual void draw(sf::RenderTarget& target);
    virtual int getMovementSpeed();
    int getFactor();
    bool canGoThrough();
    bool isOnCoordinate(int _mX, int _mY);

    void setMapPositon(int X, int Y);

    MovementProcessor* getMovementProcessor();
    Direction getDirection();

    void setPosition(float X, float Y);
    sf::Vector2f getPosition();
    void setReferenceScene(SceneMap* smap);
    void setDirection(Direction dir);
    void setSprite(SpriteBase* spr);
    virtual bool canMoveTo(int X, int Y, Direction dir);

    void getMapCoordinates(int* p_mX, int* p_mY);
    void getCoordsInFrontOfObject(int* p_mX, int* p_mY);

    virtual void onMovementFinished();

    virtual void update();
};

#endif // MAPOBJECT_H
