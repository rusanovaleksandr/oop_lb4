#ifndef OUT_OF_BOUNDS_EXCEPTION
#define OUT_OF_BOUNDS_EXCEPTION
#include "game_exception.h"


class OutOfBoundsException : public GameException
{
public:
    OutOfBoundsException(const std::string& message);
};

#endif