#pragma once

#include <vector>

#include "data_structures.h"

class Game {
 public:
  bool checkApples(Position);
  Position_Vector getApples();

 private:
  Position_Vector apples;
};