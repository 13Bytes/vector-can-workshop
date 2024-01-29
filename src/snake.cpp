#include "snake.h"

Snake::Snake (Game *game) {
    this->initializeBody();
    this->game = game;
}

void Snake::moveUp (void) {
    if (direction != Direction::SOUTH) {
        const Position targetPosition = getNeighboringPosition (body.front(), Direction::NORTH);
        body.push_front (targetPosition);
        direction = Direction::NORTH;
        
        if (!game->checkApples (targetPosition)) {
            body.pop_back();
        }
    } else {
        // Illegal move
    }
}

void Snake::moveDown (void) {
    if (direction != Direction::NORTH) {
        const Position targetPosition = getNeighboringPosition (body.front(), Direction::SOUTH);
        body.push_front (targetPosition);
        direction = Direction::SOUTH;
        
        if (!game->checkApples (targetPosition)) {
            body.pop_back();
        }
    } else {
        // Illegal move
    }
}

void Snake::moveLeft (void) {
    if (direction != Direction::EAST) {
        const Position targetPosition = getNeighboringPosition (body.front(), Direction::WEST);
        body.push_front (targetPosition);
        direction = Direction::WEST;
        
        if (!game->checkApples (targetPosition)) {
            body.pop_back();
        }
    } else {
        // Illegal move
    }
}

void Snake::moveRight (void) {
    if (direction != Direction::WEST) {
        const Position targetPosition = getNeighboringPosition (body.front(), Direction::EAST);
        body.push_front (targetPosition);
        direction = Direction::EAST;
        
        if (!game->checkApples (targetPosition)) {
            body.pop_back();
        }
    } else {
        // Illegal move
    }

}

Position_Vector Snake::getBody (void) {
    Position_Vector result(body.begin(), body.end());
    return result;
}

int Snake::getLength() {
    return body.size();
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
            result = Position {position.x, mod ((position.y - 1) - 1, mapSize) + 1};
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