#ifndef SAVE_DAMAGED_EXCEPTION
#define SAVE_DAMAGED_EXCEPTION
#include "game_exception.h"


class SaveFileDamagedException : public GameException
{
public:
    SaveFileDamagedException(const std::string& message);
};

#endif