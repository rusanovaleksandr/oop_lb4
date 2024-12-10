#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <vector>
#include <algorithm>
#include "ship.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ShipManager
{
private:
    std::vector<Ship> ships_;

public:
    ShipManager(const std::initializer_list<Length> &shipLengths);
    ShipManager(const std::vector<Length> &shipLengths);
    ShipManager(const ShipManager &other);
    ShipManager(ShipManager &&other);
    ~ShipManager() {};

    ShipManager &operator=(const ShipManager &other);
    ShipManager &operator=(ShipManager &&other);

    Ship& getShipAtIndex(int index);
    std::size_t getCountShips() const;

    bool allShipsDestroyed();
    void restoreShips();

    json toJson() const;
    void fromJson(const json& jsn);
};

#endif