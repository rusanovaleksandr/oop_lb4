#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <functional>
#include <map>
#include "../../rendering/headers/game_board_drawer.h"
#include "../../rendering/headers/game_message.h"
#include "../../save-load/headers/game_state.h"
#include "../../game_modules/headers/game_board.h"
#include "../../game_modules/headers/game.h"
#include "render_engine.h"
#include "render_tracker.h"


template<typename InputMethod, typename GameBoardRenderer, typename MessageRenderer>
class Controller
{
    Game& game;
    InputMethod input_method;
    RenderTracker<GameBoardRenderer, MessageRenderer> render_tracker;
    std::map<std::string, std::function<void()>> commands;

public:
    Controller(Game& game): game(game), render_tracker(game) {initializeCommands();}
    void initializeCommands();
    void run();
};

#include "controller.hpp"




#endif