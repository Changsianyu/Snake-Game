#include "Food.h"

Food::Food(Position pos) : position(pos) {}

void Food::setPosition(Position pos) {
    position = pos;
}

Position Food::getPosition() const {
    return position;
}
