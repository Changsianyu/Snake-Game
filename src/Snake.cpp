#include "Snake.h"
#include <iostream>

Snake::Snake(Position startPos, int initialLength, Direction initialDir) : currentDirection(initialDir), growFlag(false) {
    body.push_front(startPos);
    for (int i = 1; i < initialLength; ++i) {
        body.push_back(startPos + Position(-i, 0)); 
    }
}

void Snake::move() {
    Position head = body.front();
    Position offset = getDirectionOffset(currentDirection);
    
    body.push_front(head + offset);
    
    if (!growFlag) {
        body.pop_back();
    } else {
        growFlag = false;
    }
}

void Snake::changeDirection(Direction newDir) {
    if ((currentDirection == Direction::UP && newDir == Direction::DOWN) ||
        (currentDirection == Direction::DOWN && newDir == Direction::UP) ||
        (currentDirection == Direction::LEFT && newDir == Direction::RIGHT) ||
        (currentDirection == Direction::RIGHT && newDir == Direction::LEFT)) {
        return;
    }
    currentDirection = newDir;
}

void Snake::grow() {
    growFlag = true;
}

Position Snake::getHeadPosition() const {
    return body.front();
}

const std::deque<Position>& Snake::getBody() const {
    return body;
}

Direction Snake::getCurrentDirection() const {
    return currentDirection;
}

bool Snake::checkSelfCollision() const {
    if (body.size() <= 1) {
        return false;
    }
    Position head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (head == body[i]) {
            return true;
        }
    }
    return false;
}

Position Snake::getDirectionOffset(Direction dir) {
    switch (dir) {
        case Direction::UP: return Position(0, -1);
        case Direction::DOWN: return Position(0, 1);
        case Direction::LEFT: return Position(-1, 0);
        case Direction::RIGHT: return Position(1, 0);
        default: return Position(0, 0);
    }
}
