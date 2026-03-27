#pragma once
#include <string>

typedef unsigned int EntityId;

class Entity {
    public:
        virtual ~Entity() = default;

        Entity(EntityId id, std::string name, std::string shortDescription, std::string longDescription) {
            _id = id;
            _name = name;
            _shortDescription = shortDescription;
            _longDescription = longDescription;
        }

        EntityId getId() {
            return _id;
        }

        std::string getName() {
            return _name;
        }

        std::string getAdjective() {
            return _adjective;
        }

        std::string getShortDescription() {
            return _shortDescription;
        }

        std::string getLongDescription() {
            return _longDescription;
        }


    private:
        EntityId _id;

        std::string _name;
        std::string _adjective;
        std::string _shortDescription;
        std::string _longDescription;
};
