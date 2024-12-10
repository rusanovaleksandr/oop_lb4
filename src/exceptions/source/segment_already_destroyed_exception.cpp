#include "../headers/segment_already_destroyed_exception.h"

SegmentAlreadyDestroyedException::SegmentAlreadyDestroyedException(const std::string& message) : GameException(message) {}