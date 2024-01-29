#include <snake.h>

Snake::Snake (Game game) {
    this->initializeBody();
    this->game = game;
}

void Snake::moveUp (void) {
    if (direction != Direction::SOUTH) {
        if (game.checkApple ())
    } else {
        // Illegal move
    }
}

void Snake::moveDown (void) {

}

void Snake::moveLeft (void) {
        
    if (game.checkApple ())
}

void Snake::moveRight (void) {

}

Position_Vector Snake::getBody (void) {
    return this->body;
}

void Snake::initializeBody (void) {
    this->body.clear();
    this->body.push_front (Position {1, 1});
    this->body.push_front (Position {2, 1});
    this->body.push_front (Position {3, 1});
    this->direction = Direction::EAST;
}

Position Snake::getNeighboringPosition (Position position, Direction direction) {
    switch ()
}