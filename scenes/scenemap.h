#ifndef SCENEMAP_H
#define SCENEMAP_H

#include "scenebase.h"
#include <map>

class GameMap;
class MapPlayer;
class DrawableBase;
class InteractableMapObject;

class SceneMap : public SceneBase
{
private:
    GameMap* map = NULL;
    static bool playerMovementEnabled;
    boost::coroutines2::coroutine<void>::pull_type* updateActionsFunc = NULL;
    COR_FUNC action = NULL;
    MapPlayer* player = NULL;
    void* parameter = NULL;
    std::vector<DrawableBase*> drawables;
    void clearAction();
    bool action_from_interaction = false;

    sf::RectangleShape screenTint;

public:

    static std::map<sf::Keyboard::Key, COR_FUNC> keyActions;
    static bool getPlayerMovementEnabled();
    static void setPlayerMovementEnabled(bool value);

    SceneMap();
    virtual ~SceneMap();
    void setMap(GameMap* _map);
    void setMapWithPlayerCoords(GameMap* _map, int _mX, int _mY);
    void setMapWithPlayerCoordsAndDirection(GameMap* _map, int _mX, int _mY, Direction _dir);

    GameMap* getMap();

    void setParameter(void* param);

    virtual void drawScene(sf::RenderTarget& target) override;
    virtual void updateScene() override;
    virtual void handleInput(sf::Keyboard::Key key) override;
    void updateActions(YIELD_SINK &sink);
    void setAction(COR_FUNC a);
    void setInteractionAction(COR_FUNC func, InteractableMapObject* obj, InteractionType type);

    void tintScreen(YIELD_SINK &sink, sf::Color color, unsigned int speed = 60);
    void transferPlayer(YIELD_SINK &sink, GameMap* _map, int _mX, int _mY, bool retainDir = true, Direction _dir = Direction::Down);

    void addDrawable(DrawableBase* db);
    void removeDrawable(DrawableBase* db);

    bool anyAction();

    void setPlayerTextureID(unsigned int id);
};

struct InteractionData
{
    SceneMap* sceneMap;
    InteractableMapObject* interactionObject;
    InteractionType type;
};

#endif // SCENEMAP_H
