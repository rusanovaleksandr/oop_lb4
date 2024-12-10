#include "../headers/game_board.h"
#define FREE_NEIGHBOR_CELLS 9

GameBoard::GameBoard() : GameBoard(10, 10, nullptr) {}

GameBoard::GameBoard(Observer *observer) : GameBoard(10, 10, observer) {}

GameBoard::GameBoard(int x, int y, Observer *observer) : width_(x), height_(y), observer(observer)
{
    if (x <= 0 || y <= 0)
    {
        throw std::invalid_argument("Error: size component must be greater than 0");
    }
    else if (x < 5 && y < 5)
    {
        throw std::invalid_argument("Error: board is too small");
    }

    cells_.resize(height_, std::vector<CellState>(width_, CellState::EMPTY));
}

GameBoard::GameBoard(int x, int y) : GameBoard(x, y, nullptr) {}

GameBoard::GameBoard(const GameBoard &other)
{
    width_ = other.width_;
    height_ = other.height_;
    cells_ = other.cells_;
    attacked_coords_ = other.attacked_coords_;
    ships_coords_ = other.ships_coords_;
    observer = other.observer;
}

GameBoard::GameBoard(GameBoard &&other)
{
    width_ = other.width_;
    height_ = other.height_;
    cells_ = std::move(other.cells_);
    attacked_coords_ = std::move(other.attacked_coords_);
    ships_coords_ = std::move(other.ships_coords_);
    observer = other.observer;
}

GameBoard &GameBoard::operator=(const GameBoard &other)
{
    if (this != &other)
    {
        width_ = other.width_;
        height_ = other.height_;
        cells_ = other.cells_;
        attacked_coords_ = other.attacked_coords_;
        ships_coords_ = other.ships_coords_;
        observer = other.observer;
    }
    return *this;
}

GameBoard &GameBoard::operator=(GameBoard &&other)
{
    if (this != &other)
    {
        width_ = other.width_;
        height_ = other.height_;
        cells_ = std::move(other.cells_);
        attacked_coords_ = std::move(other.attacked_coords_);
        ships_coords_ = std::move(other.ships_coords_);
        observer = other.observer;
    }
    return *this;
}

void GameBoard::addShipOnBoard(Ship *ship)
{
    for (Coords coordinate : ships_coords_[ship])
    {
        cells_[coordinate.getY() - 1][coordinate.getX() - 1] = SHIP;
    }
}

const ShipSegmentState GameBoard::getSegmentShipState(const Coords &coords)
{
    Ship *found_ship = findShipByCoords(coords);
    if (found_ship != nullptr)
    {
        const std::vector<Coords> &ship_coords = ships_coords_.at(found_ship);
        for (size_t i = 0; i < ship_coords.size(); ++i)
        {
            if (ship_coords[i].getX() == coords.getX() && ship_coords[i].getY() == coords.getY())
            {
                return found_ship->getSegmentAtIndex(i);
            }
        }
    }
    return INTACT;
}

bool GameBoard::validateCoordinatesInBounds(Coords coords)
{
    if (coords.getX() < 1 || coords.getY() < 1 || coords.getX() > width_ || coords.getY() > height_)
    {
        return false;
    }
    return true;
}

bool GameBoard::checkCoordinatesForShipPlacement(Coords coords)
{
    if (!validateCoordinatesInBounds(coords))
    {
        return false;
    }
    int count = 0;
    for (int y = coords.getY() - 1; y <= coords.getY() + 1; y++)
    {
        for (int x = coords.getX() - 1; x <= coords.getX() + 1; x++)
        {
            if (x < 1 || y < 1 || x > width_ || y > height_)
            {
                count++;
            }
            else if (cells_[y - 1][x - 1] != SHIP)
            {
                count++;
            }
        }
    }

    return count == FREE_NEIGHBOR_CELLS;
}

