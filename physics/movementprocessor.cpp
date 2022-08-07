#include "movementprocessor.h"
#include "../map/mapobject.h"

/*
    enum MovementCommand {
        MOVE_COMMAND_NULL,
        MOVE_LEFT,
        MOVE_UP,
        MOVE_RIGHT,
        MOVE_DOWN,
        MOVE_RANDOM,
        TURN_LEFT,
        TURN_UP,
        TURN_RIGHT,
        TURN_DOWN,
        TURN_RANDOM
    }
*/
sf::Vector2f commandToCoor[] = {
    sf::Vector2f(0, 0),
    sf::Vector2f(-32, 0),
    sf::Vector2f(0, -32),
    sf::Vector2f(32, 0),
    sf::Vector2f(0, 32),
    sf::Vector2f(0, 0),

    sf::Vector2f(0, 0),
    sf::Vector2f(0, 0),
    sf::Vector2f(0, 0),
    sf::Vector2f(0, 0),
    sf::Vector2f(0, 0)
};

// Use for random turn and random move
MovementProcessor::MovementCommand movs[] = {
    MovementProcessor::MovementCommand::MOVE_LEFT,
    MovementProcessor::MovementCommand::MOVE_UP,
    MovementProcessor::MovementCommand::MOVE_RIGHT,
    MovementProcessor::MovementCommand::MOVE_DOWN
};
MovementProcessor::MovementCommand turs[] = {
    MovementProcessor::MovementCommand::TURN_LEFT,
    MovementProcessor::MovementCommand::TURN_UP,
    MovementProcessor::MovementCommand::TURN_RIGHT,
    MovementProcessor::MovementCommand::TURN_DOWN
};
Direction turDirs[] = {
    Direction::Left,
    Direction::Up,
    Direction::Right,
    Direction::Down
};

bool MovementProcessor::processDir(MovementProcessor::MovementCommand command) {
    if (command < MovementProcessor::MovementCommand::TURN_LEFT || command > MovementProcessor::MovementCommand::TURN_DOWN) {
        return false;
    }

    // Set direction here
    moveObject->setDirection(turDirs[command - MovementCommand::TURN_LEFT]);
    return true;
}

bool MovementProcessor::processMovement(boost::coroutines2::coroutine<void>::push_type &sink)
{
    //printf("Called proc mov\n");
    if (currentCommand < MovementProcessor::MovementCommand::MOVE_LEFT ||
            currentCommand > MovementProcessor::MovementCommand::MOVE_DOWN) {
        return false;
    }

    sf::Vector2f vec = commandToCoor[currentCommand];
    tX = oldX + vec.x;
    tY = oldY + vec.y;

    float X;
    float Y;

    moving = true;
    //printf("Move speed %i\n", moveSpeed);

    float part = 0.0f;
    for (movFrame=1; movFrame<=moveSpeed; movFrame++) {
        part = ((float)movFrame / (float)moveSpeed);
        X = oldX + (tX - oldX) * part;
        Y = oldY + (tY - oldY) * part;

        //printf("Pos %f %f\n", X, Y);
        // Set position here
        moveObject->setPosition(X, Y);
        sink();
    }
    //printf("Done\n");
    movFrame = 0;
    oldX = tX;
    oldY = tY;
    moving = false;
    return true;
}

#include <typeinfo>
MovementProcessor::MovementProcessor(MapObject *obj)
{
    moveObject = obj;
    moveSpeed = moveObject->getMovementSpeed();
    printf("MovSpeed %s %i\n", typeid(obj).name(), moveObject->getMovementSpeed());
    donechk = &done;
    oldX = moveObject->getPosition().x;
    oldY = moveObject->getPosition().y;
    printf("doneptr %p\n", &done);
}

void MovementProcessor::getNextCommand()
{
    if (moveCommands.size() == 0) {
        currentCommand = MovementCommand::MOVE_COMMAND_NULL;
        done = true;
        return;
    }
    currentCommand = moveCommands.front();
    moveCommands.pop();
    if (currentCommand == MovementCommand::MOVE_RANDOM) {
        currentCommand = movs[rand() % SIZE(movs)];
    }
    else if (currentCommand == MovementCommand::TURN_RANDOM) {
        currentCommand = turs[rand() % SIZE(turs)];
    }
}

void MovementProcessor::enqueue_movement(std::vector<MovementProcessor::MovementCommand> commands, bool _skipIfCannotMove)
{
    skipIfCannotMove = _skipIfCannotMove;
    for (MovementProcessor::MovementCommand command : commands) {
        moveCommands.push(command);
    }
    if (done) {
        done = false;
        getNextCommand();
    }
}

void MovementProcessor::enqueue_direction_as_movement(Direction dir)
{
    skipIfCannotMove = false;
    moveCommands.push((MovementCommand)(MovementCommand::MOVE_LEFT + dir));
    if (done) {
        done = false;
        getNextCommand();
    }
}

void MovementProcessor::setCoordinates(float X, float Y)
{
    oldX = X;
    oldY = Y;
}

bool MovementProcessor::isMoving()
{
    return moving;
}

bool MovementProcessor::isDone()
{
    return done;
}

unsigned int MovementProcessor::getFrame()
{
    return movFrame;
}

void MovementProcessor::update(boost::coroutines2::coroutine<void>::push_type &sink)
{
    while (true) {

        while (true) {
            sink();
            //printf("done %i %p\n", done, &done);
            if (!done) {
                break;
            }
        }
        printf("Command %i\n", (int)currentCommand);

        if (currentCommand == MovementCommand::MOVE_COMMAND_NULL) {
            getNextCommand();
            if (done) {
                moveObject->onMovementFinished();
            }
            continue;
        }

        if (processDir(currentCommand)) {
            sink();
            getNextCommand();
            if (done) {
                moveObject->onMovementFinished();
            }
            continue;
        }

        processMovement(sink);
        getNextCommand();
        if (done) {
            moveObject->onMovementFinished();
        }
    }
}
