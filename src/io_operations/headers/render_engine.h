#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H
#include <iostream>
#include <string>
#include "../../game_modules/headers/game.h"

class Game;

template<typename GameBoardRenderer, typename MessageRenderer>
class RenderEngine
{
    GameBoardRenderer game_board_renderer;
    MessageRenderer message_renderer;
    Game& game;

public:
    RenderEngine(Game &game) : game(game) {};
    void render(const std::string &command);
    void update(const std::string &command);
};

#include "render_engine.hpp"

#endif