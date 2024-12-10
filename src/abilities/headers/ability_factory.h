#ifndef ABILITY_FACTORY_H
#define ABILITY_FACTORY_H

#include "iability_factory.h"
#include "double_damage_factory.h"
#include "bombardment_factory.h"
#include "scanner_factory.h"
#include "../../rendering/headers/game_message.h"
#include "../../io_operations/headers/input_processor.h"


class AbilityFactory
{
    GameBoard& board;
    ShipManager& ship_manager;

    std::shared_ptr<DoubleDamageFactory> _double_damage_factory;
    std::shared_ptr<BombardmentFactory> _bombardment_factory;
    std::shared_ptr<ScannerFactory> _scanner_factory;
public:
    AbilityFactory(GameBoard& board, ShipManager& manager);
    AbilityFactory(const AbilityFactory& other);
    AbilityFactory(AbilityFactory &&other);

    AbilityFactory& operator = (const AbilityFactory& other);
    AbilityFactory& operator = (AbilityFactory &&other);

    ~AbilityFactory() = default;

    std::shared_ptr<DoubleDamageFactory> getDoubleDamageFactory();
    std::shared_ptr<BombardmentFactory> getBombardmentFactory();
    std::shared_ptr<ScannerFactory> getDoubleScannerFactory();

};


#endif