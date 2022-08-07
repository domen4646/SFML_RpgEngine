#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "engine.h"

class Tileset;
class Tilemap;
class SceneMap;
class GameMap;

class GameResources
{
private:
    static std::vector<sf::Texture> game_textures;
    static std::vector<Tileset*> game_tilesets;
    static std::vector<Tilemap*> game_tilemaps;
    static std::vector<GameMap*> game_maps;

    static SceneMap* mapScene;

public:
    // Textures
    static void addTexture(const char* filename);
    static void setTextureTo(sf::Sprite& sprite, unsigned int textureID);
    static sf::Texture retrieveTexture(unsigned int textureID);

    // Tilesets
    static void addTileset(Tileset* tileSet);
    static Tileset* getTileset(unsigned int index);

    // Tilemaps
    static bool loadTilemapFromFile(const char* filename, unsigned int tilesetIndex);
    static void addTilemap(Tilemap* tilemap);
    static Tilemap* getTilemap(unsigned int index);

    static void loadAllTextures();
    static void setupTilesets();
    static void loadAllTilemaps();

    static SceneMap *getMapScene();
    static void setupScenes();

    static GameMap* getGameMap(unsigned int ID);

    static sf::Font font;
};

#endif // GAMERESOURCES_H
