#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../../game_modules/headers/game_board.h"
#include "../../game_modules/headers/ship_manager.h"
#include "../../game_modules/headers/enemy_ai.h"
#include "../../game_modules/headers/ship.h"
#include "../../abilities/headers/ability_manager.h"

#include "file_manager.h"

using json = nlohmann::json;

class GameState
{
    std::string filename;
    json saved_data;

public:
    GameState(const std::string &name);

    void save(GameBoard &user_board, GameBoard &enemy_board,
              ShipManager &user_ship_manager, ShipManager &enemy_ship_manager, 
              AbilityManager &ability_manager);

    void load(GameBoard &user_board, GameBoard &enemy_board,
              ShipManager &user_ship_manager, ShipManager &enemy_ship_manager,
              AbilityFactory &ability_factory, AbilityManager &ability_manager, EnemyAI& enemy_ai);

    bool isFileWritten() const;

    void writeState();

    friend std::ostream &operator<<(std::ostream &os, const GameState &game_state);

    friend std::istream &operator>>(std::istream &is, GameState &game_state);

};

#endif