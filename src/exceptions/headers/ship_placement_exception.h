#ifndef SHIP_PLACE_EXCEPTION
#define SHIP_PLACE_EXCEPTION
#include "game_exception.h"

class ShipPlacementException : public GameException
{
public:
    explicit ShipPlacementException(const std::string& message);
};

#endif