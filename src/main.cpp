#include "Game.h"
#include <string.h>

int main(int argc, char *argv[]) {
    int maxUnknowns = 0;
    char navKeys[] = "hjkl";
    for (auto i = 1; i < argc; i++) {
        if (atoi(argv[i]) > 0) {
            maxUnknowns = atoi(argv[i]);
        }
        if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--wasd") == 0) {
            strcpy(navKeys, "aswd");
        }
    }

    Game game(maxUnknowns, navKeys);
    game.mainLoop();
}
