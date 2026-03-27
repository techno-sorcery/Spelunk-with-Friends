#pragma once

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

    // Treasure
    CACHE, // Small cache of supplies, low encounter risk
    CORPSE, // The corpse of another spelunker, medium encounter risk
    TREASURE, // Valuable treasure, high encounter risk

    // Hazards
    NEST, // A nest crawling with enemies
    AMBUSH, // Seems like a normal room, until you try to leave and get attacked
    ANTECHAMBER, // Mini boss fight leading up to main one
    BOSS, // The main showdown

    // Landmarks
    CAMPSITE, // An abandoned campsite
    FOUNTAIN, // A fountain containing a mysterious liquid
    CATHEDRAL, // High-ceilinged cavern with dramatic formations
    CHASM, // An impassible hole in the ground
    LAKE, // An underground lake

    // Lore
    ALTAR, // An altar to an unknown god

    // Themed
    TREE, // (Lush) A large, overgrown tree

    // Puzzle
    // SWITCHES, // Three switches on the wall

};
