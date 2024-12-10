#ifndef COORDS_H
#define COORDS_H

class Coords
{
private:
    int x;
    int y;

public:
    Coords(int x, int y);
    Coords();
    Coords(const Coords &other);
    Coords(Coords &&other);
    ~Coords() {};

    Coords& operator=(const Coords &other);
    Coords& operator=(Coords &&other);
    bool operator<(const Coords& other) const;
    bool operator==(const Coords& other) const;
    
    int getX() const;
    int getY() const;
};
#endif