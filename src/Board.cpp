#include "Board.h"

const int Board::DEFAULT_WIDTH;
const int Board::DEFAULT_HEIGHT;

Board::Board(int w, int h) : width(w), height(h) {}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

bool Board::isInside(Position pos) const {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}
