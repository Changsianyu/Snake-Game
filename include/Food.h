#ifndef FOOD_H
#define FOOD_H

#include "unit.h"

class Food {
private:
    Position position;

public:
    Food(Position pos = Position(0,0));
    
    void setPosition(Position pos);
    Position getPosition() const;
};

#endif
