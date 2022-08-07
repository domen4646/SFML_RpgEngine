#include "scenemap.h"
#include "../map/gamemap.h"
#include "../map/mapplayer.h"
#include "../ui/drawablebase.h"
#include "../map/interactablemapobject.h"
#include "../map/eventpage.h"
#include "../utils/utils.h"
#include <boost/bind.hpp>
#include <algorithm>

bool SceneMap::playerMovementEnabled = true;
void SceneMap::clearAction()
{
    action = NULL;
}

bool SceneMap::getPlayerMovementEnabled()
{
    return playerMovementEnabled;
}

void SceneMap::setPlayerMovementEnabled(bool value)
{
    playerMovementEnabled = value;
}

void SceneMap::setAction(COR_FUNC a)
{
    if (action == NULL) {
        action_from_interaction = false;
        action = a;
    }
}

void SceneMap::setInteractionAction(COR_FUNC func, InteractableMapObject *obj, InteractionType type)
{
    if (action == NULL) {
        action_from_interaction = true;
        action = func;
        InteractionData* idata = new InteractionData();
        idata->interactionObject = obj;
        idata->sceneMap = this;
        idata->type = type;
        parameter = (void*) idata;
    }
}

void SceneMap::tintScreen(YIELD_SINK &sink, sf::Color color, unsigned int speed)
{
    utils::animate_rectangle_color(sink, &screenTint, color, speed);
}

void SceneMap::transferPlayer(YIELD_SINK &sink, GameMap *_map, int _mX, int _mY, bool retainDir, Direction _dir)
{
    tintScreen(sink, sf::Color::Black);
    if (!retainDir) {
        setMapWithPlayerCoordsAndDirection(_map, _mX, _mY, _dir);
    }
    else {
        setMapWithPlayerCoords(_map, _mX, _mY);
    }
    tintScreen(sink, sf::Color::Transparent);
}

void SceneMap::addDrawable(DrawableBase *db)
{
    drawables.push_back(db);
}

void SceneMap::removeDrawable(DrawableBase *db)
{
    drawables.erase(std::remove(drawables.begin(), drawables.end(), db), drawables.end());
}

bool SceneMap::anyAction()
{
    return (action != NULL);
}

void SceneMap::setPlayerTextureID(unsigned int id)
{
    player->setPlayerTextureID(id);
}

SceneMap::SceneMap()
{
    updateActionsFunc = new boost::coroutines2::coroutine<void>::pull_type(boost::bind(&SceneMap::updateActions, this, _1));
    player = new MapPlayer(this);
    screenTint.setSize(sf::Vector2f(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT));
    screenTint.setPosition(0, 0);
    screenTint.setFillColor(sf::Color::Transparent);
}

SceneMap::~SceneMap()
{
}

void SceneMap::setMap(GameMap *_map)
{
    map = _map;
    map->setPlayer(player);
    map->onLoad();
}

void SceneMap::setMapWithPlayerCoords(GameMap *_map, int _mX, int _mY)
{
    map = _map;
    map->setPlayer(player);
    player->setMapPositon(_mX, _mY);
    map->onLoad();
}

void SceneMap::setMapWithPlayerCoordsAndDirection(GameMap *_map, int _mX, int _mY, Direction _dir)
{
    map = _map;
    map->setPlayer(player);
    player->setMapPositon(_mX, _mY);
    player->setDirection(_dir);
    map->onLoad();
}

GameMap *SceneMap::getMap()
{
    return map;
}

void SceneMap::setParameter(void *param)
{
    parameter = param;
}

void SceneMap::drawScene(sf::RenderTarget &target)
{
    if (map != NULL) {
        map->draw(target);
    }
    for (DrawableBase* db : drawables) {
        db->draw(target);
    }
    target.draw(screenTint);
}

void SceneMap::updateScene()
{
    updateActionsFunc->operator ()();
    if (action != NULL) {
        return;
    }
    if (map != NULL) {
        map->update();
    }
}

void SceneMap::handleInput(sf::Keyboard::Key key)
{
    if (action != NULL) {
        for (DrawableBase* db : drawables) {
            if (db->acceptsInput()) {
                db->handleInput(key);
            }
        }
        return;
    }
    if (key == sf::Keyboard::Return && map != NULL) {
        map->attemptInteraction();
        return;
    }
    if (SceneMap::keyActions.count(key) > 0) {
        printf("action\n");
        setParameter((void*) this);
        setAction(keyActions[key]);
    }
}

void SceneMap::updateActions(YIELD_SINK &sink)
{
    while (true) {
        while (action == NULL) {
            sink();
        }

        InteractableMapObject* imo = NULL;
        Direction dir;
        if (action_from_interaction) {
            imo = ((InteractionData*) parameter)->interactionObject;
            if (imo->shouldChangeDirection()) {
                dir = imo->getDirection();
                Direction _d = reverse_direction(player->getDirection());
                imo->setDirection(_d);
            }
        }
        action(sink, parameter);
        if (action_from_interaction) {
            if (imo->shouldChangeDirection()) {
                imo->setDirection(dir);
            }
            delete (InteractionData*) parameter;
            action_from_interaction = false;
        }
        clearAction();
    }
}

std::map<sf::Keyboard::Key, COR_FUNC> SceneMap::keyActions;
