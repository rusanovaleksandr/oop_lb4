#include "../headers/game_board_renderer.h"

void GameBoardRenderer::drawGameBoard(Game& game)
{
    GameBoardDrawer drawer;
    auto user_data = game.getUserObject();
    auto enemy_data = game.getEnemyObject();

    drawer.showPlayerView(user_data.first, 0);
    drawer.showPlayerView(enemy_data.first, 1);
}

void GameBoardRenderer::showCompleteGameBoard(Game& game, bool mode)
{
    GameBoardDrawer drawer;
    auto user_data = game.getUserObject();
    auto enemy_data = game.getEnemyObject();
    if(mode == 0)
    {
        drawer.showCompleteBoard(user_data.first, 0);
    }
    else
    {
        drawer.showCompleteBoard(enemy_data.first, 1);
    }
}

void GameBoardRenderer::showShips(Game& game, bool mode)
{
    GameBoardDrawer drawer;
    auto user_data = game.getUserObject();
    auto enemy_data = game.getEnemyObject();
    if(mode == 0)
    {
        drawer.showShips(user_data.second);
    }
    else
    {
        drawer.showShips(enemy_data.second);
    }
}