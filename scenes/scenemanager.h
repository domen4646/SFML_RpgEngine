#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../engine.h"

class SceneBase;

class SceneManager
{
private:
    static SceneBase* scene;

public:
    static SceneBase* getScene();
    static void changeScene(SceneBase* _scene);
    static void renderTo(sf::RenderTarget& target);
    static void updateScene();
    static void handleInputForScene(sf::Keyboard::Key key);
};

#endif // SCENEMANAGER_H
