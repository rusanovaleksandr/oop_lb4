#ifndef NO_ABILITIES_EXCEPTION
#define NO_ABILITIES_EXCEPTION
#include "game_exception.h"

class NoAbilitiesException : public GameException
{
public:
    explicit NoAbilitiesException(const std::string& message);
};

#endif