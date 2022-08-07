#include "../engine.h"


Direction reverse_direction(Direction original) {
    return (Direction) ((original + 2) % 4);
}

Direction get_random_direction() {
    return (Direction) (rand() % 4);
}
