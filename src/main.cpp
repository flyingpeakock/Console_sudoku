#include "Game.h"

int main(int argc, char *argv[]) {
    int maxUnknowns = 0;
    for (auto i = 1; i < argc; i++) {
        if (atoi(argv[i]) > 0) {
            maxUnknowns = atoi(argv[i]);
        }
    }

    Game game(maxUnknowns);
    game.mainLoop();
}
