#ifndef UNIT_H
#define UNIT_H

struct Position {
    int x;
    int y;
    Position(int e1 = 0, int e2 = 0) : x(e1), y(e2) {}
    
    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

enum Color { BLACK = 0, RED, GREEN, YELLOW, BLUE, PINK, CYAN, WHITE, NOCHANGE };

enum class Direction {
    UP, DOWN, LEFT, RIGHT, NONE
};

#endif
