#include "WorldGen.hpp"
#include "enums/WorldGenEnums.hpp"
#include "WorldGenTables.hpp"

#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <random>

WorldGen::WorldGen(int rows, int columns, int roomCount) {
    std::random_device rd;
    int totalRooms = 0;
    int iterations = 0;

    // Repeat until satisfactory generation
    while ( totalRooms < roomCount || totalRooms > roomCount + ROOM_THRESH ||
            _greatestDepth < TARGET_DEPTH || _greatestDepth > TARGET_DEPTH + DEPTH_THRESH) {

        // Initialize empty variables and arrays
        _greatestDepth = 0;
        _roomNodes.clear();
        _roomGrid = std::vector<std::vector<RoomId>>(rows, std::vector<RoomId>(columns, ROOM_ID_NULL));

        // Generate random themes
        _upperTheme = upperThemes[_rng() % upperThemes.size()];
        _middleTheme = middleThemes[_rng() % middleThemes.size()];
        _lowerTheme = lowerThemes[_rng() % lowerThemes.size()];

        // Seed random number generator
        _rng = std::mt19937(rd());

        // Generate grid and iterate
        totalRooms = _generateGrid(rows, columns, roomCount);
        iterations++;
    }

    // Now apply types and themes to the rooms
    _differentiateRooms();

    _printWorld();
    std::cout << "Iterations: " << iterations << "\n";

}

RoomTheme WorldGen::getLowerToMiddleTheme(RoomTheme lower) {
    switch (lower) {
        case RoomTheme::INFESTED:
            return RoomTheme::DECAYING;
        case RoomTheme::VOLCANIC:
            return RoomTheme::CRACKED;
        case RoomTheme::ABYSSAL:
            return RoomTheme::UNDERWATER;
        case RoomTheme::VOID:
            return RoomTheme::DISTORTED;
        default:
            return lower;
    }
}

RoomTheme WorldGen::getMiddleToUpperTheme(RoomTheme middle) {
    switch (middle) {
        case RoomTheme::LUSH:
            return RoomTheme::OVERGROWN;
        case RoomTheme::CRYSTAL:
            return RoomTheme::CRYSTALLINE;
        case RoomTheme::FLOODED:
            return RoomTheme::DAMP;
        case RoomTheme::RUINED:
            return RoomTheme::LIGHT_RUINS;
        default:
            return middle;
    }
}

// Apply types and themes to rooms based on depth, layout, and probabilities
void WorldGen::_differentiateRooms() {

    // Iterate through room nodes
    for (RoomNode& node : _roomNodes) {

        // Decide whether to attempt loop
        if (_rng() % 100 < 50) {
            std::vector<neighborRoom> neighborRooms;
            _addNeighbors(&neighborRooms, node.roomCoords, node.roomId);
            
            // Find loop candidate amongst neighbors
            for (NeighborRoom neighbor : neighborRooms) {
                RoomId neighborId = _roomGrid[neighbor.childCoords.X][neighbor.childCoords.Y];

                // Make sure neighbor exists
                if (neighborId != ROOM_ID_NULL) {
                    RoomNode* neighborNode =  &_roomNodes[neighborId];

                    // Build loop if within 1 level of node and not already hub-sized
                    if (neighborNode->rootDepth >= node.rootDepth - 1 &&
                            neighborNode->rootDepth <= node.rootDepth + 1 &&
                            neighborNode->countExits() < 4) {

                        // Create link
                        neighborNode->setExit(neighbor.directionToParent, node.roomId);
                        node.setExit(neighbor.directionFromParent, neighborId);
                        break;
                    }
                }
            }
        }

        // Prune nodes with too few exits
        switch (node.countExits()) {
            case 1:
                node.setRoomLayout(RoomLayout::TERMINUS);
                break;
            case 2:
                node.setRoomLayout(RoomLayout::CORRIDOR);
                break;
            case 3:
                node.setRoomLayout(RoomLayout::JUNCTION);
                break;
            case 4:
                node.setRoomLayout(RoomLayout::HUB);
                break;
        }

        // Promote neighboring candidates for transitional themes
        for (RoomId neighborId : node.getExitRoomIds()) {

            if (node.roomDepth == RoomDepth::MIDDLE && 
                    _roomNodes[neighborId].roomDepth == RoomDepth::UPPER) { // Middle -> Upper
                _roomNodes[neighborId].setRoomTheme(getMiddleToUpperTheme(_middleTheme));

            } else if (node.roomDepth == RoomDepth::LOWER && 
                    _roomNodes[neighborId].roomDepth == RoomDepth::MIDDLE) { // Lower -> Middle
                _roomNodes[neighborId].setRoomTheme(getLowerToMiddleTheme(_lowerTheme));
            }
        }
    }
}

