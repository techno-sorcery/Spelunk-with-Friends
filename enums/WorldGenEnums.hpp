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
    PATIENT_ZERO, // Dead traveler containing info on the infestation's source
    HIVE, // Outer edges of the infestation, traces of enemies
    EPICENTER, // Infestation epicenter filled with enemies
    SPORES, // Don't touch anything in the room or you'll get sick

    // Volcanic

    // Abyssal
    SHIP, // Sunken ship with enemies and treasure

    // Void
    ENDLESS, // An endless corridor requiring the player to turn back to pass
    SHATTERED, // Glitched room with hidden lore
    INVERTED, // Exits inverted, attacking players damages enemies and vice-versa
    UNSTABLE, // Teleports a player to random middle/upper chamber
};
