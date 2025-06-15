#include "Renderer.h"
#include <iostream>
#include <iomanip>
#include <string>

const char* Renderer::SNAKE_CHAR = "██";
const char* Renderer::FOOD_CHAR = "● ";
const char* Renderer::EMPTY_CHAR = "  ";

void Renderer::renderGame(const Board& board, const Snake& snake, const Food& food, int score) {
    clearScreen();
    
    std::cout << AnsiPrint("=== Snake Game ===", WHITE, NOCHANGE, true) << std::endl;
    std::cout << std::endl;
    
    renderGameBoard(board, snake, food);
    std::cout << std::endl;
    renderUI(score, board.getWidth());
}

void Renderer::renderGameOver(int score) {
    clearScreen();
    
    const int effective_board_width_chars = Board().DEFAULT_WIDTH * 2;
    const int total_frame_width = effective_board_width_chars + 2;
    
    std::string horizontal_border(total_frame_width - 2, '═');

    std::string top_border_line_str = "╔" + horizontal_border + "╗";
    std::cout << AnsiPrint(top_border_line_str.c_str(), RED) << std::endl;
    
    std::string game_over_content = "GAME OVER!";
    std::string game_over_line_inner = std::string((total_frame_width - 2 - game_over_content.length()) / 2, ' ') + game_over_content + std::string((total_frame_width - 2 - game_over_content.length() + 1) / 2, ' ');
    std::string game_over_full_line_str = "║" + game_over_line_inner + "║";
    std::cout << AnsiPrint(game_over_full_line_str.c_str(), RED, NOCHANGE, true) << std::endl;


    std::string middle_border_line_str = "╠" + horizontal_border + "╣";
    std::cout << AnsiPrint(middle_border_line_str.c_str(), RED) << std::endl;
    
    std::string score_label_content = "Final Score: ";
    std::string score_value_content = std::to_string(score);
    
    int content_length = score_label_content.length() + score_value_content.length();
    int padding_needed = total_frame_width - 2 - content_length;

    std::string score_line_content_str = AnsiPrint(score_label_content.c_str(), YELLOW, NOCHANGE, true) + AnsiPrint(score_value_content.c_str(), YELLOW, NOCHANGE, true);
    std::string score_full_line_str = "║" + score_line_content_str + std::string(padding_needed, ' ') + "║";
    std::cout << AnsiPrint(score_full_line_str.c_str(), RED) << std::endl;
    
    std::string bottom_border_line_str = "╚" + horizontal_border + "╝";
    std::cout << AnsiPrint(bottom_border_line_str.c_str(), RED) << std::endl;
}


void Renderer::clearScreen() {
    std::cout << "\x1b[2J\x1b[H";
}

void Renderer::renderGameBoard(const Board& board, const Snake& snake, const Food& food) {
    std::vector<std::vector<std::string>> displayGrid(board.getHeight(), std::vector<std::string>(board.getWidth(), EMPTY_CHAR));
    
    displayGrid[food.getPosition().y][food.getPosition().x] = AnsiPrint(FOOD_CHAR, YELLOW, NOCHANGE, true);
    
    const auto& snakeBody = snake.getBody();
    for (const auto& segment : snakeBody) {
        if (board.isInside(segment)) {
            displayGrid[segment.y][segment.x] = AnsiPrint(SNAKE_CHAR, GREEN, NOCHANGE, true);
        }
    }
    
    std::string top_border_line_str = "╔";
    for (int i = 0; i < board.getWidth(); ++i) {
        top_border_line_str += "══";
    }
    top_border_line_str += "╗";
    std::cout << AnsiPrint(top_border_line_str.c_str(), RED) << std::endl;
    
    for (int y = 0; y < board.getHeight(); ++y) {
        std::cout << AnsiPrint("║", RED);
        for (int x = 0; x < board.getWidth(); ++x) {
            std::cout << displayGrid[y][x]; 
        }
        std::cout << AnsiPrint("║", RED) << std::endl;
    }
    
    std::string bottom_border_line_str = "╚";
    for (int i = 0; i < board.getWidth(); ++i) {
        bottom_border_line_str += "══";
    }
    bottom_border_line_str += "╝";
    std::cout << AnsiPrint(bottom_border_line_str.c_str(), RED) << std::endl;
}

void Renderer::renderUI(int score, int board_width) {
    const int effective_board_width_chars = board_width * 2;
    const int total_frame_width = effective_board_width_chars + 2;

    std::string horizontal_line_str(total_frame_width - 2, '─');
    
    std::string top_line_str = "┌" + horizontal_line_str + "┐";
    std::cout << AnsiPrint(top_line_str.c_str(), WHITE) << std::endl;
    
    std::string score_value_str = std::to_string(score);
    std::string score_label_content = "Score: ";
    int score_label_visual_len = score_label_content.length();
    int score_value_visual_len = score_value_str.length();
    int remaining_space = effective_board_width_chars - score_label_visual_len - score_value_visual_len;
    
    std::string score_line_content_str = AnsiPrint(score_label_content.c_str(), WHITE) + AnsiPrint(score_value_str.c_str(), YELLOW, NOCHANGE, true);
    std::string score_full_line_str = "│" + score_line_content_str + std::string(remaining_space, ' ') + "│";
    std::cout << AnsiPrint(score_full_line_str.c_str(), WHITE) << std::endl;
    
    std::string bottom_line_str = "└" + horizontal_line_str + "┘";
    std::cout << AnsiPrint(bottom_line_str.c_str(), WHITE) << std::endl;
}
