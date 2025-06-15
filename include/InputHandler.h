#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <termios.h> 
#include <unistd.h> 
#include "unit.h"

extern struct termios old_termios, new_termios;

class InputHandler {
public:
    static Direction getDirectionInput();
    static bool getGameControlInput(char& key);
    
    static void setupTerminal();
    static void resetTerminal();
    
private:
    static int readChar();
};

#endif
