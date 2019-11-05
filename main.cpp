#include <iostream>
#include <ctime>
#include "Game.h"

using namespace std;

int main() {
    // makes the rand() function produce more "random" numbers
    srand(time(NULL));

    // start the game
    Game* game = new Game;
    game->start();
    
    return 0;
}
