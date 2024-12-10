#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "segment_already_destroyed_exception.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

enum ShipOrientation
{
    HORIZONTAL,
    VERTICAL
};

enum Length
{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4
};

enum ShipSegmentState
{
    INTACT,
    DAMAGED,
    DESTROYED
};

class Ship
{
private:
    Length length_;
    ShipOrientation orientation_;
    std::vector<ShipSegmentState> segments_;

public:
    Ship();
    Ship(Length length);
    Ship(Length length, ShipOrientation orientation);
    Ship(const Ship &other);
    Ship(Ship &&other);
    ~Ship() {};

    Ship &operator=(const Ship &other);
    Ship &operator=(Ship &&other);

    void setOrientation(ShipOrientation orientation);
    void setOrientation(char orientation_char);
    void hitSegment(int index);
    bool isDestroyed() const;

    void setSegmentAtIndex(int index, ShipSegmentState state);

    const Length getLength() const;
    const ShipOrientation getOrientation() const;
    const ShipSegmentState getSegmentAtIndex(int index) const;

    //void toJson() const;
    json toJson() const;
    void fromJson(const json& jsn);
};

#endif