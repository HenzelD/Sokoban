#include "Game.h"

int main(int argc, char** argv)
{
    int gameMode = 1; // 1 - normal, 2 - hard

    if (argc > 1 && (std::string)argv[1] == (std::string)"hard") {
        gameMode = 2;
    }

    Game game = Game(gameMode);
    game.play();

    return 0;
}
