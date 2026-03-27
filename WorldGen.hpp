#pragma once

#include <random>
#include <vector>

#include "enums/Direction.hpp"
#include "datatypes/RoomId.hpp"
#include "datatypes/Coords.hpp"
#include "RoomNode.hpp"

constexpr Direction directionLookup[3][3] ={
    {Direction::NORTH_WEST,     Direction::NORTH,       Direction::NORTH_EAST},
    {Direction::WEST,           Direction::NORTH,       Direction::EAST},
    {Direction::SOUTH_WEST,     Direction::SOUTH,       Direction::SOUTH_EAST}
};

typedef struct neighborRoom {
    Coords childCoords;
    RoomId parentId;
    Direction directionFromParent;
    Direction directionToParent;
} NeighborRoom;

class WorldGen {
    public:
        WorldGen(int rows, int columns, int roomCount);
        
    private:
        std::vector<std::vector<RoomId>> _roomGrid;
        std::vector<RoomNode> _roomNodes;
        std::mt19937 _rng;

        RoomTheme _upperTheme;
        RoomTheme _middleTheme;
        RoomTheme _lowerTheme;

        int _greatestDepth = 0;

        int _generateGrid(int rows, int columns, int roomCount);
        void _addNeighbors(std::vector<NeighborRoom>* childRooms, 
                Coords coords, RoomId id);
        void _printWorld();
        void _generateRoomNode(RoomId roomId, RoomId parentId, Coords roomCoords);
        void _differentiateRooms();
        int _depth(RoomId parentRoomId);

        RoomTheme getMiddleToUpperTheme(RoomTheme middle);
        RoomTheme getLowerToMiddleTheme(RoomTheme lower);
};
