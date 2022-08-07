#include "scenemanager.h"
#include "scenebase.h"

SceneBase* SceneManager::scene = NULL;

SceneBase *SceneManager::getScene()
{
    return scene;
}

void SceneManager::changeScene(SceneBase *_scene)
{
    scene = _scene;
}

void SceneManager::renderTo(sf::RenderTarget &target)
{
    if (scene != NULL) {
        scene->drawScene(target);
    }
}

void SceneManager::updateScene()
{
    if (scene != NULL) {
        scene->updateScene();
    }
}

void SceneManager::handleInputForScene(sf::Keyboard::Key key)
{
    if (scene != NULL) {
        scene->handleInput(key);
    }
}
