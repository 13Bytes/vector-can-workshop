#include <snake.h>

Snake::Snake (void) {
    this->initializeBody();
}

Position_Vector Snake::getBody (void) {
    return this->body;
}

void Snake::initializeBody (void) {
    this->body.clear();
    // TODO:
}