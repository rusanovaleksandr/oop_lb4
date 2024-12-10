#include <iostream>
#include <map>
#include <functional>
#include <utility> 
#include "../../game_modules/headers/ship_manager.h"
#include "../../game_modules/headers/game_board.h"
#include "../../save-load/headers/game_state.h"
#include "input_processor.h"
#include "../../exceptions/headers/exceptions.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CliInput
{
    InputProcessor input_processor;
    std::map<std::string, std::string> key_map;
    std::map<std::string, std::string> command_map;

public:
    CliInput();
    std::string getInput();
    std::string getCommand(const std::string& input);
    void loadCommands(const std::string& file_name);

private:
    void loadDefaultCommands();
};