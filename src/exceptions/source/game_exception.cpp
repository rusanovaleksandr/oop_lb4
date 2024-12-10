#include "../headers/game_exception.h"

GameException::GameException(const std::string& message) : std::runtime_error(message) {}
