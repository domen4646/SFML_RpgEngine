#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "../engine.h"

class Tilemap;
class MapPlayer;
class MapObject;
class InteractableMapObject;
class SceneMap;

// TODO implement all

class GameMap
{
private:
    Tilemap* currentTilemap = NULL;
    MapPlayer* player = NULL;
    //std::vector<MapObject*> mapObjectList;
    SceneMap* sceneMap = NULL;

    std::vector<InteractableMapObject*> eventList[3];

public:
    GameMap(Tilemap* t, SceneMap* ref);
    void setPlayer(MapPlayer* p);
    //void addMapObject(MapObject* obj);
    //MapObject* getMapObject(unsigned int index);
    void draw(sf::RenderTarget& target);
    void afterDraw(sf::RenderTarget& target);
    void update();
    bool canMoveTo(int X, int Y, Direction dir);
    bool isOutOfMap(int X, int Y);
    bool isCollisonWithEvent(int X, int Y, Direction dir, MapObject* source);
    InteractableMapObject* getObjectInFrontOfPlayer(RenderPriority priority);
    InteractableMapObject* getObjectAtPlayer(RenderPriority priority);

    void onLoad();

    void attemptInteraction();
    void playerMoveInteraction();

    void addEvent(InteractableMapObject* obj);
    void changeEventRenderPriority(InteractableMapObject* event, RenderPriority _old, RenderPriority _new);
};

#endif // GAMEMAP_H
