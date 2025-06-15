#ifndef BOARD_H
#define BOARD_H

#include "unit.h"
#include <vector>

class Board {
private:
    
    int width;
    int height;

public:
	static const int DEFAULT_WIDTH = 20;
	static const int DEFAULT_HEIGHT = 15;
    Board(int w = DEFAULT_WIDTH, int h = DEFAULT_HEIGHT);
    
    int getWidth() const;
    int getHeight() const;
    
    bool isInside(Position pos) const;
};

#endif
