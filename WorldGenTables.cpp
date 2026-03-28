#include "WorldGenTables.hpp"
#include "enums/WorldGenEnums.hpp"

const int roomLayoutProbability[3][4] = {
    {5, 70, 100, 0}, // UPPER
    {15, 60, 80, 100}, // MIDDLE
    {20, 70, 100, 0}, // LOWER
};

const std::array<RoomTheme, 3> upperThemes = {
    RoomTheme::CAVERN,
    RoomTheme::LIMESTONE,
    RoomTheme::SANDSTONE
};

const std::array<RoomTheme, 4> middleThemes = {
    RoomTheme::LUSH,
    RoomTheme::CRYSTAL,
    RoomTheme::FLOODED,
    RoomTheme::RUINED
};

const std::array<RoomTheme, 4> lowerThemes = {
    RoomTheme::INFESTED,
    RoomTheme::VOLCANIC,
    RoomTheme::ABYSSAL,
    RoomTheme::VOID
};
