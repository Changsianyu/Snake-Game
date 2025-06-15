#ifndef SNAKE_H
#define SNAKE_H

#include "unit.h"
#include <vector>
#include <deque>

class Snake {
private:
    std::deque<Position> body;
    Direction currentDirection;
    bool growFlag;

public:
    Snake(Position startPos, int initialLength = 3, Direction initialDir = Direction::RIGHT);
    
    void move();
    void changeDirection(Direction newDir);
    void grow();
    
    Position getHeadPosition() const;
    const std::deque<Position>& getBody() const;
    Direction getCurrentDirection() const;
    
    bool checkSelfCollision() const;
    
    static Position getDirectionOffset(Direction dir);
};

#endif
