#include "../headers/coords.h"

Coords::Coords() : Coords(1, 1) {}

Coords::Coords(int x, int y)
{
    this->x = x;
    this->y = y;
}

Coords::Coords(const Coords &other)
{
    this->x = other.x;
    this->y = other.y;
}

Coords::Coords(Coords &&other)
{
    this->x = other.x;
    this->y = other.y;
}

Coords& Coords::operator=(const Coords &other)
{
    if(this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

Coords& Coords::operator=(Coords &&other)
{
    if(this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

bool Coords::operator<(const Coords& other) const
{
    if(x != other.x)
    {
        return x < other.x;
    }
    else
    {
        return y < other.y;
    }
}

bool Coords::operator==(const Coords& other) const
{
    return x == other.x && y == other.y;
}
 
int Coords::getX() const
{
    return x;
}

int Coords::getY() const
{
    return y;
}