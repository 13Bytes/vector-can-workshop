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
    Position result;
    switch (direction) {
        case NORTH:
            result = Position {position.x, mod ((position.y + 1) - 1, mapSize) + 1};
        break;

        case EAST:
            result = Position {mod ((position.x + 1) - 1, mapSize) + 1, position.y};
        break;

        case SOUTH:
            result = Position {position.x, ((position.y - 1) - 1 % mapSize) + 1};
        break;

        case WEST:
            result = Position {mod ((position.x - 1) - 1, mapSize) + 1, position.y};
        break;
    }
    return result;
}

int Snake::mod (int a, int b) {
    if (a < 0) {
        return b - (-a % b);
    } else {
        return a % b;
    }
}