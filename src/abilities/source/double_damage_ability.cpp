#include "../headers/double_damage_ability.h"

DoubleDamageAbility::DoubleDamageAbility(GameBoard& board) : board(board) {}

void DoubleDamageAbility::apply()
{
    board.setDoubleDamageFlag(true);
}
