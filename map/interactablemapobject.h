#ifndef INTERACTABLEMAPOBJECT_H
#define INTERACTABLEMAPOBJECT_H

#include "mapobject.h"

class EventPage;
class GameMap;

class InteractableMapObject : public MapObject
{
private:
    std::vector<EventPage*> event_pages;
    int active_page = -1;

    bool active = true;
    void updatePage();
    RenderPriority renderPriority = RenderPriority::BelowCharacters;
    GameMap* gameMap = NULL;

    int initialX;
    int initialY;
    Direction initialDirection = Direction::Down;

public:
    InteractableMapObject(GameMap* ref, int _X, int _Y, Direction _dir = Direction::Down);
    bool isActive();
    EventPage* getActivePage();
    void addEventPage(EventPage* page);
    void refresh();
    void reload();
    void interact(InteractionType type, SceneMap* sceneMap);
    bool shouldChangeDirection();

    //bool isOnCoordinate(int _mX, int _mY);
};

#endif // INTERACTABLEMAPOBJECT_H
