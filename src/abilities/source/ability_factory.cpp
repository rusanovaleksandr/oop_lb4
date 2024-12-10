#include "../headers/ability_factory.h"

AbilityFactory::AbilityFactory(GameBoard &board, ShipManager &manager) : board(board), ship_manager(manager)
{
    _double_damage_factory = std::make_shared<DoubleDamageFactory>(board);
    _bombardment_factory = std::make_shared<BombardmentFactory>(ship_manager);
    auto input_processor = std::make_shared<InputProcessor>();
    auto game_message = std::make_shared<GameMessage>();
    _scanner_factory = std::make_shared<ScannerFactory>(board, input_processor, game_message);
}

AbilityFactory::AbilityFactory(const AbilityFactory &other) : board(other.board), ship_manager(other.ship_manager)
{
    _double_damage_factory = other._double_damage_factory;
    _bombardment_factory = other._bombardment_factory;
    _scanner_factory = other._scanner_factory;
}

AbilityFactory::AbilityFactory(AbilityFactory &&other) : board(other.board), ship_manager(other.ship_manager)
{
    _double_damage_factory = std::move(other._double_damage_factory);
    _bombardment_factory = std::move(other._bombardment_factory);
    _scanner_factory = std::move(other._scanner_factory);
}

AbilityFactory &AbilityFactory::operator=(const AbilityFactory &other)
{
    if (this != &other)
    {
        board = other.board;
        ship_manager = other.ship_manager;
        _double_damage_factory = other._double_damage_factory;
        _bombardment_factory = other._bombardment_factory;
        _scanner_factory = other._scanner_factory;
    }
    return *this;
}

AbilityFactory &AbilityFactory::operator=(AbilityFactory &&other)
{
    if (this != &other)
    {
        board = other.board;
        ship_manager = other.ship_manager;
        _double_damage_factory = std::move(other._double_damage_factory);
        _bombardment_factory = std::move(other._bombardment_factory);
        _scanner_factory = std::move(other._scanner_factory);
    }
    return *this;
}

std::shared_ptr<DoubleDamageFactory> AbilityFactory::getDoubleDamageFactory()
{
    return _double_damage_factory;
}

std::shared_ptr<BombardmentFactory> AbilityFactory::getBombardmentFactory()
{
    return _bombardment_factory;
}

std::shared_ptr<ScannerFactory> AbilityFactory::getDoubleScannerFactory()
{
    return _scanner_factory;
}
