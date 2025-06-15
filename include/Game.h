#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Snake.h"
#include "Food.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "unit.h"

#include <memory>
#include <random>
#include <chrono>

class Game {
private:
    Board board;
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Food> food;
    
    int score;
    bool isRunning;
    bool isPaused;
    
    std::random_device rd;
    std::mt19937 gen;
    
    int frameCounter;
    static const int FRAME_DELAY_MS = 150;
    
public:
    Game();
    ~Game();
    
    void run();
    void initialize();

private:
    void gameLoop();
    void update();
    void handleInput();
    void render();
    void generateNewFood();
    bool checkCollision();
    void pause();
    void resume();
    void quit();
};

#endif
