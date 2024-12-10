#include "render_engine.h"

template<typename GameBoardRenderer, typename MessageRenderer>
void RenderEngine<GameBoardRenderer, MessageRenderer>::render(const std::string &command)
{
    if (command == "boards") {
        game_board_renderer.drawGameBoard(game);
    } else if (command == "attack_message") {
        message_renderer.attackMessage(game);
    } else if (command == "my_ships") {
        game_board_renderer.showShips(game, 0);
    } else if (command == "enemy_ships") {
        game_board_renderer.showShips(game, 1);
    } else if (command == "view_enemy") {
        game_board_renderer.showCompleteGameBoard(game, 1);
    } else if (command == "view_my") {
        game_board_renderer.showCompleteGameBoard(game, 0);
    } else if (command == "apply_ability") {
        message_renderer.applyAbility(game);
    } else if (command == "next_ability") {
        message_renderer.nextAbility(game);
    } else if (command == "help") {
        message_renderer.help();
    } 
}

template<typename GameBoardRenderer, typename MessageRenderer>
void RenderEngine<GameBoardRenderer, MessageRenderer>::update(const std::string &command)
{
    render(command);
}