#include <iostream>
#include "Generator.h"
#include <ncurses.h>
#include <string.h>
#include <locale.h>
#include <vector>

#define WIDTH 37
#define HEIGHT 19

void pencil(std::vector<char> &pencilMarks, char val) {
    int x, y;
    getyx(stdscr, y, x);

    bool newMark = true;

    // Updating pencil marks after removing input
    if (val == '\0') {
        newMark = false;
    }

    // If backspace or space, remove most recent pencilMark
    if (val == ' ') {
        if (pencilMarks[0] != ' ') {
            pencilMarks.erase(pencilMarks.begin());
        }
        newMark = false;
    }
    
    // Check if pencil mark exists, if index is more than 2
    // move to front, if index is less, remove it
    for (auto i = 0; i < pencilMarks.size(); i++) {
        if (pencilMarks[i] == val) {
            if (i > 2) {
                pencilMarks.erase(pencilMarks.begin() + i);
                pencilMarks.insert(pencilMarks.begin(), val);
            }
            else {
                pencilMarks.erase(pencilMarks.begin() + i);
            }
            newMark = false;
            break;
        }
    }

    if (newMark) {
        pencilMarks.insert(pencilMarks.begin(), val);
    }

    char str[] = {pencilMarks[0], pencilMarks[2], pencilMarks[1], '\0'};
    attron(A_DIM);
    mvprintw(y, x - 1, "%s", str);
    attroff(A_DIM);
}

void input(std::array<std::array<int, 9>, 9> &grid,
           std::array<std::array<int, 9>, 9> &solution, 
           char val, 
           std::vector<char> &pencilMarks,
           int row,
           int col) {

    int x, y;
    getyx(stdscr, y, x);
    if (grid[row][col] == solution[row][col]) {
        // Already correct value in space, do nothing
        return;
    }
    if (val == ' ') {
        // Player wants to remove incorrect value
        printw(" ");
        move(y, x);
        pencil(pencilMarks, '\0');
        return;
    }
    if ((int) (val - '0') != solution[row][col]) {
        // Player is placing a bad value, mark it red
        attron(COLOR_PAIR(1));
    }
    // Print a 3 long string to overwrite any pencil marks
    attron(A_BOLD);
    mvprintw(y, x - 1, " %c ", val);
    grid[row][col] = val - '0';
    attroff(A_BOLD);

    attroff(COLOR_PAIR(1));
}

void go(int top, int left){
    top--;
    left -= 2;
    char col, row = 0;
    while (col < '1' || col > '9') {
        col = getch();
        if (col == 'q') {
            return;
        }
    }
    while (row < '1' || row > '9') {
        row = getch();
        if (row == 'q') {
            return;
        }
    }

    // Get index from input;
    col -= '1';
    row -= '1';

    int scr_col = (col * 4) + left + 2;
    int scr_row = (row * 2) + top + 1;

    move(scr_row, scr_col);
}

void printBoxes(const int startWidth, const int startHeight) {
    const char topRow[] = "\u2554\u2550\u2550\u2550\u2564\u2550\u2550\u2550\u2564"
                          "\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2564\u2550"
                          "\u2550\u2550\u2564\u2550\u2550\u2550\u2566\u2550\u2550"
                          "\u2550\u2564\u2550\u2550\u2550\u2564\u2550\u2550\u2550\u2557";
    const char middleRow[] = "\u2551   \u2502   \u2502   \u2551   \u2502"
                             "   \u2502   \u2551   \u2502   \u2502   \u2551";
    const char middleRow2[] = "\u255f\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u253c"
                              "\u2500\u2500\u2500\u256b\u2500\u2500\u2500\u253c"
                              "\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u256b"
                              "\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u253c"
                              "\u2500\u2500\u2500\u2562";
    const char middleRow3[] = "\u2560\u2550\u2550\u2550\u256a\u2550\u2550\u2550\u256a"
                              "\u2550\u2550\u2550\u256c\u2550\u2550\u2550\u256a"
                              "\u2550\u2550\u2550\u256a\u2550\u2550\u2550\u256c"
                              "\u2550\u2550\u2550\u256a\u2550\u2550\u2550\u256a"
                              "\u2550\u2550\u2550\u2563";
    const char botRow[] = "\u255a\u2550\u2550\u2550\u2567\u2550\u2550\u2550\u2567"
                          "\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2567"
                          "\u2550\u2550\u2550\u2567\u2550\u2550\u2550\u2569"
                          "\u2550\u2550\u2550\u2567\u2550\u2550\u2550\u2567"
                          "\u2550\u2550\u2550\u255d";
    
    attron(A_BOLD);
    mvprintw(startHeight, startWidth, "%s", topRow);
    for (auto i = 0; i < 3; i++) {
        mvprintw((startHeight + 1) + 6*i, startWidth, "%s", middleRow);
        mvprintw((startHeight + 2) + 6*i, startWidth, "%s", middleRow2);
        mvprintw((startHeight + 3) + 6*i, startWidth, "%s", middleRow);
        mvprintw((startHeight + 4) + 6*i, startWidth, "%s", middleRow2);
        mvprintw((startHeight + 5) + 6*i, startWidth, "%s", middleRow);
        if (i != 2)
            mvprintw((startHeight + 6) + 6*i, startWidth, "%s", middleRow3);
    }
    mvprintw(startHeight + 18, startWidth, "%s", botRow);
    attroff(A_BOLD);
}

