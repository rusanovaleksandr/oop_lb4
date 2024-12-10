#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    virtual void accept() = 0;
    virtual ~Observer() = default;
};

#endif