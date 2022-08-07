#include "gameresources.h"
#include "tileset.h"
#include "tilemap.h"
#include "scenes/scenemap.h"
#include "scenes/scenemanager.h"
#include "map/gamemap.h"
#include "map/interactablemapobject.h"
#include "map/eventpage.h"
#include "rendering/animatedsprite.h"
#include "ui/windowmessage.h"
#include <iostream>

// Definitions for static members
std::vector<sf::Texture> GameResources::game_textures;
std::vector<Tileset*> GameResources::game_tilesets;
std::vector<Tilemap*> GameResources::game_tilemaps;
std::vector<GameMap*> GameResources::game_maps;
SceneMap* GameResources::mapScene = NULL;
sf::Font GameResources::font;

SceneMap *GameResources::getMapScene()
{
    return mapScene;
}

void GameResources::addTexture(const char *filename)
{
    game_textures.push_back(sf::Texture());
    game_textures[game_textures.size() - 1].loadFromFile(filename);
}

void GameResources::setTextureTo(sf::Sprite &sprite, unsigned int textureID)
{
    sprite.setTexture(game_textures[textureID]);
}

sf::Texture GameResources::retrieveTexture(unsigned int textureID)
{
    return game_textures[textureID];
}

void GameResources::addTileset(Tileset *tileSet)
{
    game_tilesets.push_back(tileSet);
}

Tileset *GameResources::getTileset(unsigned int index)
{
    return game_tilesets[index];
}

bool GameResources::loadTilemapFromFile(const char *filename, unsigned int tilesetIndex)
{
    FILE* tilemapFile = fopen(filename, "rb");
    if (tilemapFile == NULL) {
        std::cout << "Unable to open tilemap file: " << filename << std::endl;
        addTilemap(NULL);
        return false;
    }
    Tileset* t = getTileset(tilesetIndex);
    Tilemap* tmap = new Tilemap(tilemapFile, t);
    fclose(tilemapFile);

    if (!tmap->isValid()) {
        std::cout << "Tilemap is not valid!" << std::endl;
        addTilemap(NULL);
        return false;
    }
    addTilemap(tmap);
}

void GameResources::addTilemap(Tilemap *tilemap)
{
    game_tilemaps.push_back(tilemap);
}

Tilemap *GameResources::getTilemap(unsigned int index)
{
    return game_tilemaps[index];
}

const char *texNames[] = {
    "player.png",
    "outside.png",
    "npc001.png"
};
void GameResources::loadAllTextures() {
    for (int i=0; i<SIZE(texNames); i++) {
        addTexture(texNames[i]);
    }
}

void GameResources::setupTilesets()
{
    Tileset* t = new Tileset(1);
    t->getTileData(121)->passage = false;
    t->getTileData(98)->passage = false;
    t->getTileData(0)->passage = false;
    addTileset(t);
}

void GameResources::loadAllTilemaps()
{
    loadTilemapFromFile("tilemap003.bin", 0);
    loadTilemapFromFile("tilemap004.bin", 0);
}

void GameResources::setupScenes() {
    mapScene = new SceneMap();
    mapScene->setPlayerTextureID(0);
    GameMap* gameMap = new GameMap(getTilemap(0), mapScene);
    GameMap* map004 = new GameMap(getTilemap(1), mapScene);
    game_maps.push_back(gameMap);
    game_maps.push_back(map004);
    printf("ss\n");


    AnimatedSprite* as = new AnimatedSprite();
    as->setImage(2);
    as->setAsRpgSprite();
    InteractableMapObject* imo = new InteractableMapObject(gameMap, 2, 2);
    imo->setReferenceScene(mapScene);
    imo->setSprite(as);
    EventPage* ep = new EventPage([](YIELD_SINK &sink, void* parameter) {
        WindowMessage* winme = new WindowMessage("Hello, thanks for talking to me.");
        mapScene->addDrawable(winme);
        winme->update(sink);
        mapScene->removeDrawable(winme);
        delete winme;
        winme = new WindowMessage("You can go now.");
        mapScene->addDrawable(winme);
        winme->update(sink);
        mapScene->removeDrawable(winme);
        delete winme;
    }, NULL, RenderPriority::SameAsCharacters, InteractionType::ActionButton, as);
    imo->addEventPage(ep);
    imo->refresh();
    imo->setMapPositon(2, 2);
    printf("added\n");
    gameMap->addEvent(imo);

    InteractableMapObject* obj00001 = new InteractableMapObject(gameMap, 5, 5);
    obj00001->setReferenceScene(mapScene);
    obj00001->setSprite(NULL);
    EventPage* ep00001 = new EventPage([](YIELD_SINK &sink, void* parameter) {
            WindowMessage* winme = new WindowMessage("Touch event");
            mapScene->addDrawable(winme);
            winme->update(sink);
            mapScene->removeDrawable(winme);
            delete winme;
    }, NULL, RenderPriority::BelowCharacters, InteractionType::PlayerTouch, NULL);
    obj00001->addEventPage(ep00001);
    obj00001->refresh();
    obj00001->setMapPositon(5, 5);
    gameMap->addEvent(obj00001);


    InteractableMapObject* obj00002 = new InteractableMapObject(map004, 2, 12);
    obj00002->setReferenceScene(mapScene);
    obj00002->setSprite(NULL);
    EventPage* ep00002 = new EventPage([](YIELD_SINK & sink, void* parameter) {
        mapScene->transferPlayer(sink, game_maps[0], 7, 1, false);
    }, NULL, RenderPriority::BelowCharacters, InteractionType::PlayerTouch, NULL);
    obj00002->addEventPage(ep00002);
    map004->addEvent(obj00002);


    InteractableMapObject* obj00003 = new InteractableMapObject(gameMap, 7, 0);
    obj00003->setReferenceScene(mapScene);
    obj00003->setSprite(NULL);
    EventPage* ep00003 = new EventPage([](YIELD_SINK &sink, void* parameter) {
        mapScene->transferPlayer(sink, game_maps[1], 2, 11, false, Direction::Up);
    }, NULL, RenderPriority::BelowCharacters, InteractionType::PlayerTouch, NULL);
    obj00003->addEventPage(ep00003);
    gameMap->addEvent(obj00003);

    mapScene->setMapWithPlayerCoords(gameMap, 3, 3);
    SceneManager::changeScene(mapScene);
}

GameMap* GameResources::getGameMap(unsigned int ID) {
    if (ID >= game_maps.size()) {
        return NULL;
    }
    return game_maps[ID];
}

