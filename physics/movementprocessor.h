#ifndef MOVEMENTPROCESSOR_H
#define MOVEMENTPROCESSOR_H

#include "../engine.h"
//#include <map>
#include <queue>

class MapObject;

class MovementProcessor
{
public:
    enum MovementCommand {
        MOVE_COMMAND_NULL = 0,
        MOVE_LEFT = 1,
        MOVE_UP = 2,
        MOVE_RIGHT = 3,
        MOVE_DOWN = 4,
        MOVE_RANDOM = 5,
        TURN_LEFT = 6,
        TURN_UP = 7,
        TURN_RIGHT = 8,
        TURN_DOWN = 9,
        TURN_RANDOM = 10
    };

private:
    //static std::map<MovementCommand, sf::Vector2f> commandToCoor;

    std::queue<MovementProcessor::MovementCommand> moveCommands;
    bool skipIfCannotMove = false;
    bool moving = false;
    bool canMove = true;
    MovementCommand currentCommand = MOVE_COMMAND_NULL;

    bool done = true;
    bool* donechk = NULL;

    // Old X and Y
    float oldX;
    float oldY;

    // Target X and Y for movement
    float tX;
    float tY;

    // Movement speed
    int moveSpeed;

    unsigned int movFrame = 0;

    // obj
    MapObject* moveObject = NULL;

    void getNextCommand();
    bool processMovement(boost::coroutines2::coroutine<void>::push_type &sink);
    bool processDir(MovementProcessor::MovementCommand command);

public:
    MovementProcessor(MapObject* obj);
    void enqueue_movement(std::vector<MovementCommand> commands, bool _skipIfCannotMove);
    void enqueue_direction_as_movement(Direction dir);

    void setCoordinates(float X, float Y);
    bool isMoving();
    bool isDone();
    unsigned int getFrame();

    void update(boost::coroutines2::coroutine<void>::push_type &sink);
};

#endif // MOVEMENTPROCESSOR_H
