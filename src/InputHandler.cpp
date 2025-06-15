#include "InputHandler.h"
#include <cstdio>
#include <cstdlib>

struct termios old_termios, new_termios;

int InputHandler::readChar() {
    fflush(stdout);
    char buf[4096];    
    int n = read(STDIN_FILENO, buf, 1);
    return (n > 0) ? buf[0] : -1;
}

Direction InputHandler::getDirectionInput() {
    int key = readChar();
    
    switch(key) {
        case 'w': case 'W': return Direction::UP;
        case 'a': case 'A': return Direction::LEFT;
        case 's': case 'S': return Direction::DOWN;
        case 'd': case 'D': return Direction::RIGHT;
        default: return Direction::NONE;
    }
}

bool InputHandler::getGameControlInput(char& key) {
    int input = readChar();
    if (input != -1) {
        key = static_cast<char>(input);
        return true;
    }
    return false;
}

void InputHandler::setupTerminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 0;              
    new_termios.c_cc[VTIME] = 0;             
    
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    
    printf("\x1b[?25l");
    std::atexit(resetTerminal);
}

void InputHandler::resetTerminal() {
    printf("\x1b[0m");
    printf("\x1b[?25h");
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}
