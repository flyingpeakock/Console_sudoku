#pragma once

#include "Board.h"
#include <ncurses.h>
#include <string>

class Window {
    private:
        Board *game;
        int cursorRow, cursorCol;
        int windowRows, windowCols;
        const int BoardRows = 19;
        const int BoardCols = 37;
        int boardTop;
        int boardLeft;
        std::string mode;
        bool checkColors;
        int highlightNum;

        char leftKey;
        char downKey;
        char upKey;
        char rightKey;

        void printBoxes();
        void printPencil();
        void printNumbs();
        void printInstructions();
        void printCoords();
        void printMode();
        void printCursor();
    public:
        Window(Board *g, char *navKeys);
        ~Window();
        void moveCursor(int row, int col);
        void printBoard();
        void changeMode(std::string s);
        void check();
        void select(int val);
};