// Find depth from roomId to root
int WorldGen::_depth(RoomId parentRoomId) {
    if (parentRoomId == -1) {
        return 0;
    }

    std::queue<std::pair<RoomId, int>> roomQueue;
    std::set<RoomId> visitedRooms;

    roomQueue.push({parentRoomId, 1});

    // BFS to find shortest path
    while (!roomQueue.empty()) {
        auto [roomId, depth] = roomQueue.front();

        // Set greatest depth
        if (depth > _greatestDepth) {
            _greatestDepth = depth;
        }

        roomQueue.pop();

        // Return if root
        if (roomId == 0) {
            return depth;
        }

        // Visit neighbors
        for (RoomId neighborId : _roomNodes[roomId].getExitRoomIds()) {

            // Check if neighbor has already been visited
            if (visitedRooms.count(neighborId) == 0) {

                // If not, add to queue
                visitedRooms.insert(neighborId);
                roomQueue.push({neighborId, depth + 1});
            }
        }
    }

    return 0;
}

// Generate new room and add to vector
void WorldGen::_generateRoomNode(RoomId roomId, RoomId parentId, Coords roomCoords) {
    int rootDepth = _depth(parentId);
    float normDepth = float(rootDepth) / TARGET_DEPTH; // Distance to root node

    int nodeProb = _rng() % 100;
    RoomLayout layout;
    RoomDepth depth;
    RoomTheme theme;

    // Pathing based on depth (distance from root / target depth)
    if (normDepth <= UPPER_DEPTH) { 
        depth = RoomDepth::UPPER;
        theme = _upperTheme;

    } else if (normDepth <= MIDDLE_DEPTH) {
        depth = RoomDepth::MIDDLE;
        theme = _middleTheme;

    } else {
        depth = RoomDepth::LOWER;
        theme = _lowerTheme;
    }

    // Set layout based on probabilities and depth
    if (nodeProb < 
            roomLayoutProbability[static_cast<int>(depth)][static_cast<int>(RoomLayout::TERMINUS)]) {
        layout = RoomLayout::TERMINUS;

    } else if (nodeProb < 
            roomLayoutProbability[static_cast<int>(depth)][static_cast<int>(RoomLayout::CORRIDOR)]) {
        layout = RoomLayout::CORRIDOR;

    } else if (nodeProb < 
            roomLayoutProbability[static_cast<int>(depth)][static_cast<int>(RoomLayout::JUNCTION)]) {
        layout = RoomLayout::JUNCTION;

    } else {
        layout = RoomLayout::HUB;
    }

    // Create room node
    _roomNodes.push_back(RoomNode(roomId, depth, rootDepth, roomCoords));
    _roomNodes.back().setRoomLayout(layout);
    _roomNodes.back().setRoomTheme(theme);
}

