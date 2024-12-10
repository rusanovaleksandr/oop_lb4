#include "../headers/game.h"
#define GAME_DATA_FILE "game_data.json"
#define DEFAULT_SHIPS ONE

Game::Game() : user_board(), enemy_board(),
               user_ship_manager({DEFAULT_SHIPS}), enemy_ship_manager({DEFAULT_SHIPS}),
               ability_factory(enemy_board, enemy_ship_manager),
               ability_manager(ability_factory),
               state(GAME_DATA_FILE), enemy_ai(enemy_board, user_board, enemy_ship_manager) {}

void Game::startNewGame()
{
    int board_width;
    int board_height;

    inputBoardDimensions(board_width, board_height);

    initializeBoardsAndAI(board_width, board_height);

    initializeShipManagers();
    placeUserShips();

    placeEnemyShips();
}

void Game::inputBoardDimensions(int &board_width, int &board_height)
{
    InputType currentInputType = WIDTH;
    bool valid_input = false;

    while (!valid_input)
    {
        try
        {
            if (currentInputType == WIDTH)
            {
                notifyStartMessage(INPUT_WIDTH);
            }
            else
            {
                notifyStartMessage(INPUT_HEIGHT);
            }

            std::string input = input_processor.input();
            std::stringstream ss(input);

            int value;

            if (ss >> value && value > 0)
            {
                if (currentInputType == WIDTH)
                {
                    board_width = value;
                    currentInputType = HEIGHT;
                }
                else
                {
                    board_height = value;
                    valid_input = true;
                }
            }
            else
            {
                notifyStartMessage(INVALID_INPUT);
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << e.what() << std::endl;
            board_width = 0;
            board_height = 0;
            currentInputType = WIDTH;
        }
    }
}

void Game::placeUserShips()
{
    for (int i = 0; i < user_ship_manager.getCountShips(); i++)
    {
        Ship &ship = user_ship_manager.getShipAtIndex(i);
        int x, y;
        char orientation_char;
        bool valid_input = false;

        while (!valid_input)
        {
            notifyStartMessage(INPUT_COORDINATE);

            std::string input_line = input_processor.input();
            std::stringstream ss(input_line);
            ss >> x >> y;

            if (ss.fail() || ss.bad() || x < 0 || y < 0)
            {
                notifyStartMessage(INVALID_COORDINATE);
                continue;
            }

            if (ss.peek() != EOF)
            {
                ss >> orientation_char;
            }

            try
            {
                ship.setOrientation(orientation_char);
                user_board.addShip(&ship, {x, y});
                valid_input = true;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                notifyStartMessage(RE_ENTER_COORDINATE);
            }
        }
    }
}

void Game::placeEnemyShips()
{
    enemy_ai.placeShips();
}

void Game::initializeBoardsAndAI(int board_width, int board_height)
{
    user_board = GameBoard(board_width, board_height);
    enemy_board = GameBoard(board_width, board_height);
    enemy_board.setObserver(&ability_manager);
    enemy_board.setBotAttacked(true);

    enemy_ai = EnemyAI(enemy_board, user_board, enemy_ship_manager);
}

void Game::initializeShipManagers()
{
    switch (user_board.determineBoardSize())
    {
    case LARGE:
        user_ship_manager = ShipManager({FOUR, THREE, THREE, TWO, TWO, TWO, ONE, ONE, ONE, ONE});
        enemy_ship_manager = ShipManager({FOUR, THREE, THREE, TWO, TWO, TWO, ONE, ONE, ONE, ONE});
        break;
    case MEDIUM:
        user_ship_manager = ShipManager({FOUR, THREE, TWO, ONE, ONE, ONE});
        enemy_ship_manager = ShipManager({FOUR, THREE, TWO, ONE, ONE, ONE});
        break;
    case SMALL:
        user_ship_manager = ShipManager({TWO, TWO, ONE, ONE});
        enemy_ship_manager = ShipManager({TWO, TWO, ONE, ONE});
        break;
    }
}

void Game::playGame()
{
    if (state.isFileWritten())
    {
        notifyGameMessage(OPTION_LOAD_GAME);
        std::string option = input_processor.input();
        if (option == "yes" || option == "Y" || option == "y")
        {
            try
            {
                loadGame();
            }
            catch (const SaveFileDamagedException &e)
            {
                std::cerr << e.what() << '\n';
                notifyGameStateMessage(QUES_START_NEW_GAME);
                handleUserDecisionForNewGame();
            }
        }
        else
        {
            startNewGame();
        }
    }
    else
    {
        startNewGame();
    }
}

void Game::checkGameState()
{
    if (user_ship_manager.allShipsDestroyed())
    {
        checkEnemyWin();
    }
    else if (enemy_ship_manager.allShipsDestroyed())
    {
        checkUserWin();
    }
}

void Game::checkEnemyWin()
{
    notifyGameStateMessage(LOSER);
    notifyGameStateMessage(QUES_START_NEW_GAME);
    handleUserDecisionForNewGame();
}

void Game::checkUserWin()
{
    notifyGameStateMessage(WINNER);
    notifyGameStateMessage(QUES_START_NEW_ROUND);
    handleUserDecisionForNewRound();
}

void Game::handleUserDecisionForNewGame()
{
    std::string option = input_processor.input();

    if (option == "yes" || option == "Y" || option == "y")
    {
        notifyGameStateMessage(START_NEW_GAME);

        startNewGame();
    }
    else
    {
        endGame();
    }
}

void Game::handleUserDecisionForNewRound()
{
    std::string option = input_processor.input();

    if (option == "yes" || option == "Y" || option == "y")
    {
        notifyGameStateMessage(START_NEW_ROUND);
        enemy_ship_manager.restoreShips();
        enemy_board.resetBoard();
        enemy_ai = EnemyAI(enemy_board, user_board, enemy_ship_manager);
        placeEnemyShips();
    }
    else
    {
        endGame();
    }
}

void Game::userAttack()
{
    trigger_bot_attack = true;
    int x = -1;
    int y = -1;
    bool valid_input = false;

    while (!valid_input)
    {
        notifyGameMessage(ATTACK_COORDINATE);
        std::string input_line = input_processor.input();

        std::stringstream ss(input_line);

        ss >> x >> y;
        if (ss.fail() || ss.bad() || ss.peek() != EOF)
        {
            notifyGameMessage(INVALID_COORDINATE_FOR_ATTACK);
            continue;
        }

        try
        {
            bool result = enemy_board.shoot({x, y});
            valid_input = true;
        }
        catch (const OutOfBoundsException &)
        {
            notifyGameMessage(ATTACK_COORDINATE_OUT_OF_RANGE);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void Game::applyAbility()
{
    try
    {
        ability_manager.applyAbility();
    }
    catch (const std::exception &e)
    {
    }
}

void Game::endGame()
{
    notifyGameStateMessage(EXIT);
    exit(0);
}

AbilityManager &Game::getAbilityManager()
{
    return ability_manager;
}

void Game::saveGame()
{
    state.save(user_board, enemy_board, user_ship_manager, enemy_ship_manager, ability_manager);
    notifyGameStateMessage(SAVE);
}

void Game::loadGame()
{
    state.load(user_board, enemy_board, user_ship_manager, enemy_ship_manager, ability_factory, ability_manager, enemy_ai);
    notifyGameStateMessage(LOAD);
}

void Game::enemyTurn()
{
    trigger_bot_attack = false;

    enemy_ai.attack();

    checkGameState();
}

AbilityFactory &Game::getAbilityFactory()
{
    return ability_factory;
}

GameState &Game::getGameState()
{
    return state;
}

std::pair<GameBoard &, ShipManager &> Game::getUserObject()
{
    return std::make_pair(std::ref(user_board), std::ref(user_ship_manager));
}

std::pair<GameBoard &, ShipManager &> Game::getEnemyObject()
{
    return std::make_pair(std::ref(enemy_board), std::ref(enemy_ship_manager));
}

bool Game::isEnemyTurn()
{
    return trigger_bot_attack;
}

void Game::addListener(GameListener *listener)
{
    listeners.push_back(listener);
}

void Game::notifyStartMessage(GameMessageEnum msg)
{
    for (auto listener : listeners)
    {
        listener->onStartMessage(msg);
    }
}

void Game::notifyGameMessage(GameMessageEnum msg)
{
    for (auto listener : listeners)
    {
        listener->onGameMessage(msg);
    }
}

void Game::notifyGameStateMessage(GameMessageEnum msg)
{
    for (auto listener : listeners)
    {
        listener->onGameStateMessage(msg);
    }
}
