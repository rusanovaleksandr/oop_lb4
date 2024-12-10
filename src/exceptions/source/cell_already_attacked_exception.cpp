#include "../headers/cell_already_attacked_exception.h"

CellAlreadyAttackedException::CellAlreadyAttackedException(const std::string& message) : GameException(message) {}