// Generate world map
int WorldGen::_generateGrid(int rows, int columns, int roomCount) {
    RoomId roomId = 0;

    // Elect center room as the root
    Coords rootCoords = {columns / 2, rows / 2};
    std::vector<NeighborRoom> prospectiveRooms = {{rootCoords, -1, Direction::EAST, Direction::EAST}};

    // Continue until room count is reached, or no rooms left to traverse
    while (!prospectiveRooms.empty() && (roomId < roomCount || _greatestDepth < TARGET_DEPTH)) {

        // Select random empty room and remove from vector
        int roomIndex = _rng() % prospectiveRooms.size();
        NeighborRoom childRoom = prospectiveRooms[roomIndex];

        prospectiveRooms.erase(prospectiveRooms.begin() + roomIndex);

        // Unpack room balues
        Coords roomCoords = childRoom.childCoords;
        RoomId parentId = childRoom.parentId;
        Direction directionFromParent = childRoom.directionFromParent;
        Direction directionToParent = childRoom.directionToParent;

        // Skip generation if not empty, if parent has too many exits, or if parent is too deep
        if (_roomGrid[roomCoords.X][roomCoords.Y] != ROOM_ID_NULL || 
                (parentId > -1 && _roomNodes[parentId].countExits() == _roomNodes[parentId].maxExits()) ||
                (parentId > -1 && _roomNodes[parentId].rootDepth > TARGET_DEPTH + 3)) {
            continue;
        }

        // Create node and add to list
        _generateRoomNode(roomId, parentId, roomCoords);

        // Create connection to/from parent if not root
        if (parentId > -1) {
            _roomNodes[roomId].setExit(directionToParent, parentId);
            _roomNodes[parentId].setExit(directionFromParent, roomId);
        }

        // Mark on grid and add empty neighbors to vector
        _roomGrid[roomCoords.X][roomCoords.Y] = roomId;
        _addNeighbors(&prospectiveRooms, roomCoords, roomId);

        roomId++;
    } 

    return roomId;
}

