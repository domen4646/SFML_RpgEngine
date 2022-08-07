#ifndef EVENTS_H
#define EVENTS_H

#include "../engine.h"

class SceneMap;

namespace events {

// Shows an in-game message
void show_message(SceneMap* sceneMap, YIELD_SINK &sink, std::string message);

// Transfer player to another map
void transfer_player(SceneMap* sceneMap, YIELD_SINK &sink, unsigned int mapID, int mapX, int mapY,
                     bool retainDirection = true, Direction direction = Direction::Down);

void set_boolean(unsigned int boolID, bool value);

void set_variable(unsigned int varID, long long value);

}

#endif // EVENTS_H
