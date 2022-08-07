#include "engine.h"
#include "gameresources.h"
#include "scenes/scenemanager.h"
#include "scenes/scenemap.h"
#include "map/gamemap.h"
#include "map/mapobject.h"
#include "ui/windowbase.h"
#include "ui/windowmessage.h"
#include <iostream>


int main() {
    std::cout << "Starting game ..." << std::endl;

    GameResources::font.loadFromFile("terminus.ttf");

    // Load textures and tilemaps
    GameResources::loadAllTextures();
    GameResources::setupTilesets();
    GameResources::loadAllTilemaps();

    // Create scenes, gamemaps and set data
    GameResources::setupScenes();

    // Create window
    sf::RenderWindow renderWindow(sf::VideoMode(544, 416), "game");
    renderWindow.setFramerateLimit(60);

    SceneMap::keyActions.insert(std::pair<sf::Keyboard::Key, COR_FUNC>(sf::Keyboard::Escape, [](YIELD_SINK &sink, void* param) {
        printf("escape pressed\n");
        SceneMap* ref = (SceneMap*) param;
        WindowBase* wb = new WindowBase(100, 100, 256, 256);
        ref->addDrawable(wb);
        wb->update(sink);
        ref->removeDrawable(wb);
        delete wb;
    }));

    SceneMap::keyActions.insert(std::pair<sf::Keyboard::Key, COR_FUNC>(sf::Keyboard::M, [](YIELD_SINK &sink, void* param) {
        SceneMap* ref = (SceneMap*) param;
        WindowMessage* messageWindow = new WindowMessage("Hello. This is a test string in this RPG engine.\ntesting newline too!\na\na\na");
        ref->addDrawable(messageWindow);
        messageWindow->update(sink);
        ref->removeDrawable(messageWindow);
        delete messageWindow;
    }));

    // Game loop
    sf::Event event;
    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "Closing main window and game ..." << std::endl;
                renderWindow.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                SceneManager::handleInputForScene(event.key.code);
            }
        }

        renderWindow.clear();
        SceneManager::updateScene();
        SceneManager::renderTo(renderWindow);
        renderWindow.display();
    }
}






// TEST IS BELOW
// don't use

/*
#include <iostream>
#include <SFML/Graphics.hpp>
#include <boost/coroutine2/coroutine.hpp>

sf::Text textRender;
std::string textCur;
std::string textFull = "Hello, this is a sample string to prove that coroutines work, or something";

void cor(boost::coroutines2::coroutine<void>::push_type& sink) {
    sink();
    for (int i=0; i<textFull.length(); i++) {
        textCur += textFull[i];
        textRender.setString(textCur);
        sink();
    }
    while (true) {
        sink();
    }
}

int main()
{
    sf::Font font;
    font.loadFromFile("terminus.ttf");
    textRender.setFont(font);
    textRender.setString("");
    textRender.setCharacterSize(16);
    textRender.setPosition(10, 10);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML WORKS");
    window.setFramerateLimit(60);

    sf::Event event;
    boost::coroutines2::coroutine<void>::pull_type updateFunc {cor};
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        updateFunc();

        window.clear(sf::Color::Black);
        window.draw(textRender);
        window.display();
    }

    return 0;
}
*/
