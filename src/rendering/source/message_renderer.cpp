#include "../headers/message_renderer.h"

void MessageRenderer::nextAbility(Game &game)
{
    GameMessage message;
    ConsolePrinter printer;
    AbilityManager& ability_manager = game.getAbilityManager();
    std::string ability_name = ability_manager.peekNextAbility();
    printer.print(message.messageNextAbility(ability_name));
}

void MessageRenderer::applyAbility(Game& game)
{
    GameMessage message;
    ConsolePrinter printer;
    printer.print(message.messageInformAbilityApply(game.getAbilityManager().lastAbilityApplied()));
}

void MessageRenderer::help()
{
    GameMessage message;
    ConsolePrinter printer;
    printer.print(message.helpMessage());
}

void MessageRenderer::attackMessage(Game& game)
{
    GameMessage message;
    ConsolePrinter printer;
    auto user_data = game.getUserObject();
    auto enemy_data = game.getEnemyObject();

    printer.print(message.messageUserAttack(enemy_data.first));
    printer.print(message.messageEnemyAttack(user_data.first));
}

void MessageRenderer::onStartMessage(GameMessageEnum msg)
{
    GameMessage message;
    ConsolePrinter printer;
    printer.print(message.startMessage(msg));
}


void MessageRenderer::onGameStateMessage(GameMessageEnum msg)
{
    GameMessage message;
    ConsolePrinter printer;
    printer.print(message.gameStateMessage(msg));
}



void MessageRenderer::onGameMessage(GameMessageEnum msg)
{
    GameMessage message;
    ConsolePrinter printer;
    printer.print(message.gameMessage(msg));
}
