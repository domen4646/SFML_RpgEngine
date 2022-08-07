#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <boost/coroutine2/coroutine.hpp>

#define GAME_WINDOW_WIDTH 544
#define GAME_WINDOW_HEIGHT 416

enum Direction {
    Left = 0,
    Up = 1,
    Right = 2,
    Down = 3
};

enum RenderPriority {
    BelowCharacters = 0,
    SameAsCharacters = 1,
    AboveCharacters = 2
};

// Add para process
enum InteractionType {
    ActionButton = 0,
    PlayerTouch = 1,
    EventTouch = 2,
    Autorun = 3
};

typedef void (*ACTION_FUNC)(boost::coroutines2::coroutine<void>::push_type&);
typedef boost::coroutines2::coroutine<void>::push_type YIELD_SINK;
typedef boost::coroutines2::coroutine<void>::pull_type COROUTINE;
typedef void (*COR_FUNC)(YIELD_SINK&, void*);

#define SIZE(x) (sizeof(x) / sizeof(*x))

Direction reverse_direction(Direction original);
Direction get_random_direction();

#endif // ENGINE_H
