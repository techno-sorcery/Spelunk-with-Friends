#pragma once

#include "enums/WorldGenEnums.hpp"
#include <array>
#include <cstdint>
#include <string_view>

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

#define COMMON_RARITY 60
#define UNCOMMON_RARITY 25
#define RARE_RARITY 15

typedef struct roomTypeEntry {
    // Generation data
    RoomType type;

    RoomRarity rarity;
    RoomRisk risk;

    uint8_t allowedLayouts;
    uint32_t allowedThemes;
    uint32_t tags;

    // Room definition
    std::string_view shortDesc;
    std::string_view longDesc;
} RoomTypeEntry;

constexpr int roomLayoutProbability[3][4] = {
    {5, 70, 100, 0}, // UPPER
    {15, 60, 80, 100}, // MIDDLE
    {20, 70, 100, 0}, // LOWER
};

constexpr std::array<RoomTheme, 3> upperThemes = {
    RoomTheme::CAVERN,
    RoomTheme::LIMESTONE,
    RoomTheme::SANDSTONE
};

constexpr std::array<RoomTheme, 4> middleThemes = {
    RoomTheme::LUSH,
    RoomTheme::CRYSTAL,
    RoomTheme::FLOODED,
    RoomTheme::RUINED
};

constexpr std::array<RoomTheme, 4> lowerThemes = {
    RoomTheme::INFESTED,
    RoomTheme::VOLCANIC,
    RoomTheme::ABYSSAL,
    RoomTheme::VOID
};

extern const RoomTypeEntry roomTypeEntries[];
