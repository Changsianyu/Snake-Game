#include "Game.h"
#include <iostream>

int main() {
    try {
        Game game;
        game.run();
    } catch(const std::exception& e) {
        std::cerr << "Something wrong: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
