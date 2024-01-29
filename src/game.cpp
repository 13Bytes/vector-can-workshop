#include "game.h"

bool Game::checkAndConsumeApple(Position position) {
  bool result;
  static int appleCount = 0;
  for (Position_Vector::iterator it = this->apples.begin(); it != this->apples.end(); ++it) {
    if (it->x == position.x && it->y == position.y) {
      result = true;
    } else {
      result = false;
    }
  }

  // Remove the element
  auto newEnd = std::remove(apples.begin(), apples.end(), position);

  // Erase the "removed" elements
  apples.erase(newEnd, apples.end());
  
  switch (appleCount++)
  {
  case 1:
    apples.push_back (Position {2, 2});
    break;

  case 2:
    apples.push_back (Position {3, 7});
    break;

  case 3:
    apples.push_back (Position {1, 10});
    break;

  case 4:
    apples.push_back (Position {8, 2});
    break;
  
  case 5:
    apples.push_back (Position {6, 1});
    break;

  case 6:
    apples.push_back (Position {10, 10});
    break;

  case 7:
    apples.push_back (Position {4, 2});
    break;

  case 8:
    apples.push_back (Position {4, 8});
    break;

  case 9:
    apples.push_back (Position {9, 1});
    break;

  case 10:
    apples.push_back (Position {7, 4});
    break;
  
  default:
    break;
  }

  return result;
}

Position_Vector Game::getApples() { return this->apples; }