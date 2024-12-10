#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H
#include <iostream>
#include <utility>
#include "../../game_modules/headers/game.h"
#include "game_board_drawer.h"

class GameBoardRenderer
{
public:
    void drawGameBoard(Game &game);
    void showShips(Game &game, bool mode);
    void showCompleteGameBoard(Game &game, bool mode);
};

#endif