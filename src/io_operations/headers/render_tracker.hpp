#include "render_tracker.h"

template<typename GameBoardRenderer, typename MessageRenderer>
std::string RenderTracker<GameBoardRenderer, MessageRenderer>::getCurrentState()
{
    return current_state;
}

template<typename GameBoardRenderer, typename MessageRenderer>
void RenderTracker<GameBoardRenderer, MessageRenderer>::update(const std::string& state)
{
    current_state = state;
    render_engine.update(state);
}

