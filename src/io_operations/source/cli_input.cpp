#include "../headers/cli_input.h"
#define COMMAND_FILE "commands.json"

CliInput::CliInput() {loadCommands(COMMAND_FILE);}

std::string CliInput::getInput()
{
    bool valid_command = false;
    std::string command = "";
    while (!valid_command)
    {
        std::cout << "Enter command: ";
        std::string input = input_processor.input();

        try
        {
            command = getCommand(input);
            valid_command = true;
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what()  << '\n';
            std::cerr << "Please try again." << std::endl;
        }
    }
    return command;
}

std::string CliInput::getCommand(const std::string& input)
{
    if(command_map.find(input) == command_map.end())
    {
        throw std::invalid_argument("Unknown command: " + input);
    }
    return command_map[input];
}

void CliInput::loadCommands(const std::string& file_name)
{
    if(std::ifstream file{file_name})
    {
        json json_object;
        file >> json_object;

        for(auto& element : json_object.items())
        {
            const std::string command = element.key();
            const std::string key = element.value();

            if(key_map.find(key) != key_map.end())
            {
                throw std::invalid_argument("Duplicate key found in commands: " + key);
            }

            if(command_map.find(command) != command_map.end())
            {
                throw std::invalid_argument("Duplicate command found in commands: " + command);
            }

            command_map[command] = key;
            key_map[key] = command;
        }
    }
    else
    {
        std::cerr << "Could not open file: " << file_name << "\nDefault commands loading." << std::endl;
        loadDefaultCommands();
    }
}


void CliInput::loadDefaultCommands()
{
    json default_commands = {
        {"a", "attack"},
        {"ms", "my_ships"},
        {"es", "enemy_ships"},
        {"q", "end_game"},
        {"ve", "view_enemy"},
        {"vm", "view_my"},
        {"f", "boards"},
        {"n", "next_ability"},
        {"s", "save_game"},
        {"l", "load_game"},
        {"u", "apply_ability"},
        {"h", "help"}
    };

    for (auto& element : default_commands.items()) {
        const std::string command = element.key();
        const std::string key = element.value();

        if (key_map.find(key) != key_map.end()) {
            throw std::invalid_argument("Duplicate key found in default commands: " + key);
        }

        if (command_map.find(command) != command_map.end()) {
            throw std::invalid_argument("Duplicate command found in default commands: " + command);
        }

        command_map[command] = key;
        key_map[key] = command;
    }
}