void printCoords(const int width, const int height) {
    const int top = height  - 1;
    const int topleft = width + 2;
    const int left = width - 2;
    mvprintw(top, topleft, "1   2   3   4   5   6   7   8   9");
    for (auto i = 0; i < 9; i++) {
        mvprintw((top + 2) + (i*2), left, "%d", i + 1);
    }
}

void printInstructions(const int width, const int height) {
    const int row = height + 4;
    const int col = width + 42;

    mvaddch(row, col + 3, 'k');
    mvaddch(row + 2, col, 'h');
    mvaddch(row + 2, col + 6, 'l');
    mvaddch(row + 4, col + 3, 'j');
    attron(A_UNDERLINE);
    mvaddch(row + 8, col, 'i');
    attroff(A_UNDERLINE);
    printw("nsert");
    attron(A_UNDERLINE);
    mvaddch(row + 9, col, 'p');
    attroff(A_UNDERLINE);
    printw("encil");
    attron(A_UNDERLINE);
    mvaddch(row + 10, col, 'g');
    attroff(A_UNDERLINE);
    printw("o");
    attron(A_UNDERLINE);
    mvaddch(row + 11, col, 'q');
    attroff(A_UNDERLINE);
    printw("uit");
}

void printNumbs(const int width, const int height, std::array<std::array<int, 9>, 9> &grid) {
    int y = height + 1;

    attron(A_BOLD);
    for (auto ar : grid) {
        int x = width + 2;
        for (auto num : ar) {
            const char ch = num + '0';
            if (ch > '0') {
                mvaddch(y, x, ch);
            }
            x += 4;
        }
        y += 2;
    }
    attroff(A_BOLD);
}

void printPencil(const int width, const int height,
                 std::array<std::array<std::vector<char>, 9>, 9> &pencilMarks,
                 std::array<std::array<int, 9>, 9> &grid) {

    attron(A_DIM);
    int y = height + 1;
    //for (auto &arr : pencilMarks) {
    for (auto i = 0; i < pencilMarks.size(); i++) {
        int x = width + 1;
        //for (auto &ar : arr) {
        for (auto j = 0; j < pencilMarks[i].size(); j++) {
            if (grid[i][j] < 1) {
                std::vector<char> ar = pencilMarks[i][j];
                char str[] = {ar[0], ar[2], ar[1], '\0'};
                mvprintw(y, x, "%s", str);
            }
            x += 4;
        }
        y += 2;
    }
    attroff(A_DIM);
}

void draw(int &nc_col, int &nc_row, int &gridTop, int &gridLeft,
          std::array<std::array<int, 9>, 9> &grid,
          std::array<std::array<std::vector<char>, 9>, 9> &pencilMarks,
          bool showInstructions, bool showCoords, bool showTitle) {

    int y, x;
    getyx(stdscr, y, x);

    // Get cursor position to move it back after drawing
    const int pos_y = (y - ((nc_row - HEIGHT) / 2)) / 2;
    const int pos_x = (x - ((nc_col - WIDTH) / 2)) / 4;

    // Get new screen size
    getmaxyx(stdscr, nc_row, nc_col);

    int top = (nc_row - HEIGHT) / 2;
    int left = (nc_col - WIDTH) / 2;
    gridTop = top + 1;
    gridLeft = left + 2;

    clear();

    if (nc_row < HEIGHT || nc_col < WIDTH) {
        char error[] = "Not enough space to draw board";
        mvprintw(nc_row / 2, (nc_col - strlen(error)) / 2, "%s", error);
        move(0,0);
        refresh();
        return;
    }

    if (nc_row - HEIGHT >= 4 && showTitle) {
        attron(A_BOLD | A_UNDERLINE);
        char title[] = "Console Sudoku";
        mvprintw(top - 3, (nc_col - strlen(title)) / 2, "%s", title);
        attroff(A_BOLD | A_UNDERLINE);
    }

    printBoxes(left, top);
    printPencil(left, top, pencilMarks, grid);
    printNumbs(left, top, grid);
    if (nc_col - WIDTH >= 24 && showInstructions)
        printInstructions(left, top);
    if (nc_col - WIDTH >= 4 && nc_row - HEIGHT >= 2 && showCoords)
        printCoords(left, top);

    // Move cursor back into correct box
    move((pos_y * 2) + top + 1, (pos_x * 4) + left + 2);

    refresh();
}

