#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "../engine.h"

class SceneBase
{
public:
    virtual void drawScene(sf::RenderTarget& target) = 0;
    virtual void updateScene() = 0;
    virtual void handleInput(sf::Keyboard::Key key) = 0;
};

#endif // SCENEBASE_H
