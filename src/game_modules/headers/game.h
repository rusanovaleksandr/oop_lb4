#ifndef GAME_H
#define GAME_H

#include <nlohmann/json.hpp>
#include <iostream>
#include <map>
#include <functional>
#include <utility>
#include "ship_manager.h"
#include "game_board.h"
#include "../../save-load/headers/game_state.h"
#include "game_message_enum.h"
#include "../../io_operations/headers/input_processor.h"
#include <algorithm>
#include "enemy_ai.h"
#include "game_listener.h"

using json = nlohmann::json;

enum InputType
{
    WIDTH,
    HEIGHT
};

class Game
{
    GameBoard user_board;
    GameBoard enemy_board;
    ShipManager user_ship_manager;
    ShipManager enemy_ship_manager;
    AbilityFactory ability_factory;
    AbilityManager ability_manager;
    GameState state;
    EnemyAI enemy_ai;
    InputProcessor input_processor;
    bool trigger_bot_attack = false;
    std::vector<GameListener*> listeners;
    
public:
    Game();

    void startNewGame();

    void placeEnemyShips();

    void enemyTurn();

    AbilityManager &getAbilityManager();
    AbilityFactory &getAbilityFactory();
    GameState &getGameState();

    void userAttack();
    void endGame();
    void applyAbility();
    void checkGameState();

    void saveGame();
    void loadGame();
    void playGame();


    bool isEnemyTurn();
    void addListener(GameListener* listener);

    std::pair<GameBoard&, ShipManager&> getUserObject();
    std::pair<GameBoard&, ShipManager&> getEnemyObject();

    
    ShipManager &getUserShipManager()
    {
        return user_ship_manager;
    }

    ShipManager &getEnemyShipManager()
    {
        return user_ship_manager;
    }

    GameBoard &getEnemyBoard()
    {
        return enemy_board;
    }

    GameBoard &getUserBoard()
    {
        return user_board;
    }

private:
    void inputBoardDimensions(int &board_width, int &board_height);
    void initializeBoardsAndAI(int board_width, int board_height);
    void initializeShipManagers();
    void placeUserShips();
    void checkUserWin();
    void checkEnemyWin();
    void handleUserDecisionForNewGame();
    void handleUserDecisionForNewRound();

    void notifyStartMessage(GameMessageEnum msg);
    void notifyGameMessage(GameMessageEnum msg);
    void notifyGameStateMessage(GameMessageEnum msg);
};

#endif