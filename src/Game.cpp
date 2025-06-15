#include "Game.h"
#include <iostream>
#include <thread>
#include <algorithm>

Game::Game() 
    : board(Board::DEFAULT_WIDTH, Board::DEFAULT_HEIGHT), 
      score(0), 
      isRunning(false), 
      isPaused(false),
      gen(rd()),
      frameCounter(0) {
}

Game::~Game() {
    InputHandler::resetTerminal();
}

void Game::run() {
    InputHandler::setupTerminal();
    initialize();
	gameLoop();
}

void Game::initialize() {
    Position initialSnakePos(board.getWidth() / 2, board.getHeight() / 2);
    snake = std::make_unique<Snake>(initialSnakePos, 3, Direction::RIGHT);
    
    generateNewFood();
    score = 0;
    isRunning = true;
    isPaused = false;
    frameCounter = 0;
    fflush(stdout);
    char temp_key;
    InputHandler::getGameControlInput(temp_key); 
    Renderer::clearScreen();
}

void Game::gameLoop() {
    while(isRunning) {
        auto frameStart = std::chrono::steady_clock::now();
        
        handleInput();
        
        if(!isPaused) {
            update();
            render();
            
            if (checkCollision()) {
                isRunning = false;
                Renderer::renderGameOver(score);
                char temp_key;
                InputHandler::getGameControlInput(temp_key);
            }
        } else {
            render(); 
        }
        
        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        
        if(elapsed.count() < FRAME_DELAY_MS) {
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS - elapsed.count()));
        }
    }
}

void Game::update() {
    snake->move();
    
    if (snake->getHeadPosition() == food->getPosition()) {
        snake->grow();
        score++;
        generateNewFood();
    }
}

void Game::handleInput() {
    Direction newDir = InputHandler::getDirectionInput();
    if (newDir != Direction::NONE) {
        snake->changeDirection(newDir);
    }

    char controlKey;
    if (InputHandler::getGameControlInput(controlKey)) {
        if (controlKey == 'p' || controlKey == 'P') {
            if (isPaused) resume();
            else pause();
        } else if (controlKey == 'q' || controlKey == 'Q') {
            quit();
        }
    }
}
void Game::render() {
	Renderer::renderGame(board, *snake, *food, score);
}

void Game::generateNewFood() {
    std::uniform_int_distribution<> dis_x(0, board.getWidth() - 1);
    std::uniform_int_distribution<> dis_y(0, board.getHeight() - 1);
    
    Position newFoodPos;
    bool validPosFound = false;
    
    while (!validPosFound) {
        newFoodPos = Position(dis_x(gen), dis_y(gen));
        
        bool collisionWithSnake = false;
        const auto& snakeBody = snake->getBody();
        for (const auto& segment : snakeBody) {
            if (newFoodPos == segment) {
                collisionWithSnake = true;
                break;
            }
        }
        
        if (!collisionWithSnake) {
            validPosFound = true;
        }
    }
    
    if (!food) {
        food = std::make_unique<Food>(newFoodPos);
    } else {
        food->setPosition(newFoodPos);
    }
}

bool Game::checkCollision() {
    if (!board.isInside(snake->getHeadPosition())) {
        return true;
    }
    
    if (snake->checkSelfCollision()) {
        return true;
    }
    
    return false;
}

void Game::pause() {
    isPaused = true;
}

void Game::resume() {
    isPaused = false;
}

void Game::quit() {
    isRunning = false;
}
