#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Entity.hpp"
#include "enums/Direction.hpp"
#include "datatypes/Coords.hpp"
#include "datatypes/RoomId.hpp"


class Room {
    public:
        Room(RoomId id, Coords coords, std::string name, std::string shortDescription, 
                std::string longDescription) {
            _id = id;
            _coords = coords;


            _name = name;
            _shortDescription = shortDescription;
            _longDescription = longDescription;
        }

        RoomId getId() {
            return _id;
        }

        Coords getCoords(){
            return _coords;
        }


        std::string getName() {
            return _name;
        }

        std::string getShortDescription() {
            return _shortDescription;
        }

        std::string getLongDescription() {
            return _longDescription;
        }

        std::vector<EntityId> getEntities() {
            return _entities;
        }

        bool checkExit(Direction direction) {
            return _exits.count(direction) > 0;
        }

        void setExit(Direction direction, RoomId roomId) {
            _exits[direction] = roomId;
        }

        int countExits() {
            return _exits.size();
        }

        std::vector<RoomId> getExitRoomIds() {
            std::vector<RoomId> exitRoomIds;

            for (auto pair : _exits) {
                exitRoomIds.push_back(pair.second);
            }

            return exitRoomIds;
        }

    private:
        RoomId _id;
        Coords _coords;


        std::string _name;
        std::string _shortDescription;
        std::string _longDescription;

        std::unordered_map<Direction, RoomId> _exits{};
        std::vector<EntityId> _entities;
};
