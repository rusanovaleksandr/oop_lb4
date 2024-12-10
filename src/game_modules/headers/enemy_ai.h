#ifndef ENEMY_H
#define ENEMY_H

#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "game_board.h"
#include "ship_manager.h"
#include "coords.h"
#include <vector>

class EnemyAI
{
    GameBoard& enemy_board;
    GameBoard& user_board;
    ShipManager& ship_manager;

public:
    EnemyAI(GameBoard& enemy_board, GameBoard& user_board, ShipManager& ship_manager);
    EnemyAI(const EnemyAI& other);
    EnemyAI& operator=(const EnemyAI& other);
    ~EnemyAI();


    void placeShips();
    void attack();
    void reset(GameBoard& enemy_board, GameBoard& user_board, ShipManager& ship_manager);
};


#endif

