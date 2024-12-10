#include "controller.h"

template <typename InputMethod, typename GameBoardRenderer, typename MessageRenderer>
void Controller<InputMethod, GameBoardRenderer, MessageRenderer>::initializeCommands()
{
    commands["attack"] = [&]()
    {
        game.userAttack();
        render_tracker.update("new_game");
    };
    commands["my_ships"] = [&]()
    { render_tracker.update("my_ships"); };
    commands["enemy_ships"] = [&]()
    { render_tracker.update("enemy_ships"); };
    commands["end_game"] = [&]()
    { game.endGame(); };
    commands["boards"] = [&]()
    { render_tracker.update("boards"); };
    commands["view_enemy"] = [&]()
    { render_tracker.update("view_enemy"); };
    commands["view_my"] = [&]()
    { render_tracker.update("view_my"); };
    commands["next_ability"] = [&]()
    { render_tracker.update("next_ability"); };
    commands["save_game"] = [&]()
    { game.saveGame(); };
    commands["load_game"] = [&]()
    { game.loadGame(); };
    commands["apply_ability"] = [&]()
    {
        game.applyAbility();
        render_tracker.update("apply_ability");
    };
    commands["help"] = [&]()
    { render_tracker.update("help"); };
}

template <typename InputMethod, typename GameBoardRenderer, typename MessageRenderer>
void Controller<InputMethod, GameBoardRenderer, MessageRenderer>::run()
{
    game.playGame();
    bool isGameRunning = true;

    while (isGameRunning)
    {
        std::string input = input_method.getInput();
        if (commands.find(input) != commands.end())
        {
            commands[input]();
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
        if (!game.isEnemyTurn())
        {
            continue;
        }
        game.enemyTurn();
        game.checkGameState();
        render_tracker.update("attack_message");
        render_tracker.update("boards");
    }
}
