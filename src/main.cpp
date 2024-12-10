#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "./save-load/headers/file_manager.h"
#include "./game_modules/headers/game_board.h"
#include "./abilities/headers/ability_manager.h"
#include "game.h"
#include <fstream>
#include "../../io_operations/headers/cli_input.h"
#include "../../io_operations/headers/controller.h"
#include "../../rendering/headers/game_board_renderer.h"
#include "../../rendering/headers/message_renderer.h"

int main()
{
    try
    {
        Game game;
        MessageRenderer renderer;
        game.addListener(&renderer);
        Controller<CliInput, GameBoardRenderer, MessageRenderer> controller(game);

        controller.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}