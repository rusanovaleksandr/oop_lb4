#include "../headers/enemy_ai.h"

EnemyAI::EnemyAI(GameBoard &enemy_board, GameBoard &user_board, ShipManager &ship_manager)
    : enemy_board(enemy_board), user_board(user_board), ship_manager(ship_manager) {}

EnemyAI::EnemyAI(const EnemyAI &other)
    : enemy_board(other.enemy_board), user_board(other.user_board), ship_manager(other.ship_manager) {}

EnemyAI &EnemyAI::operator=(const EnemyAI &other)
{
    if (this == &other)
    {
        return *this;
    }

    enemy_board = other.enemy_board;
    user_board = other.user_board;
    ship_manager = other.ship_manager;

    return *this;
}

EnemyAI::~EnemyAI() {}

void EnemyAI::placeShips()
{
    srand(static_cast<unsigned int>(time(NULL)));

    int width = enemy_board.getWidth();
    int height = enemy_board.getHeight();

    for (int i = 0; i < ship_manager.getCountShips(); i++)
    {
        Ship &ship = ship_manager.getShipAtIndex(i);
        bool is_placed = false;
        
        while (!is_placed)
        {
            try
            {
                int x = (rand() % width) + 1;
                int y = (rand() % height) + 1;
                ShipOrientation orientation = (rand() % 2 == 0) ? HORIZONTAL : VERTICAL;
                enemy_board.addShip(&ship, {x, y});
                is_placed = true;
            }
            catch(const ShipPlacementException& e)
            {
                
            }
        }
    }
}

void EnemyAI::attack()
{
    int x, y;
    bool valid_attack = false;

    while (!valid_attack)
    {
        x = (rand() % user_board.getWidth()) + 1;
        y = (rand() % user_board.getHeight()) + 1;

        try
        {
            user_board.shoot({x, y});
            valid_attack = true;
        }
        catch(const std::exception& e)
        {
            continue;
        }
    }
}

void EnemyAI::reset(GameBoard& enemy_board, GameBoard& user_board, ShipManager& ship_manager)
{
    this->enemy_board = enemy_board;
    this->user_board = user_board;
    this->ship_manager = ship_manager;
}
