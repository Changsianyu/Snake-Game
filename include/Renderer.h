#ifndef RENDERER_H
#define RENDERER_H

#include "Board.h"
#include "Snake.h"
#include "Food.h"
#include "AnsiPrint.h"
#include "unit.h"
#include <vector>
#include <string>

class Renderer {
public:
    static void renderGame(const Board& board, const Snake& snake, const Food& food, int score);
    static void renderGameOver(int score);
    static void clearScreen();
private:
    static void renderGameBoard(const Board& board, const Snake& snake, const Food& food);
    static void renderUI(int score, int board_width); 
    
    static const char* SNAKE_CHAR;
    static const char* FOOD_CHAR;
    static const char* EMPTY_CHAR;
};

#endif
