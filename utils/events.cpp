#include "events.h"
#include "../scenes/scenemap.h"
#include "../ui/windowmessage.h"
#include "../gameresources.h"


void events::show_message(SceneMap *sceneMap, YIELD_SINK &sink, std::string message)
{
    WindowMessage* windowMessage = new WindowMessage(message);
    sceneMap->addDrawable(windowMessage);
    windowMessage->update(sink);
    sceneMap->removeDrawable(windowMessage);
    delete windowMessage;
}

void events::transfer_player(SceneMap *sceneMap, YIELD_SINK &sink, unsigned int mapID, int mapX, int mapY, bool retainDirection, Direction direction)
{
    sceneMap->transferPlayer(sink, GameResources::getGameMap(mapID), mapX, mapY, retainDirection, direction);
}