bool GameBoard::addShip(Ship *ship, const Coords &coords)
{
    std::vector<Coords> coordinates;
    bool flag = true;
    for (int i = 0; i < ship->getLength(); i++)
    {
        if (ship->getOrientation() == HORIZONTAL)
        {
            if (checkCoordinatesForShipPlacement({coords.getX() + i, coords.getY()}))
            {
                coordinates.push_back({coords.getX() + i, coords.getY()});
            }
            else
            {
                flag = false;
                break;
            }
        }
        else if (ship->getOrientation() == VERTICAL)
        {
            if (checkCoordinatesForShipPlacement({coords.getX(), coords.getY() + i}))
            {
                coordinates.push_back({coords.getX(), coords.getY() + i});
            }
            else
            {
                flag = false;
                break;
            }
        }
    }

    if (flag)
    {
        ships_coords_[ship] = coordinates;
        addShipOnBoard(ship);
    }
    else
    {
        throw ShipPlacementException("Can not place ship here");
    }
    return flag;
}

bool GameBoard::shoot(Coords shoot_coordinate)
{
    if (!validateCoordinatesInBounds(shoot_coordinate))
    {
        throw OutOfBoundsException("Attack out of bounds");
    }
    if(std::find(attacked_coords_.begin(), attacked_coords_.end(), shoot_coordinate) != attacked_coords_.end() && isShipAt(shoot_coordinate) == false)
    {
        throw CellAlreadyAttackedException("Coordinate was already attacked");

    }

    attacked_coords_.insert(shoot_coordinate);

    if (cells_[shoot_coordinate.getY() - 1][shoot_coordinate.getX() - 1] == SHIP)
    {
        Ship *found_ship = findShipByCoords(shoot_coordinate);

        if (found_ship != nullptr)
        {
            const std::vector<Coords> &ship_coords = ships_coords_.at(found_ship);
            for (size_t i = 0; i < ship_coords.size(); ++i)
            {
                if (ship_coords[i].getX() == shoot_coordinate.getX() && ship_coords[i].getY() == shoot_coordinate.getY())
                {
                    if (double_damage_flag)
                    {
                        found_ship->setSegmentAtIndex(i, DESTROYED);
                        setDoubleDamageFlag(false);
                    }
                    else
                    {
                        found_ship->hitSegment(i);
                    }
                    if (found_ship->isDestroyed())
                    {
                        if(observer != nullptr)
                        {
                            observer->accept();
                        }
                        
                        markSurroundingCells(found_ship);
                    }
                    if (bot_attacked)
                    {
                        last_attempt_user = 1;
                    }
                    else
                    {
                        last_attempt_enemy = 1;
                    }
                    return true;
                }
            }
        }
    }
    if (double_damage_flag)
    {
        setDoubleDamageFlag(false);
    }
    if (bot_attacked)
    {
        last_attempt_user = 0;
    }
    else
    {
        last_attempt_enemy = 0;
    }
    return false;
}

Ship *GameBoard::findShipByCoords(const Coords &coords) const
{
    for (const auto &pair : ships_coords_)
    {
        auto it = std::find_if(pair.second.begin(), pair.second.end(), [&coords](const Coords &coordinate)
                               { return coordinate.getX() == coords.getX() && coordinate.getY() == coords.getY(); });

        if (it != pair.second.end())
        {
            return pair.first;
        }
    }
    return nullptr;
}

bool GameBoard::isShipAt(const Coords& coords) const
{
    if(findShipByCoords(coords) != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GameBoard::markSurroundingCells(Ship *ship)
{
    std::vector<Coords> coordinates = ships_coords_[ship];
    for (const auto &coord : coordinates)
    {
        for (int y = coord.getY() - 1; y <= coord.getY() + 1; y++)
        {
            for (int x = coord.getX() - 1; x <= coord.getX() + 1; x++)
            {
                Coords current_coordinate(x, y);
                if (validateCoordinatesInBounds(current_coordinate))
                {
                    attacked_coords_.insert(current_coordinate);
                }
            }
        }
    }
}

const int GameBoard::getWidth() const
{
    return width_;
}

const int GameBoard::getHeight() const
{
    return height_;
}

const std::vector<std::vector<CellState>> &GameBoard::getCells() const
{
    return cells_;
}

const std::set<Coords> &GameBoard::getAttackedCoords() const
{
    return attacked_coords_;
}

void GameBoard::setObserver(Observer *observer)
{
    this->observer = observer;
}

void GameBoard::setDoubleDamageFlag(bool value)
{
    this->double_damage_flag = value;
}

bool GameBoard::getDoubleDamageFlag()
{
    return double_damage_flag;
}

bool GameBoard::getBotAttacked()
{
    return bot_attacked;
}

void GameBoard::setBotAttacked(bool value)
{
    bot_attacked = value;
}

bool GameBoard::getLastAttemptUser()
{
    return last_attempt_user;
}

bool GameBoard::getLastAttemptEnemy()
{
    return last_attempt_enemy;
}

void GameBoard::setLastAttemptUser(bool value)
{
    last_attempt_user = value;
}

void GameBoard::setLastAttemptEnemy(bool value)
{
    last_attempt_enemy = value;
}

BoardSize GameBoard::determineBoardSize()
{
    int area = width_ * height_;

    if (area >= 100)
    {
        return LARGE;
    }
    else if (area >= 75)
    {
        return MEDIUM;
    }
    else
    {
        return SMALL;
    }
}

void GameBoard::resetBoard()
{
    attacked_coords_.clear();
    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            cells_[y][x] = UNKNOWN;
        }
    }
}

