#include "../headers/save_file_damaged_exception.h"

SaveFileDamagedException::SaveFileDamagedException(const std::string& message) : GameException(message) {}