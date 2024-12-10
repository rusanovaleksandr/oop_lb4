#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <map>
#include <set>
#include <iostream>
#include "ship_manager.h"
#include "coords.h"
#include "observer.h"
#include "../../exceptions/headers/ship_placement_exception.h"
#include "../../exceptions/headers/out_of_bounds_exception.h"
#include "../../exceptions/headers/cell_already_attacked_exception.h"

enum CellState
{
    UNKNOWN,
    EMPTY,
    SHIP
};

enum BoardSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class GameBoard
{
private:
    int height_;
    int width_;
    Observer* observer;
    std::vector<std::vector<CellState>> cells_;
    std::set<Coords> attacked_coords_;
    std::map<Ship*, std::vector<Coords>> ships_coords_;

    bool double_damage_flag{false};
    int last_attempt_user{0};
    int last_attempt_enemy{0};
    bool bot_attacked{false};

    void addShipOnBoard(Ship *ship);
    void markSurroundingCells(Ship *ship);

public:
    GameBoard();
    GameBoard(Observer* observer);
    GameBoard(int x, int y, Observer* observer);
    GameBoard(int x, int y);
    GameBoard(const GameBoard &other);
    GameBoard(GameBoard &&other);
    ~GameBoard() = default;

    GameBoard &operator=(const GameBoard &other);
    GameBoard &operator=(GameBoard &&other);

    bool checkCoordinatesForShipPlacement(Coords coords);
    bool validateCoordinatesInBounds(Coords coords);
    bool addShip(Ship *ship, const Coords &coords);
    bool shoot(Coords shoot_coordinate);
    
    void setObserver(Observer* observer);
    
    void setDoubleDamageFlag(bool value);
    bool getDoubleDamageFlag();

    bool getBotAttacked();
    void setBotAttacked(bool value);

    bool getLastAttemptUser();
    bool getLastAttemptEnemy();

    void setLastAttemptUser(bool value);
    void setLastAttemptEnemy(bool value);

    Ship* findShipByCoords(const Coords& coords) const;
    bool isShipAt(const Coords& coords) const;
    const ShipSegmentState getSegmentShipState(const Coords &coords);

    const int getHeight() const;
    const int getWidth() const;
    const std::vector<std::vector<CellState>> &getCells() const;
    const std::set<Coords> &getAttackedCoords() const;
    std::map<Ship*, std::vector<Coords>> getShipsCoords();

    BoardSize determineBoardSize();

    void resetBoard();
    void updatePointers(ShipManager& ship_manager);

    json toJson() const; 
    void fromJson(const json& jsn);

};

#endif