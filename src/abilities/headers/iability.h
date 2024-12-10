#ifndef IABILITY_H
#define IABILITY_H

#include <functional>

class GameBoard;

class IAbility
{
public:
    virtual void apply() = 0;
    virtual ~IAbility() = 0;
};


#endif