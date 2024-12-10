#include "../headers/bombardment_ability.h"
#include <random>

BombardmentAbility::BombardmentAbility(ShipManager& manager) : ship_manager(manager) {};

void BombardmentAbility::apply()
{
    Ship* ship = getRandomShip(ship_manager);
    int index = getRandomIndexOfSegment(ship);

    if(ship != nullptr)
    {
        ship->hitSegment(index);
    }
}


Ship* BombardmentAbility::getRandomShip(ShipManager &ship_manager)
{
    std::vector<Ship*> undestroyed_ships;

    for(int i = 0; i < ship_manager.getCountShips(); i++)
    {
        if(!ship_manager.getShipAtIndex(i).isDestroyed())
        {
            undestroyed_ships.push_back(&ship_manager.getShipAtIndex(i));
        }
    }

    if (undestroyed_ships.empty())
    {
        return nullptr;
    }

    int random_index = generateRandomIndex(undestroyed_ships.size());

    return undestroyed_ships[random_index];
}

int BombardmentAbility::getRandomIndexOfSegment(const Ship* ship)
{
    std::vector<int> undestroyed_segments;

    for (int i = 0; i < ship->getLength(); i++)
    {
        if (ship->getSegmentAtIndex(i) != DESTROYED)
        {
            undestroyed_segments.push_back(i);
        }
    }

    int random_index = generateRandomIndex(undestroyed_segments.size());

    return undestroyed_segments[random_index];
}

int BombardmentAbility::generateRandomIndex(int size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    int random_index = dis(gen);
    return random_index;
}
