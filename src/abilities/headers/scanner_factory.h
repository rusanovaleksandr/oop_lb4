#ifndef SCANNER_FACTORY_H
#define SCANNER_FACTORY_H
#include <sstream>
#include <string>
#include "iability_factory.h"
#include "scanner_ability.h"
#include "../../rendering/headers/game_message.h"
#include "../../io_operations/headers/input_processor.h"
#include "../../rendering/headers/console_printer.h"

class ScannerFactory : public IAbilityFactory
{
    GameBoard& board;
    std::shared_ptr<InputProcessor> input_processor;
    std::shared_ptr<GameMessage> game_message;
public:
    ScannerFactory(GameBoard& board, std::shared_ptr<InputProcessor> coord_request, std::shared_ptr<GameMessage> ship_detected);
    std::shared_ptr<IAbility> create() override;
    std::string getName() const override;
    ~ScannerFactory() override = default;

    virtual json toJson() override; 
    virtual void fromJson(const json& jsn) override;
};


#endif