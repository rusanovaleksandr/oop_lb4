#ifndef SCANNER_ABILITY_H
#define SCANNER_ABILITY_H

#include "iability.h"
#include "../../game_modules/headers/game_board.h"
#include "../../rendering/headers/game_message.h"
#include "../../rendering/headers/console_printer.h"


class ScannerAbility : public IAbility
{
    int x_{0}, y_{0};
    GameBoard& board;
    std::shared_ptr<GameMessage> result_reveal;
public:
    ScannerAbility(Coords coordinate, GameBoard& board, std::shared_ptr<GameMessage> game_message);
    void apply() override;
    ~ScannerAbility() override = default;
};

#endif