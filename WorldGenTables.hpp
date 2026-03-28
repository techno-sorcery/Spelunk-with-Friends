#pragma once

#include "enums/WorldGenEnums.hpp"
#include <array>

#define UPPER_DEPTH 0.4
#define MIDDLE_DEPTH 0.7
#define LOWER_DEPTH 1

#define MIN_LOWER 0.15

#define TARGET_DEPTH 15
#define DEPTH_THRESH 0

#define ROOM_THRESH 10

#define LOOP_PROB 15
#define LOOP_THRESH 5
#define LOOP_GUARANTEED 1
#define LOOP_MAX 0.1

extern const int roomLayoutProbability[3][4];

extern const std::array<RoomTheme, 3> upperThemes;
extern const std::array<RoomTheme, 4> middleThemes;
extern const std::array<RoomTheme, 4> lowerThemes;