json GameBoard::toJson() const
{
    json json_object;

    json_object["height"] = height_;
    json_object["width"] = width_;

    json cells_array = json::array();
    for (const auto &row : cells_)
    {
        json row_array = json::array();
        for (const auto &cell : row)
        {
            row_array.push_back(cell);
        }

        cells_array.push_back(row_array);
    }

    json_object["cells"] = cells_array;

    json attacked_coords_array = json::array();
    for (const auto &coords : attacked_coords_)
    {
        json coords_object;
        coords_object["x"] = coords.getX();
        coords_object["y"] = coords.getY();
        attacked_coords_array.push_back(coords_object);
    }
    json_object["attacked_coords"] = attacked_coords_array;

    json ships_coords_array = json::array();
    for (const auto &shipCoords : ships_coords_)
    {
        json ship_coords_object;
        ship_coords_object["ship"] = shipCoords.first->toJson();
        json coords_array = json::array();
        for (const auto &coords : shipCoords.second)
        {
            json coords_object;
            coords_object["x"] = coords.getX();
            coords_object["y"] = coords.getY();
            coords_array.push_back(coords_object);
        }
        ship_coords_object["coords"] = coords_array;
        ships_coords_array.push_back(ship_coords_object);
    }
    json_object["ships_coords"] = ships_coords_array;

    json_object["double_damage_flag"] = double_damage_flag;

    json_object["last_attempt_user"] = last_attempt_user;
    json_object["last_attempt_enemy"] = last_attempt_enemy;

    json_object["bot_attacked"] = bot_attacked;

    return json_object;
}

void GameBoard::fromJson(const json &jsn)
{
    height_ = jsn.at("height").get<int>();
    width_ = jsn.at("width").get<int>();

    cells_.clear();
    for (const auto &row : jsn.at("cells"))
    {
        std::vector<CellState> rowArray;
        for (const auto &cell : row)
        {
            rowArray.push_back(cell.get<CellState>());
        }
        cells_.push_back(rowArray);
    }

    attacked_coords_.clear();
    for (const auto &coords : jsn.at("attacked_coords"))
    {
        attacked_coords_.insert(Coords{coords.at("x").get<int>(), coords.at("y").get<int>()});
    }

    ships_coords_.clear();
    for (const auto &shipCoords : jsn.at("ships_coords"))
    {
        Ship *ship = new Ship();
        ship->fromJson(shipCoords.at("ship"));
        std::vector<Coords> coordsArray;
        for (const auto &coords : shipCoords.at("coords"))
        {
            coordsArray.push_back(Coords{coords.at("x").get<int>(), coords.at("y").get<int>()});
        }
        ships_coords_[ship] = coordsArray;
    }

    double_damage_flag = jsn.at("double_damage_flag").get<bool>();

    last_attempt_user = jsn.at("last_attempt_user").get<int>();
    last_attempt_enemy = jsn.at("last_attempt_enemy").get<int>();

    bot_attacked = jsn.at("bot_attacked").get<bool>();
}

void GameBoard::updatePointers(ShipManager &shipManager)
{
    std::map<Ship *, std::vector<Coords>> updatedShipsCoords;
    int i = 0;
    for (auto &shipCoords : ships_coords_)
    {
        updatedShipsCoords[&shipManager.getShipAtIndex(i++)] = ships_coords_[shipCoords.first];
        delete shipCoords.first;
    }
    ships_coords_ = std::move(updatedShipsCoords);
}

std::map<Ship*, std::vector<Coords>> GameBoard::getShipsCoords()
{
    return ships_coords_;
}
