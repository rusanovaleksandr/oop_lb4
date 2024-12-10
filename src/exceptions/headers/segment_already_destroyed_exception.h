#ifndef SEG_ALREADY_DESTROYED_H
#define SEG_ALREADY_DESTROYED_H
#include "game_exception.h"

class SegmentAlreadyDestroyedException : public GameException
{
public:
    explicit SegmentAlreadyDestroyedException(const std::string& message);
};


#endif