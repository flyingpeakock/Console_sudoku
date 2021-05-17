#include "Game.h"
#include "Stopwatch.h"
#include <ctime>
#include <sstream>

Game::Game(Board b, char *navKeys): board(b), window(&board, navKeys) {
    mode = 'i';
    row = 0;
    col = 0;
}

void Game::mainLoop() {
    board.startPlaying();
    Stopwatch timer;
    timer.start();
    while (board.isPlaying()) {
        window.printBoard();
        wchar_t prevMode = mode;
        int ch = wgetch(stdscr);
        switch (ch) {
        case KEY_LEFT:
        case 'a':
        case 'h':
            left();
            break;
        case KEY_DOWN:
        case 's':
        case 'j':
            down();
            break;
        case KEY_UP:
        case 'w':
        case 'k':
            up();
            break;
        case KEY_RIGHT:
        case 'd':
        case 'l':
            right();
            break;
        case 'g':
            changeMode(ch);
            window.printBoard();
            go();
            changeMode(prevMode);
            break;
        case 'i':
        case 'p':
            changeMode(ch);
            break;
        case 'q':
            board.stopPlaying();
            break;
        case 'c':
            window.check();
            break;
        case 27:
            if (mode == 'i') {
                changeMode('p');
            }
            else {
                changeMode('i');
            }
            break;
        default:
            if ((ch > '0' && ch <= '9') || ch == ' ') {
                window.select(ch);
                if (mode == 'i') {
                    insert(ch);
                }
                else if (mode == 'p') {
                    pencil(ch);
                }
            }
        }

        board.isWon();
    }
    timer.stop();
    if (!board.isWon()) {
        return;
    }

    window.changeMode(timer.timeTaken());
    window.printBoard();

    getch();
}

void Game::insert(char val) {
    board.insert(val, row, col);
}

void Game::pencil(char val) {
    board.pencil(val, row, col);
}

void Game::changeMode(wchar_t c) {
    std::string s;
    switch (c) {
    case L'i':
        s = "Input mode";
        mode = c;
        break;
    case L'p':
        s = "Pencil mode";
        mode = c;
        break;
    case L'g':
        s = "Go";
        mode = c;
        break;
    }
    window.changeMode(s);
}


void Game::up() {
    if (row <= 0) {
        row = 9;
    }
    window.moveCursor(--row, col);
}

void Game::down() {
    if (row >= 8) {
        row = -1;
    }
    window.moveCursor(++row, col);
}

void Game::left() {
    if (col <= 0) {
        col = 9;
    }
    window.moveCursor(row, --col);
}

void Game::right() {
    if (col >= 8) {
        col = -1;
    }
    window.moveCursor(row, ++col);
}

void Game::go() {
    char r = 0;
    char c = 0;
    while (c < '1' || c > '9') {
        c = getch();
        if (c == 'q') {
            return;
        }
    }

    while (r < '1' || r > '9') {
        r = getch();
        if (r == 'q') {
            return;
        }
    }
    window.moveCursor(r - '1', c - '1');
    row = r - '1';
    col = c - '1';
}