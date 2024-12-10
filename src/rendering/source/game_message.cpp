#include "../headers/game_message.h"

std::string GameMessage::messageEnemyAttack(GameBoard &board)
{
    if (board.getLastAttemptEnemy() == 0)
    {
        return "Bot missed!";
    }
    else
    {
        return "Bot hit!";
    }
}

std::string GameMessage::messageUserAttack(GameBoard &board)
{
    if (board.getLastAttemptUser() == 0)
    {
        return "You missed!";
    }
    else
    {
        return "You hit!";
    }
}

std::string GameMessage::startMessage(GameMessageEnum msg)
{
    switch (msg)
    {
    case INPUT_WIDTH:
        return "Enter board width: ";
    case INPUT_HEIGHT:
        return "Enter board heigth: ";
    case INVALID_INPUT:
        return "Invalid input. Height and width must be positive integers";
    case INPUT_COORDINATE:
        return "Enter ship coordinates and its orientation(v - vertical, h - horizontal): ";
    case INVALID_COORDINATE:
        return "Invalid input for ship info. \nHint: x coordinate must be in range [1, width], y coordinate must be in range [1, height], orientation must be v - vertical, h - horizontal";
    case RE_ENTER_COORDINATE:
        return "Please re-enter ship info";
    default:
        return "";
    }
}

std::string GameMessage::helpMessage()
{
    std::string help_message = R"(
**Default controlls**

Key | Action
----|-------
a   | attack
ms  | my_ships
es  | enemy_ships
q   | end_game
ve  | view_enemy
vm  | view_my
f   | boards
n   | next_ability
s   | save_game
l   | load_game
u   | apply_ability
h   | help
)";
    return help_message;
}

std::string GameMessage::gameStateMessage(GameMessageEnum msg)
{
    switch (msg)
    {
    case GameMessageEnum::LOSER:
        return "You lost!";
    case GameMessageEnum::QUES_START_NEW_GAME:
        return "Do you want to start a new game? (y/n) ";
    case GameMessageEnum::START_NEW_GAME:
        return "Starting a new game.";
    case GameMessageEnum::WINNER:
        return "You won this round!";
    case GameMessageEnum::QUES_START_NEW_ROUND:
        return "Do you want to start a new round? (y/n)";
    case GameMessageEnum::START_NEW_ROUND:
        return "Starting the next round.";
    case GameMessageEnum::SAVE:
        return "Game saved";
    case GameMessageEnum::LOAD:
        return "Game loaded";
    case GameMessageEnum::EXIT:
        return "Extitng the game. Have a nice day!";
    default:
        return "";
    }
}

std::string GameMessage::messageNextAbility(std::string ability)
{
    if (ability != "No abilities available")
    {
        return "Next ability is: " + ability;
    }
    else
    {
        return "No abilities available";
    }
}

std::string GameMessage::gameMessage(GameMessageEnum msg)
{
    switch (msg)
    {
    case GameMessageEnum::ATTACK_COORDINATE:
        return "Enter attack coordinate (x y): ";
    case GameMessageEnum::OPTION_LOAD_GAME:
        return "Do you want to load game? (y/n)";
    case GameMessageEnum::ATTACK_COORDINATE_OUT_OF_RANGE:
        return "Attack coordinates are out of range. Please enter valid coordinates.";
    case GameMessageEnum::INVALID_COORDINATE_FOR_ATTACK:
        return "Invalid input. Please enter valid integers for coordinates.";
    case GameMessageEnum::INVALID_COORDINATE_FOR_SCANNER:
        return "Invalid input. Please enter valid integers for coordinates.";
    case GameMessageEnum::SCANNER_COORDINATE:
        return "Enter coordinates for scanner (x y): ";
    case GameMessageEnum::SCANNER_COORDINATE_OUT_OF_RANGE:
        return "Scanner coordinates are out of range. Please enter valid coordinates.";
    case GameMessageEnum::SCANNER_FOUND_SHIP:
        return "Scanner found ship in the area!";
    case GameMessageEnum::NO_SHIP_FOUND:
        return "No ship detected";
    default:
        return "";
    }
}

std::string GameMessage::messageInformAbilityApply(std::string ability_name)
{
    if (ability_name == "DoubleDamage")
    {
        return "Using Double Damage...\nDouble Damage ability activated. Next hit will take x2 damage";
    }
    else if (ability_name == "Bombardment")
    {
        return "Using Bombardment...\nBombardment completed!";
    }
    else if (ability_name == "Scanner")
    {
        return "";
    }
    else
    {
        return "No abilities available";
    }
}