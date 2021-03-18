#include "Game.h"
#include <string.h>

void printHelp() {
    const char *helptext = "usage: console_sodoku [OPTIONS] \n\n"
                           "Play Sudoku in the terminal.\n\n"
                           "Optional args:\n"
                           "-h, --help       View this page\n"
                           "-w,  --wasd      Display wasd instead of hjkl\n"
                           "INTEGER          Number of squares to leave empty\n\n"
                           "Move with hjkl, wasd or the arrow keys.\n"
                           "Enter pencil mode by pressing 'p'.\n"
                           "Enter insert mode by pressing 'i'.\n"
                           "Go to a specific square by pressing 'g' followed by the column then row.\n"
                           "Check the board for mistakes by pressing 'c'.\n"
                           "Quit the game by pressing 'q'.\n\n"
                           "For information on Sudoku puzzles see the wikipedia entry:\n"
                           "https://en.wikipedia.org/wiki/Sudoku\n\n"
                           "See the readme for more information.\n"
                           "The readme can be read online at:\n"
                           "https://github.com/flyingpeakock/Console_sudoku/blob/master/README.md\n"
                           "https://philipj.ydns.eu/stagit/Console_sudoku/file/README.md.html\n";
    printf(helptext);
}

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
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        }
    }

    Game game(maxUnknowns, navKeys);
    game.mainLoop();
}
