#pragma once

#include <vector>

typedef struct {
    int x, y; 
} Position;

enum Direction {
    NORTH, EAST, SOUTH, WEST
};

typedef std::vector<Position> Position_Vector;