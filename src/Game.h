#pragma once

#include "Window.h"
#include "Board.h"

class Game{
    private:
        Board board;
        Window window;
        wchar_t mode;
        int row, col;
    public:
        Game(Board b, char *navKeys);
        void mainLoop();
        void changeMode(wchar_t c);
        void up();
        void down();
        void left();
        void right();
        void insert(char val);
        void pencil(char val);
        void go();
        void check();
};