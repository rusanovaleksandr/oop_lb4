#include "../headers/scanner_ability.h"

ScannerAbility::ScannerAbility(Coords coordinate, GameBoard& board, std::shared_ptr<GameMessage> game_message) : x_(coordinate.getX()), y_(coordinate.getY()), board(board){ result_reveal = game_message;}

void ScannerAbility::apply()
{
    bool ship_detected = false;

    for (int y = this->y_ - 1; y <= this->y_ + 1; y++)
    {
        for (int x = this->x_ - 1; x <= this->x_ + 1; x++)
        {
            if (board.validateCoordinatesInBounds({x, y}))
            {
                if(board.getCells()[y - 1][x - 1] == SHIP)
                {
                    ship_detected = true;
                    break;
                }
            }
        }
        if (ship_detected)
        {
            break;
        }
    }

    if (result_reveal)
    {
        ConsolePrinter printer;
        if(ship_detected)
        {
            printer.print(result_reveal->gameMessage(SCANNER_FOUND_SHIP));
        }
        else
        {
            printer.print(result_reveal->gameMessage(NO_SHIP_FOUND));
        }
    }
}

