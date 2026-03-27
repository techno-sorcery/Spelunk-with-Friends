#pragma once
#include <vector>

#include "Entity.hpp"
#include "Room.hpp"
#include "datatypes/Coords.hpp"


class World {
    public:

    private:
        std::vector<Room> _rooms;
        std::vector<Entity> _entities;

};
