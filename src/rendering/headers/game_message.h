#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include <iostream>
#include <map>
#include <functional>
#include <utility> 

#include "../../game_modules/headers/game_message_enum.h"
#include "../../game_modules/headers/ship_manager.h"
#include "../../game_modules/headers/game_board.h"


class GameMessage
{
public:
    std::string messageNextAbility(std::string ability);
    std::string messageInformAbilityApply(std::string ability_name);
    std::string helpMessage();
    std::string startMessage(GameMessageEnum msg);
    std::string gameMessage(GameMessageEnum msg);
    std::string gameStateMessage(GameMessageEnum msg);
    std::string messageUserAttack(GameBoard& board);
    std::string messageEnemyAttack(GameBoard& board);
};


#endif