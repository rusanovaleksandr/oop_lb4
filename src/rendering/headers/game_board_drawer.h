#ifndef BOARD_DRAWER_H
#define BOARD_DRAWER_H

#include <iostream>
#include <utility>
#include "../../game_modules/headers/ship_manager.h"
#include "../../game_modules/headers/game_board.h"

class GameBoardDrawer
{
public:
    void showPlayerView(GameBoard& game_board, bool mode);
    void showCompleteBoard(GameBoard& game_board, bool mode);
    void showShips(ShipManager& ship_manager);
};

#endif