#pragma once

#include <vector>
#include <algorithm>
#include "data_structures.h"

class Game {
 public:
  bool checkAndConsumeApple(Position);
  Position_Vector getApples();

 private:
  Position_Vector apples = {Position {5, 5}};
};