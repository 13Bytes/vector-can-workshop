#pragma once

#include <deque>
#include "game.h"

class Snake {
    public:
        Snake (Game game);
        ~Snake (void);

        void moveUp (void);
        void moveDown (void);
        void moveLeft (void);
        void moveRight (void);
        int getLength (void);
        Position_Vector getBody (void);

    private:
        const int mapSize = 10;
        Game game;
        std::deque<Position> body;
        Direction direction;
        void initializeBody (void);

        Position getNeighboringPosition (Position position, Direction direction);

        /**
         * Returns a mod b. Also works with negative numbers as a.
        */
        int mod (int a, int b);
};