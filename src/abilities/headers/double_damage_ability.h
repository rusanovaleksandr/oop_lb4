#ifndef DOUBLE_DAMAGE_ABILITY_H
#define DOUBLE_DAMAGE_ABILITY_H

#include "iability.h"
#include "../../game_modules/headers/game_board.h"


class DoubleDamageAbility : public IAbility
{
private:
    GameBoard& board;
public:
    DoubleDamageAbility(GameBoard& board);
    void apply() override;
    ~DoubleDamageAbility() override = default;
};

#endif