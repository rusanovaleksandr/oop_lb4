#ifndef RENDER_TRACKER_H
#define RENDER_TRACKER_H
#include <string>
#include "../../game_modules/headers/game.h"
#include "render_engine.h"

template<typename GameBoardRenderer, typename MessageRenderer>
class RenderTracker
{
    RenderEngine<GameBoardRenderer, MessageRenderer> render_engine;
    std::string current_state;
public:
    RenderTracker(Game &game) : render_engine(game), current_state("") {};
    std::string getCurrentState();
    void update(const std::string &state);
};

#include "render_tracker.hpp"

#endif