// Print a map of the world
void WorldGen::_printWorld() {
    int gridSizeY = _roomGrid.size();
    int gridSizeX = _roomGrid[0].size();

    // Print grid
    for (int y = 0; y < gridSizeY; y++) {

        for (int pass = 0; pass < 3; pass++) {
            for (int x = 0; x < gridSizeX; x++) {

                RoomId gridRoomId = _roomGrid[x][y];

                if (gridRoomId != ROOM_ID_NULL) {
                    switch (pass) {
                        case 0:

                            if (_roomNodes[gridRoomId].checkExit(Direction::NORTH_WEST)) {
                                std::cout << "\\ ";
                            } else {
                                std::cout << "  ";
                            }

                            if (_roomNodes[gridRoomId].checkExit(Direction::NORTH)) {
                                std::cout << "| ";
                            } else {
                                std::cout << "  ";
                            }

                            if (_roomNodes[gridRoomId].checkExit(Direction::NORTH_EAST)) {
                                std::cout << "/ ";
                            } else {
                                std::cout << "  ";
                            }
                            break;

                        case 1:
                            if (_roomNodes[gridRoomId].checkExit(Direction::WEST)) {
                                std::cout << "— ";
                            } else {
                                std::cout << "  ";
                            }

                            if (gridRoomId == 0) {
                                std::cout << "R ";

                            } else {

                                switch (_roomNodes[gridRoomId].getRoomTheme()) {
                                    // Upper
                                    case RoomTheme::CAVERN:
                                        std::cout << "CV";
                                        break;
                                    case RoomTheme::LIMESTONE:
                                        std::cout << "LS";
                                        break;
                                    case RoomTheme::SANDSTONE:
                                        std::cout << "SS";
                                        break;

                                        // Upper -> Middle
                                    case RoomTheme::OVERGROWN:
                                        std::cout << "OG";
                                        break;
                                    case RoomTheme::CRYSTALLINE:
                                        std::cout << "CY";
                                        break;
                                    case RoomTheme::DAMP:
                                        std::cout << "DP";
                                        break;
                                    case RoomTheme::LIGHT_RUINS:
                                        std::cout << "LR";
                                        break;

                                        // Middle
                                    case RoomTheme::LUSH:
                                        std::cout << "LU";
                                        break;
                                    case RoomTheme::CRYSTAL:
                                        std::cout << "CR";
                                        break;
                                    case RoomTheme::FLOODED:
                                        std::cout << "FL";
                                        break;
                                    case RoomTheme::RUINED:
                                        std::cout << "RN";
                                        break;

                                        // Middle -> Lower
                                    case RoomTheme::DECAYING:
                                        std::cout << "DC";
                                        break;
                                    case RoomTheme::CRACKED:
                                        std::cout << "CK";
                                        break;
                                    case RoomTheme::UNDERWATER:
                                        std::cout << "UW";
                                        break;
                                    case RoomTheme::DISTORTED:
                                        std::cout << "DT";
                                        break;

                                        // Lower
                                    case RoomTheme::INFESTED:
                                        std::cout << "IN";
                                        break;
                                    case RoomTheme::VOLCANIC:
                                        std::cout << "VO";
                                        break;
                                    case RoomTheme::ABYSSAL:
                                        std::cout << "AB";
                                        break;
                                    case RoomTheme::VOID:
                                        std::cout << "VD";
                                        break;

                                    default:
                                        std::cout << "??";
                                        break;
                                }


                                // switch (_roomNodes[gridRoomId].roomDepth) {

                                //     case (RoomDepth::LOWER):
                                //         std::cout << "L ";
                                //         break;

                                //     case (RoomDepth::MIDDLE):
                                //         std::cout << "M ";
                                //         break;

                                //     case (RoomDepth::UPPER):
                                //         std::cout << "U ";
                                //         break;

                                // }
                            }
                            if (_roomNodes[gridRoomId].checkExit(Direction::EAST)) {
                                std::cout << "— ";
                            } else {
                                std::cout << "  ";
                            }
                            break;

                        case 2:
                            if (_roomNodes[gridRoomId].checkExit(Direction::SOUTH_WEST)) {
                                std::cout << "/ ";
                            } else {
                                std::cout << "  ";
                            }

                            if (_roomNodes[gridRoomId].checkExit(Direction::SOUTH)) {
                                std::cout << "| ";
                            } else {
                                std::cout << "  ";
                            }

                            if (_roomNodes[gridRoomId].checkExit(Direction::SOUTH_EAST)) {
                                std::cout << "\\ ";
                            } else {
                                std::cout << "  ";
                            }
                            break;
                    }
                } else {
                    std::cout << ". . . ";
                }
            }
            std::cout << "\n";
        }
    }
}

// Get a cell's neighboring cells
void WorldGen::_addNeighbors(std::vector<NeighborRoom>* childRooms, Coords coords, RoomId id) {
    int gridSizeY = _roomGrid.size();
    int gridSizeX = _roomGrid[0].size();

    std::vector<Coords> neighbors = {};

    // Rows
    for (int yOffset = -1; yOffset <= 1; yOffset++) {

        // Columns
        for (int xOffset = -1; xOffset <= 1; xOffset++) {
            Coords neighborCoords = {coords.X + xOffset, coords.Y + yOffset};


            // Check validity of neighbor
            if (neighborCoords.X >= 0 && neighborCoords.X < gridSizeX && // X boundaries
                    neighborCoords.Y >= 0 && neighborCoords.Y < gridSizeY && // Y boundaries
                    !(xOffset == 0 && yOffset == 0)) { // Not same as room

                Direction directionFromParent = directionLookup[yOffset + 1][xOffset + 1];
                Direction directionToParent = directionLookup[(-yOffset) + 1][(-xOffset) + 1];

                // Push neighbor coords to list
                childRooms->push_back({neighborCoords, id, directionFromParent, directionToParent});
            }
        }
    }
}
