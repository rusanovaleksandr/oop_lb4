#ifndef CELL_ALREADY_ATTACKED_EXCEPTION
#define CELL_ALREADY_ATTACKED_EXCEPTION
#include "game_exception.h"

class CellAlreadyAttackedException : public GameException
{
public:
    explicit CellAlreadyAttackedException(const std::string& message);
};

#endif