#pragma once

#include <vector>
#include "game.h"

class Snake {
    public:
        Snake (void);
        ~Snake (void);

        void moveUp (void);
        void moveDown (void);
        void moveLeft (void);
        void moveRight (void);
        int getLength (void);
        Position_Vector getBody (void);

    private:
        Position_Vector body;
        void initializeBody (void);
};