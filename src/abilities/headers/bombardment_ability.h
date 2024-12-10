#ifndef BOMBARDMENT_ABILITY_H
#define BOMBARDMENT_ABILITY_H

#include "iability.h"
#include "../../game_modules/headers/ship_manager.h"

class BombardmentAbility : public IAbility
{
private:
    ShipManager& ship_manager;

    Ship* getRandomShip(ShipManager& ship_manager);
    int getRandomIndexOfSegment(const Ship* ship);
    int generateRandomIndex(int size);
public:
    BombardmentAbility(ShipManager& manager);
    void apply() override;
    ~BombardmentAbility() override = default;
};

#endif