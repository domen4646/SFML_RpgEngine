#include "interactablemapobject.h"
#include "eventpage.h"
#include "../scenes/scenemap.h"
#include "gamemap.h"


InteractableMapObject::InteractableMapObject(GameMap *ref, int _X, int _Y, Direction _dir)
{
    gameMap = ref;
    initialX = _X;
    initialY = _Y;
    initialDirection = _dir;
    setMapPositon(_X, _Y);
}

bool InteractableMapObject::isActive()
{
    return active;
}

EventPage *InteractableMapObject::getActivePage()
{
    if (active_page < 0 || active_page >= event_pages.size()) {
        return NULL;
    }
    return event_pages[active_page];
}

void InteractableMapObject::addEventPage(EventPage *page)
{
    event_pages.push_back(page);
}

void InteractableMapObject::refresh()
{
    for (active_page = event_pages.size() - 1; active_page >= 0; active_page--) {
        if (event_pages[active_page]->isActive(this)) {
            updatePage();
            return;
        }
    }
    updatePage();
}

void InteractableMapObject::reload()
{
    setMapPositon(initialX, initialY);
    setDirection(initialDirection);
    refresh();
}

void InteractableMapObject::interact(InteractionType type, SceneMap *sceneMap)
{
    if (getActivePage()->getInteractionType() == type) {
        COR_FUNC a = getActivePage()->getAction();
        if (a == NULL) {
            return;
        }
        sceneMap->setInteractionAction(a, this, type);
    }
}

bool InteractableMapObject::shouldChangeDirection()
{
    if (getActivePage() == NULL) {
        return false;
    }
    if (getActivePage()->getDirectionFix()) {
        return false;
    }
    if (getActivePage()->getRenderPriority() != RenderPriority::SameAsCharacters) {
        return false;
    }
    return true;
}
/*
bool InteractableMapObject::isOnCoordinate(int _mX, int _mY)
{
    return (mX == _mX && mY == _mY);
}
*/
void InteractableMapObject::updatePage()
{
    EventPage* ep = getActivePage();

    if (ep == NULL) {
        if (renderPriority != RenderPriority::BelowCharacters) {
            gameMap->changeEventRenderPriority(this, renderPriority, RenderPriority::BelowCharacters);
            renderPriority = RenderPriority::BelowCharacters;
        }
    }
    else {
        RenderPriority nextPriority = ep->getRenderPriority();
        if (nextPriority != renderPriority) {
            gameMap->changeEventRenderPriority(this, renderPriority, nextPriority);
            renderPriority = nextPriority;
        }
    }

    if (ep == NULL || ep->getSprite() == NULL) {
        visible = false;
        return;
    }
    printf("added\n");
    setSprite(ep->getSprite());
}

