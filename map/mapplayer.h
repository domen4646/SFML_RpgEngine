#ifndef MAPPLAYER_H
#define MAPPLAYER_H

#include "mapobject.h"

class SceneMap;

class MapPlayer : public MapObject
{
private:
    unsigned int playerTexture;
    bool checkMovement();
    bool checkArrowKeys();
    unsigned int movementFrame = 0;

public:
    void setPlayerTextureID(unsigned int tex);
    MapPlayer(SceneMap* ref);
    virtual void update() override;
    virtual int getMovementSpeed() override;
    virtual void onMovementFinished() override;

    //virtual void draw(sf::RenderTarget& target) override;
};

#endif // MAPPLAYER_H
