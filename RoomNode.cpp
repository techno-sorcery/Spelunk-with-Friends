#include "RoomNode.hpp"

int RoomNode::maxExits() {
    switch(_roomLayout) {
        case RoomLayout::TERMINUS:
            return 1;
        case RoomLayout::CORRIDOR:
            return 2;
        case RoomLayout::JUNCTION:
            return 3;
        case RoomLayout::HUB:
            return 4;
    }

    return 0;
}

bool RoomNode::checkExit(Direction direction) {
    return _exits.count(direction) > 0;
}

void RoomNode::setExit(Direction direction, RoomId roomId) {
    _exits[direction] = roomId;
}

int RoomNode::countExits() {
    return _exits.size();
}

std::vector<RoomId> RoomNode::getExitRoomIds() {
    std::vector<RoomId> exitRoomIds;

    for (auto pair : _exits) {
        exitRoomIds.push_back(pair.second);
    }

    return exitRoomIds;
}
