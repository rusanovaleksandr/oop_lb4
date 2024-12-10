#include "../headers/game_board_drawer.h"

void GameBoardDrawer::showCompleteBoard(GameBoard &game_board, bool mode)
{
    std::cout << std::endl;
    if (mode == 0)
    {
        std::cout << "All ships on user board: " << std::endl;

    }
    else
    {
        std::cout << "All ships on enemy board: " << std::endl;
    }


    CellState state = UNKNOWN;
    int width = game_board.getWidth();
    int height = game_board.getHeight();
    std::vector<std::vector<CellState>> board = game_board.getCells();
    std::set<Coords> attacked_cells = game_board.getAttackedCoords();

    std::cout << " ";
    for (int k = 1; k <= width; ++k)
    {
        std::cout << " " << k;
    }
    std::cout << "\n";

    for (int i = 0; i < height; ++i)
    {
        std::cout << i + 1 << " ";
        for (int j = 0; j < width; ++j)
        {
            state = board[i][j];

            if (state != SHIP)
            {
                std::cout << "~";
            }
            else
            {
                switch (game_board.getSegmentShipState({j + 1, i + 1}))
                {
                case INTACT:
                    std::cout << "▢";
                    break;
                case DAMAGED:
                    std::cout << "▣";
                    break;
                case DESTROYED:
                    std::cout << "☒";
                    break;
                default:
                    break;
                }
            }
            std::cout << " ";

        }

    std::cout << "\n";
    
    }
}

void GameBoardDrawer::showShips(ShipManager &ship_manager)
{
    std::cout << std::endl;
    std::cout << "Current states of the ships: " << std::endl;
    for (int j = 0; j < ship_manager.getCountShips(); j++)
    {
        Ship ship = ship_manager.getShipAtIndex(j);
        std::cout << "Ship at index: " << j << std::endl;
        if (ship.getOrientation() == VERTICAL)
        {
            for (int i = 0; i < ship.getLength(); i++)
            {
                switch (ship.getSegmentAtIndex(i))
                {
                case INTACT:
                    std::cout << "▢" << "\n";
                    break;
                case DAMAGED:
                    std::cout << "▣" << "\n";
                    break;
                case DESTROYED:
                    std::cout << "☒" << "\n";
                    break;
                default:
                    break;
                }
            }
            std::cout << "\n";
        }
        else if (ship.getOrientation() == HORIZONTAL)
        {
            for (int i = 0; i < ship.getLength(); i++)
            {
                switch (ship.getSegmentAtIndex(i))
                {
                case INTACT:
                    std::cout << "▢ ";
                    break;
                case DAMAGED:
                    std::cout << "▣ ";
                    break;
                case DESTROYED:
                    std::cout << "☒ ";
                    break;
                default:
                    break;
                }
            }
            std::cout << "\n";
        }
    }
}

void GameBoardDrawer::showPlayerView(GameBoard &game_board, bool mode)
{
    std::cout << std::endl;
    if (mode == 0)
    {
        std::cout << "User board" << std::endl;
    }
    else
    {
        std::cout << "Enemy board" << std::endl;
    }

    CellState state = UNKNOWN;
    int width = game_board.getWidth();
    int height = game_board.getHeight();
    std::vector<std::vector<CellState>> board = game_board.getCells();
    std::set<Coords> attacked_cells = game_board.getAttackedCoords();

    std::cout << " ";
    for (int k = 1; k <= width; ++k)
    {
        std::cout << " " << k;
    }
    std::cout << "\n";

    for (int i = 0; i < height; ++i)
    {
        std::cout << i + 1 << " ";
        for (int j = 0; j < width; ++j)
        {
            state = board[i][j];
            if (attacked_cells.find({j + 1, i + 1}) != attacked_cells.end())
            {
                if (state != SHIP)
                {
                    std::cout << "~";
                }
                else
                {
                    switch (game_board.getSegmentShipState({j + 1, i + 1}))
                    {
                    case INTACT:
                        std::cout << "▢";
                        break;
                    case DAMAGED:
                        std::cout << "▣";
                        break;
                    case DESTROYED:
                        std::cout << "☒";
                        break;
                    default:
                        break;
                    }
                }
            }
            else
            {
                std::cout << "·";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}
