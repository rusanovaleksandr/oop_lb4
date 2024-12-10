#include "../headers/scanner_factory.h"

ScannerFactory::ScannerFactory(GameBoard &board, std::shared_ptr<InputProcessor> input_processor, std::shared_ptr<GameMessage> ship_detected) : board(board), input_processor(input_processor), game_message(ship_detected) {}

std::shared_ptr<IAbility> ScannerFactory::create()
{
    int x = -1;
    int y = -1;

    ConsolePrinter printer;

    printer.print(game_message->gameMessage(SCANNER_COORDINATE));
    std::string input_line = input_processor->input();
    std::stringstream ss(input_line);
    bool valid_input = false;

    while (!valid_input)
    {
        ss >> x >> y;
        if (ss.fail() || ss.bad() || ss.peek() != EOF)
        {
            printer.print(game_message->gameMessage(INVALID_COORDINATE_FOR_SCANNER));
            continue;
        }
        else
        {
            valid_input = true;
        }
    }

    Coords coordinate(x, y);

    if (!board.validateCoordinatesInBounds(coordinate))
    {
        while (!board.validateCoordinatesInBounds(coordinate))
        {
            printer.print(game_message->gameMessage(SCANNER_COORDINATE_OUT_OF_RANGE));
            ss >> x >> y;
            coordinate = Coords(x, y);
        }
    }

    return std::make_shared<ScannerAbility>(coordinate, board, game_message);
}

std::string ScannerFactory::getName() const
{
    return "Scanner";
}

json ScannerFactory::toJson()
{
    json json_object;
    json_object["type"] = "ScannerFactory";
    json_object["name"] = getName();
    return json_object;
}

void ScannerFactory::fromJson(const json &jsn) {};