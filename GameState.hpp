#pragma once

#include "World.hpp"

typedef unsigned int GameTicks;

class GameState {

    private:
        World _world;
        GameTicks _gameTicks;
};
