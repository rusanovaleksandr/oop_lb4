#include "../headers/game_state.h"

GameState::GameState(const std::string &name) : filename(name) {}

bool GameState::isFileWritten() const
{
    std::ifstream file(filename);
    return file.peek() != std::ifstream::traits_type::eof();
}

void GameState::save(GameBoard &user_board, GameBoard &enemy_board,
                     ShipManager &user_ship_manager, ShipManager &enemy_ship_manager,
                      AbilityManager &ability_manager)
{
    json jsn;

    jsn["user_board"] = user_board.toJson();
    jsn["enemy_board"] = enemy_board.toJson();
    jsn["user_ship_manager"] = user_ship_manager.toJson();
    jsn["enemy_ship_manager"] = enemy_ship_manager.toJson();
    jsn["ability_manager"] = ability_manager.toJson();

    FileManager file_manager(filename);
    
    file_manager.write(jsn);
}

void GameState::load(GameBoard &user_board, GameBoard &enemy_board,
                     ShipManager &user_ship_manager, ShipManager &enemy_ship_manager,
                     AbilityFactory &ability_factory, AbilityManager &ability_manager, EnemyAI& enemy_ai)
{
    FileManager file_manager(filename);
    json jsn;

    file_manager.read(jsn);

    user_board.fromJson(jsn["user_board"]);
    enemy_board.fromJson(jsn["enemy_board"]);

    user_ship_manager.fromJson(jsn["user_ship_manager"]);
    enemy_ship_manager.fromJson(jsn["enemy_ship_manager"]);

    ability_manager.fromJson(jsn["ability_manager"]);
    ability_manager.setAbilityFactory(ability_factory);

    enemy_board.setObserver(&ability_manager);
    enemy_board.updatePointers(enemy_ship_manager);
    user_board.updatePointers(user_ship_manager);

    enemy_ai.reset(enemy_board, user_board, enemy_ship_manager);
}

void GameState::writeState()
{
    FileManager file_manager(filename);
    file_manager.write(saved_data);
}

std::istream& operator>>(std::istream& is, GameState& game_state)
{
    json jsn;

    is >> jsn;
    game_state.saved_data = jsn;

    if (jsn.is_null())
    {
        throw std::runtime_error("Failed to read valid JSON data.");
    }

    game_state.writeState();
    return is;
}

std::ostream &operator<<(std::ostream &os, const GameState &game_state)
{
        FileManager file_manager(game_state.filename);
        json jsn;

        file_manager.read(jsn);

        os << jsn.dump(4) << std::endl;

        return os;
}