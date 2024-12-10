#ifndef GAME_LISTENER_H
#define GAME_LISTENER_H

#include "game_board.h"
#include "game_message_enum.h"

class GameListener
{
public:
    virtual void onStartMessage(GameMessageEnum msg) = 0;
    virtual void onGameStateMessage(GameMessageEnum msg) = 0;
    virtual void onGameMessage(GameMessageEnum msg) = 0;
    virtual ~GameListener() = default;
};

#endif