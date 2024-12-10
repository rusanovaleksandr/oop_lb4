#ifndef MESSAGE_RENDERER_H
#define MESSAGE_RENDERER_H
#include <iostream>
#include <utility>
#include "../../game_modules/headers/game.h"
#include "console_printer.h"

class MessageRenderer : public GameListener
{
public:
    void attackMessage(Game &game);
    void applyAbility(Game &game);
    void nextAbility(Game &game);
    void help();

    void onStartMessage(GameMessageEnum msg) override;
    void onGameStateMessage(GameMessageEnum msg) override;
    void onGameMessage(GameMessageEnum msg) override;
};

#endif
