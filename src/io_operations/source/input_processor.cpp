#include "../headers/input_processor.h"

std::string InputProcessor::input()
{
    std::string input;
    getline(std::cin, input);
    return input;
}