#include "../headers/out_of_bounds_exception.h"

OutOfBoundsException::OutOfBoundsException(const std::string& message) : GameException(message) {}