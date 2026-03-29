#pragma once

#include <cstdint>

enum RoomTags : uint32_t {
    RT_NONE         = 0,

    // Core role (what happens here)
    RT_ENCOUNTER    = 1 << 0,   // Combat or threat
    RT_REWARD       = 1 << 1,   // Player gains something
    RT_INTERACTION  = 1 << 2,   // Player can interact
    RT_TRIAL        = 1 << 3,   // Risk/reward or challenge

    // Player impact (broad effects)
    RT_HEALING      = 1 << 4,   // Restores health
    RT_STATUS       = 1 << 5,   // Buff or debuff
    RT_RESOURCE     = 1 << 6,   // Resource gain or loss

    // Identity / flavor
    RT_LANDMARK     = 1 << 7,   // Navigational anchor
    RT_LORE         = 1 << 8,   // Story / information

    // Navigation impact
    RT_ONE_WAY      = 1 << 9,   // Cannot backtrack
    RT_HEIGHT       = 1 << 10,  // Vertical traversal (climb/drop)

    // Special generation rules
    RT_PAIRED       = 1 << 11,  // Appears in linked pairs
    RT_UNIQUE       = 1 << 12   // Limited occurrences
};

enum RoomThemeFlags : uint32_t {
    TF_NONE         = 0,

    // Upper
    TF_CAVERN       = 1 << 0,
    TF_LIMESTONE    = 1 << 1,
    TF_SANDSTONE    = 1 << 2,

    // Upper -> Middle
    TF_OVERGROWN    = 1 << 3,
    TF_CRYSTALLINE  = 1 << 4,
    TF_DAMP         = 1 << 5,
    TF_LIGHT_RUINS  = 1 << 6,

    // Middle
    TF_LUSH         = 1 << 7,
    TF_CRYSTAL      = 1 << 8,
    TF_FLOODED      = 1 << 9,
    TF_RUINED       = 1 << 10,

    // Middle -> Lower
    TF_DECAYING     = 1 << 11,
    TF_CRACKED      = 1 << 12,
    TF_UNDERWATER   = 1 << 13,
    TF_DISTORTED    = 1 << 14,

    // Lower
    TF_INFESTED     = 1 << 15,
    TF_VOLCANIC     = 1 << 16,
    TF_ABYSSAL      = 1 << 17,
    TF_VOID         = 1 << 18
};

enum RoomLayoutFlags : uint8_t {
    LF_TERMINUS    = 1 << 0,
    LF_CORRIDOR    = 1 << 1,
    LF_JUNCTION    = 1 << 2,
    LF_HUB         = 1 << 3
};

enum class RoomRisk {
    LOW,
    MEDIUM,
    HIGH
};

enum class RoomRarity {
    COMMON,
    UNCOMMON,
    RARE
};

enum class RoomLayout {
    TERMINUS,
    CORRIDOR,
    JUNCTION,
    HUB,
};

enum class RoomDepth {
    UPPER,
    MIDDLE,
    LOWER,
};

enum class RoomTheme {
    // Upper, sparse and not super interesting
    CAVERN, // A classic crack in the earth
    LIMESTONE, // Interesting geologic formations
    SANDSTONE, // Dry and eroded desert cave

    // Upper -> Middle
    OVERGROWN, // x -> Lush
    CRYSTALLINE, // x -> Crystal
    DAMP, // x -> Damp
    LIGHT_RUINS, // x -> Ruins

    // Middle, fun to explore
    LUSH, // Overgrown with lush greenery
    CRYSTAL, // Stunning crystalized formations
    FLOODED, // Damp and inundated with water
    RUINED, // Ruins of a bygone civilization

    // Middle -> Lower
    DECAYING, 
    CRACKED, 
    UNDERWATER, 
    DISTORTED, 
    // HALLOWED, // Special ruined -> Void

    // Lower, hazardous and foreboding
    INFESTED, // Infested with arthropods and fungi
    VOLCANIC, // Hellish and geologically active
    ABYSSAL, // Full of dangerous acquatic life 
    VOID, // Home to elderich horrors

    COUNT
};

enum class RoomType {
    NONE, // An undifferentiated room

    // Upper 
    STALAGTITES,

    // Navigation
    CRAWLSPACE, // A one-way crawlspace connecting part of a loop

    // Rewards
    CACHE, // Small cache of supplies, low encounter risk
    CORPSE, // The corpse of another spelunker, medium encounter risk, lore
    TREASURE, // Valuable treasure, high encounter risk
    ALTAR, // An altar to an unknown god (random good/bad event)
    FOUNTAIN, // A fountain containing a mysterious liquid (buffs/debuffs)

    // Hazards
    NEST, // A nest crawling with enemies
    ENCOUNTER, // A regular room with an enemy encounter
    AMBUSH, // Seems like a normal room, until you try to leave and get attacked
    THIEF, // Steals one of your items and runs off to another part of the dungeon
    ANTECHAMBER, // Mini boss fight leading up to main one
    BOSS, // The main showdown

    // Landmarks
    CAMPSITE, // Abandoned campsite with loot and lore
    CATHEDRAL, // High-ceilinged cavern with dramatic formations
    CHASM, // Impassible hole in the ground
    LAKE, // Underground lake
    PAINTINGS, // Ancient cave paintings revealing lore

    // Lush
    TREE, // A wise, overgrown tree. Chopping it down reveals loot but triggers encounter
    MUSHROOM, // Giant mushroom landmark that can be used for food

    // Ruins
    BUILDING, // Ruined building containing loot and lore
    GRAVEYARD, // Multiple graves can be excavated for loot at risk of an encounter
    SWITCHES, // Logic puzzle involving flicking switches to open door

    // Crystal
    MIRROR, // Rotate crystal columns to open a door

    // Flooded
    LILYPAD, // Toss out useless items to find right lilypads to cross
    DOCK, // Dock overlooking a lake; can fish for items/food

    // Infested
    HOST, // Dead traveler containing info on the infestation's source
    HIVE, // Outer edges of the infestation, traces of enemies
    EPICENTER, // Infestation epicenter filled with enemies
    TENDRILS, // Tendrils that must be cut down fill the room

    // Volcanic
    MAGMA, // Magma impeeds passage, and you must wait for it to abate

    // Abyssal
    SHIP, // Sunken ship with enemies and treasure
    PEARLS, // Harvest the pearls for treasure, or a dangerous encounter

    // Void
    ENDLESS, // An endless corridor requiring the player to turn back to pass
    SHATTERED, // Glitched room with hidden lore
    INVERTED, // Exits inverted, attacking players damages enemies and vice-versa
    UNSTABLE, // Teleports a player to random middle/upper chamber
};