void removeMarks(char val, int row, int col,
                 std::array<std::array<std::vector<char>, 9>, 9> &pencilMarks) {

    for (auto i = 0; i < 9; i++) {
        for (auto j = 0; j < pencilMarks[row][i].size(); j++) {
            if (val == pencilMarks[row][i][j]) {
                pencilMarks[row][i].erase(pencilMarks[row][i].begin() + j);
                break;
            }
        }
    }
    
    for (auto i = 0; i < 9; i++) {
        for (auto j = 0; j < pencilMarks[i][col].size(); j++) {
            if (val == pencilMarks[i][col][j]) {
                pencilMarks[i][col].erase(pencilMarks[i][col].begin() + j);
                break;
            }
        }
    }

    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (auto i = boxRow; i < boxRow + 3; i++) {
        for (auto j = boxCol; j < boxCol + 3; j++) {
            for (auto k = 0; k < pencilMarks[boxRow][boxCol].size(); k++) {
                if (val == pencilMarks[i][j][k]) {
                    pencilMarks[i][j].erase(pencilMarks[i][j].begin() + k);
                    break;
                }
            }
        }
    }
}


int main(int argc, char *argv[]) {
    bool showInstructions = true;
    bool showCoords = true;
    bool showTitle = true;
    bool showMode = true;
    bool showColor = true;
    for (auto i = 1; i < argc; i++) {
        if (strcmp(argv[i], "nocolor") == 0) {
            showColor = false;
        }
        else if (strcmp(argv[i], "noinstructions") == 0) {
            showInstructions = false;
        }
        else if (strcmp(argv[i], "nocoords") == 0) {
            showCoords = false;
        }
        else if (strcmp(argv[i],"notitle") == 0) {
            showTitle = false;
        }
        else if (strcmp(argv[i],"nomode") == 0) {
            showMode = false;
        }
        else if (strcmp(argv[i], "clean") == 0) {
            showInstructions = false;
            showCoords = false;
            showTitle = false;
            showMode = false;
        }
    }

    setlocale(LC_ALL, "");
    
    int nc_row, nc_col;

    initscr();
    getmaxyx(stdscr, nc_row, nc_col);
    cbreak();  // Get input before enter is pressed
    noecho();  // Do not show keypresses
    if (has_colors() && showColor) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
    }

    attron(A_BOLD);
    char loading[] = "Generating puzzle...";
    mvprintw(0, (nc_col - strlen(loading))/2, "%s", loading);
    attroff(A_BOLD);
    refresh();

    // Generate grid and solution
    Generator gen;
    auto grid = gen.getGrid();
    auto solution = gen.getSolution();

    // Initialize pencilmarks
    std::array<std::array<std::vector<char>, 9>, 9> pencilMarks;
    for (auto &array : pencilMarks) {
        for (auto &v : array) {
            for (auto i = 0; i < 3; i++) {
                // Adds 3 spaces to vector to make it easier to print later
                v.insert(v.begin(), ' ');
            }
        }
    }

    // Move cursor to where first box will be
    move(((nc_row - HEIGHT) / 2) + 1, ((nc_col - WIDTH) / 2) + 2);

    int top, left;
    draw(nc_col, nc_row, top, left, grid, pencilMarks, showInstructions,
         showCoords, showTitle);

    bool insertMode = true;
    bool isRunning = true;
    while (isRunning) {
        int y, x;
        getyx(stdscr, y, x);
        if (nc_row >= HEIGHT + 1 && !(nc_row < HEIGHT || nc_col < WIDTH) && showMode) {
            move(top + 18, left - 2);
            clrtoeol();
            printw("%s", insertMode? "Insert mode" : "Pencil mode");
            move(y, x);
        }
        refresh();
        wchar_t ch = wgetch(stdscr);
        switch (ch) {
        case KEY_RESIZE:
            draw(nc_col, nc_row, top, left, grid, pencilMarks, showInstructions,
                 showCoords, showTitle);
            break;
        case L'h':
            if (x - 4 >= left)
                move(y, x - 4);
            break;
        case L'j':
            if (y + 2 <= top + 16)
                move(y + 2, x);
            break;
        case L'k':
            if (y - 2 >= top) 
                move(y - 2, x);
            break;
        case L'l':
            if (x + 4 <= left + 32)
                move(y, x + 4);
            break;
        case L'i':
            insertMode = true;
            break;
        case L'p':
            insertMode = false;
            break;
        case L'g':
            go(top, left);
            break;
        case L'q':
            isRunning = false;
            break;
        default:
            if ((ch > L'0' && ch <= '9') || ch == L' ') {
                int row = (y - top) / 2;
                int col = (x - left) / 4;
                if (insertMode) {
                    input(grid, solution, ch, pencilMarks[row][col], row, col);
                    if ((int) (ch - '0') == solution[row][col]) {
                        removeMarks(ch, row, col, pencilMarks);
                        printPencil(left - 2, top - 1, pencilMarks, grid);
                    }
                }
                else if (grid[row][col] != solution[row][col]) 
                    pencil(pencilMarks[row][col], ch);
            }

            if (grid == solution) {
                move(top + 18, left - 2);
                clrtoeol();
                printw("Winner winner, chicken dinner!");
                isRunning = false;
            }
            move(y, x);
            refresh();
        }
    }
    if (grid == solution)
        getch();
    endwin();
}