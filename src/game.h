#pragma once

#include "data_structures.h"
#include "snake.h"
#include <vector>

class Game {
    public:
     bool checkApples(Position);
     Position_Vector getApples();

    private:
     Snake snake;
     Position_Vector apples;
};