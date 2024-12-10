#include "../headers/ship_manager.h"

ShipManager::ShipManager(const std::initializer_list<Length> &shipLengths)
{
    for (const auto &length : shipLengths)
    {
        ships_.push_back(Ship(length));
    }
}

ShipManager::ShipManager(const std::vector<Length> &shipLengths)
{
    for (const auto &length : shipLengths)
    {
        ships_.push_back(Ship(length));
    }
}

ShipManager::ShipManager(const ShipManager &other)
{
    this->ships_ = other.ships_;
}

ShipManager::ShipManager(ShipManager &&other)
{
    this->ships_ = std::move(other.ships_);
}

ShipManager &ShipManager::operator=(const ShipManager &other)
{
    if (this != &other)
    {
        this->ships_ = other.ships_;
    }
    return *this;
}

ShipManager &ShipManager::operator=(ShipManager &&other)
{
    if (this != &other)
    {
        this->ships_ = std::move(other.ships_);
    }
    return *this;
}

Ship& ShipManager::getShipAtIndex(int index)
{
    return ships_.at(index);
}

std::size_t ShipManager::getCountShips() const
{
    return ships_.size();
}


bool ShipManager::allShipsDestroyed()
{
    return std::all_of(ships_.begin(), ships_.end(), [](const Ship& ship)
                       { return ship.isDestroyed(); });
}

void ShipManager::restoreShips()
{
    for(int i = 0; i < getCountShips(); i++)
    {
        for(int k = 0; k < getShipAtIndex(i).getLength(); k++)
        {
            getShipAtIndex(i).setSegmentAtIndex(k, INTACT);
        }
    }
}


json ShipManager::toJson() const
{
    json json_arr = json::array();

    for(const auto& ship : ships_)
    {
        json_arr.push_back(ship.toJson());
    }

    return json_arr;
}


void ShipManager::fromJson(const json& jsn)
{
    ships_.clear();
    for(const auto& ship_json : jsn)
    {
        Ship ship;
        ship.fromJson(ship_json);
        ships_.push_back(ship);
    }
}
