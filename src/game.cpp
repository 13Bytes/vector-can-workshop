#include "game.h"

bool Game::checkApples(Position position) {
  for (Position_Vector::iterator it = this->apples.begin(); it != this->apples.end(); ++it) {
    if (it->x == position.x && it->y == position.y) {
      return true;
    } else {
      return false;
    }
  }
}

Position_Vector Game::getApples() { return this->apples; }