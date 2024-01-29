#pragma once

#include "snake.h"
#include <vector>

typedef struct {
    int x, y; 
} Position;

typedef std::vector<Position> Position_Vector;

class Game {
    public:


    private:
        Snake snake;
        Position_Vector apples;
};