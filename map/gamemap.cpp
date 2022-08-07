#include "gamemap.h"
#include "mapobject.h"
#include "interactablemapobject.h"
#include "mapplayer.h"
#include "../tilemap.h"
#include "eventpage.h"

GameMap::GameMap(Tilemap *t, SceneMap *ref)
{
    currentTilemap = t;
    sceneMap = ref;

    for (int i=0; i<3; i++) {
        eventList[i] = std::vector<InteractableMapObject*>();
        printf("ptr %p\n", &eventList[i]);
        printf("empty %i\n", eventList[i].empty());
    }

    //player = new MapPlayer(ref);
}

void GameMap::setPlayer(MapPlayer *p)
{
    player = p;
}
/*
void GameMap::addMapObject(MapObject *obj)
{
    mapObjectList.push_back(obj);
}

MapObject *GameMap::getMapObject(unsigned int index)
{
    return mapObjectList[index];
}
*/

void GameMap::draw(sf::RenderTarget &target)
{
    currentTilemap->drawTiles(target);
    /*for (MapObject* obj : mapObjectList) {
        obj->draw(target);
    }*/
    for (InteractableMapObject* imo : eventList[0]) {
        imo->draw(target);
    }
    for (InteractableMapObject* imo : eventList[1]) {
        imo->draw(target);
    }
    if (player != NULL) {
        player->draw(target);
    }
    afterDraw(target);
}

void GameMap::afterDraw(sf::RenderTarget &target)
{
    for (InteractableMapObject* imo : eventList[2]) {
        imo->draw(target);
    }
}

void GameMap::update()
{
    if (player != NULL) {
        player->update();
    }
    /*for (MapObject* obj : mapObjectList) {
        obj->update();
    }*/
    for (int i=0; i<3; i++) {
        for (InteractableMapObject* imo : eventList[i]) {
            imo->update();
        }
    }
}

bool GameMap::canMoveTo(int X, int Y, Direction dir)
{
    return currentTilemap->isFieldPassable(X, Y, dir);
}

bool GameMap::isOutOfMap(int X, int Y)
{
    return currentTilemap->isFieldOutOfMap(X, Y);
}

bool GameMap::isCollisonWithEvent(int X, int Y, Direction dir, MapObject* source)
{
    bool is_player = (source == player);
    for (InteractableMapObject* imo : eventList[1]) {
        if (imo->isOnCoordinate(X, Y)) {
            if (is_player) {
                imo->interact(InteractionType::PlayerTouch, sceneMap);
            }
            return true;
        }
    }
    if (!is_player && player->isOnCoordinate(X, Y)) {
        ((InteractableMapObject*) source)->interact(InteractionType::EventTouch, sceneMap);
    }
    return false;
}

InteractableMapObject *GameMap::getObjectInFrontOfPlayer(RenderPriority priority)
{
    int chkX, chkY;
    player->getCoordsInFrontOfObject(&chkX, &chkY);
    printf("Coords %i %i %i\n", chkX, chkY, priority);
    for (InteractableMapObject* imo : eventList[(int)priority]) {
        printf("Checking %p\n", imo);
        if (imo->isActive() && imo->isOnCoordinate(chkX, chkY)) {
            return imo;
        }
    }
    return NULL;
}

InteractableMapObject *GameMap::getObjectAtPlayer(RenderPriority priority)
{
    int chkX, chkY;
    player->getMapCoordinates(&chkX, &chkY);
    for (InteractableMapObject* imo : eventList[(int)priority]) {
        if (imo->isActive() && imo->isOnCoordinate(chkX, chkY)) {
            return imo;
        }
    }
    return NULL;
}

void GameMap::onLoad()
{
    for (int i=0; i<3; i++) {
        for (InteractableMapObject* imo : eventList[i]) {
            imo->reload();
        }
    }
}

void GameMap::attemptInteraction()
{
    InteractableMapObject* imo = NULL;
    imo = getObjectAtPlayer(RenderPriority::BelowCharacters);
    if (imo != NULL && imo->getActivePage() != NULL &&
            imo->getActivePage()->getInteractionType() == InteractionType::ActionButton) {
        imo->interact(InteractionType::ActionButton, sceneMap);
        return;
    }
    imo = getObjectInFrontOfPlayer(RenderPriority::SameAsCharacters);
    printf("IMO %p\n", imo);
    if (imo != NULL && imo->getActivePage() != NULL &&
            imo->getActivePage()->getInteractionType() == InteractionType::ActionButton) {
        imo->interact(InteractionType::ActionButton, sceneMap);
        return;
    }
    imo = getObjectAtPlayer(RenderPriority::AboveCharacters);
    if (imo != NULL && imo->getActivePage() != NULL &&
            imo->getActivePage()->getInteractionType() == InteractionType::ActionButton) {
        imo->interact(InteractionType::ActionButton, sceneMap);
        return;
    }
}

void GameMap::playerMoveInteraction()
{
    InteractableMapObject* imo = NULL;
    imo = getObjectAtPlayer(RenderPriority::BelowCharacters);
    if (imo != NULL && imo->getActivePage() != NULL &&
            imo->getActivePage()->getInteractionType() == InteractionType::PlayerTouch) {
        imo->interact(InteractionType::PlayerTouch, sceneMap);
        return;
    }
    imo = getObjectAtPlayer(RenderPriority::AboveCharacters);
    if (imo != NULL && imo->getActivePage() != NULL &&
            imo->getActivePage()->getInteractionType() == InteractionType::PlayerTouch) {
        imo->interact(InteractionType::PlayerTouch, sceneMap);
        return;
    }
}

void GameMap::addEvent(InteractableMapObject *obj)
{
    EventPage* page = obj->getActivePage();
    if (page == NULL) {
        eventList[0].push_back(obj);
        return;
    }
    printf("added\n");
    eventList[(int)page->getRenderPriority()].push_back(obj);
    printf("added\n");
}

void GameMap::changeEventRenderPriority(InteractableMapObject *event, RenderPriority _old, RenderPriority _new)
{
    int i = (int)_old;
    printf("ptr %p\n", &eventList[i]);
    printf("empty %i\n", eventList[i].empty());
    if (!eventList[i].empty()) {
        eventList[i].erase(std::remove(eventList[i].begin(), eventList[i].end(), event), eventList[i].end());
    }
    eventList[(int)_new].push_back(event);
}


