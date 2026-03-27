#pragma once

#include <unordered_map>
#include <vector>

#include "datatypes/RoomId.hpp"
#include "datatypes/Coords.hpp"
#include "enums/Direction.hpp"
#include "enums/WorldGenEnums.hpp"

class RoomNode {
    public:
        const RoomId roomId;

        const RoomDepth roomDepth;

        const int rootDepth;
        const Coords roomCoords;

        RoomNode(RoomId id, RoomDepth depth, int rootDepth, Coords coords) 
            : roomId(id), 
            roomDepth(depth), 
            rootDepth(rootDepth), 
            roomCoords(coords){
        }

        int maxExits();
        bool checkExit(Direction direction);
        void setExit(Direction direction, RoomId roomId);
        int countExits();
        std::vector<RoomId> getExitRoomIds();

        RoomLayout getRoomLayout() {
            return _roomLayout;
        }

        void setRoomLayout(RoomLayout layout) {
            _roomLayout = layout;
        }

        RoomTheme getRoomTheme() {
            return _roomTheme;
        }

        void setRoomTheme(RoomTheme theme) {
            _roomTheme = theme;
        }

        RoomType getRoomType() {
            return _roomType;
        }

        void setRoomType(RoomType type) {
            _roomType = type;
        }

    private:
        std::unordered_map<Direction, RoomId> _exits{};

        RoomLayout _roomLayout;
        RoomTheme _roomTheme;
        RoomType _roomType;
};
