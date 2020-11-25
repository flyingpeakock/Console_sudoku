#include <iostream>
#include "Generator.h"
#include <ncurses.h>
#include <string.h>
#include <locale.h>
#include <vector>

#define SIZE 37

int calcRow(int x, int y, int middle) {
    return (x - (middle + 2)) / 4;
}

int calcCol(int x, int y) {
    return (y - 4) / 2;
}

void pencil(std::vector<char> &pencilMarks, char val) {
    int x, y;
    getyx(stdscr, y, x);

    bool newMark = true;

    // Updating pencil marks after removing input
    if (val == '\0') {
        newMark = false;
    }

    // If backspace or space, remove most recent pencilMark
    if (val == KEY_BACKSPACE || val == ' ') {
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
    if (grid[col][row] == solution[col][row]) {
        // Already correct value in space, do nothing
        return;
    }
    if (val == KEY_BACKSPACE || val == ' ') {
        // Player wants to remove incorrect value
        printw(" ");
        move(y, x);
        pencil(pencilMarks, '\0');
        return;
    }
    if ((int) (val - '0') != solution[col][row]) {
        // Player is placing a bad value, mark it red
        attron(COLOR_PAIR(1));
    }
    // Print a 3 long string to overwrite any pencil marks
    attron(A_BOLD);
    mvprintw(y, x - 1, " %c ", val);
    grid[col][row] = val - '0';
    attroff(A_BOLD);

    attroff(COLOR_PAIR(1));
}

int main() {
    setlocale(LC_ALL, "");
    
    int nc_row, nc_col;

    initscr();
    getmaxyx(stdscr, nc_row, nc_col);
    cbreak();  // Get input before enter is pressed
    noecho();  // Do not show keypresses
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
    }

    attron(A_BOLD);
    char loading[] = "Generating puzzle...";
    mvprintw(1, (nc_col - strlen(loading))/2, "%s", loading);
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

    clear();
    attron(A_BOLD | A_UNDERLINE);
    char title[] = "Console Sudoku";
    mvprintw(1,(nc_col-strlen(title))/2,"%s",title);
    attroff(A_BOLD | A_UNDERLINE);

    // Printing boxes
    // char topRow[] =     "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗";
    char topRow[] = "\u2554\u2550\u2550\u2550\u2564\u2550\u2550\u2550\u2564"
                    "\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2564\u2550"
                    "\u2550\u2550\u2564\u2550\u2550\u2550\u2566\u2550\u2550"
                    "\u2550\u2564\u2550\u2550\u2550\u2564\u2550\u2550\u2550\u2557";
    //char middleRow[] =  "║   │   │   ║   │   │   ║   │   │   ║";
    char middleRow[] = "\u2551   \u2502   \u2502   \u2551   \u2502"
                       "   \u2502   \u2551   \u2502   \u2502   \u2551";
    // char middleRow2[] = "╟───┼───┼───╫───┼───┼───╫───┼───┼───╢";
    char middleRow2[] = "\u255f\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u253c"
                        "\u2500\u2500\u2500\u256b\u2500\u2500\u2500\u253c"
                        "\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u256b"
                        "\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u253c"
                        "\u2500\u2500\u2500\u2562";
    // char middleRow3[] = "╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣";
    char middleRow3[] = "\u2560\u2550\u2550\u2550\u256a\u2550\u2550\u2550\u256a"
                        "\u2550\u2550\u2550\u256c\u2550\u2550\u2550\u256a"
                        "\u2550\u2550\u2550\u256a\u2550\u2550\u2550\u256c"
                        "\u2550\u2550\u2550\u256a\u2550\u2550\u2550\u256a"
                        "\u2550\u2550\u2550\u2563";
    // char botRow[] =     "╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝";
    char botRow[] = "\u255a\u2550\u2550\u2550\u2567\u2550\u2550\u2550\u2567"
                    "\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2567"
                    "\u2550\u2550\u2550\u2567\u2550\u2550\u2550\u2569"
                    "\u2550\u2550\u2550\u2567\u2550\u2550\u2550\u2567"
                    "\u2550\u2550\u2550\u255d";
    int middle = (nc_col - SIZE) / 2;
    mvprintw(3, middle, "%s", topRow);
    for (auto i = 0; i < 3; i++) {
        mvprintw(4 + 6*i, middle, "%s", middleRow);
        mvprintw(5 + 6*i, middle, "%s", middleRow2);
        mvprintw(6 + 6*i, middle, "%s", middleRow);
        mvprintw(7 + 6*i, middle, "%s", middleRow2);
        mvprintw(8 + 6*i, middle, "%s", middleRow);
        if (i != 2)
            mvprintw(9 + 6*i, middle, "%s", middleRow3);
    }
    mvprintw(21, middle, "%s", botRow);

    // Print instructions
    mvprintw(7, middle + SIZE + 8, "k");
    mvprintw(9, middle + SIZE + 5, "h");
    mvprintw(9, middle + SIZE + 11, "l");
    mvprintw(11, middle + SIZE + 8, "j");
    attron(A_UNDERLINE);
    mvaddch(15, middle + SIZE + 5, 'i');
    attroff(A_UNDERLINE);
    printw("nsert");
    attron(A_UNDERLINE);
    mvaddch(16, middle + SIZE + 5, 'p');
    attroff(A_UNDERLINE);
    printw("encil");
    attron(A_UNDERLINE);
    mvaddch(17, middle + SIZE + 5, 'q');
    attroff(A_UNDERLINE);
    printw("uit");

    // Adding numbers to the grid
    int x = middle + 2;
    int y = 4;
    attron(A_BOLD);
    for (auto &ar : grid) {
        for (auto num : ar) {
            char ch = num + '0';
            if (ch > '0') {
                mvaddch(y, x, ch);
            }
            x = x + 4;
        }
        x = middle + 2;
        y += 2;
    }
    attroff(A_BOLD);

    // Move cursor to first box
    move(4, middle+2);

    bool insertMode = true;
    while(true) {
        getyx(stdscr, y,x);
        move(22, middle);
        clrtoeol();
        if (insertMode) {
            printw("Insert mode");
        }
        else {
            printw("Pencil mode");
        }
        move(y, x);
        refresh();
        int top = 4;
        int bot = 20;
        int left = middle + 2;
        int right = middle + 2 + 32;
        char ch = getch();
        switch(ch) {
        // Move left
        case 'h':
            if (x - 4 >= left) {
                move(y, x-4);
            }
            break;
        // Move down
        case 'j':
            if (y + 2 <= bot) {
                move(y+2, x);
            }
            break;
        // Move up
        case 'k':
            if (y - 2 >= top) {
                move(y-2, x);
            }
            break;
        // Move right
        case 'l':
            if (x + 4 <= right) {
                move(y, x+4);
            }
            break;
        // Input
        case 'i':
            insertMode = true;
            break;
        // Pencil
        case 'p':
            insertMode = false;
            break;
        // Quit
        case 'q':
            endwin();
            return 0;
        }
        if ((ch > '0' && ch <= '9') || ch == KEY_BACKSPACE || ch == ' ') {
            int row = calcRow(x, y, middle);
            int col = calcCol(x, y);
            if (insertMode) {
                input(grid, solution, ch, pencilMarks[col][row], row, col);
            }
            else if (grid[col][row] != solution[col][row]){
                // Only draw pencil marks if correct value is not present
                pencil(pencilMarks[col][row], ch);
            }
            move(y, x);
            refresh();
        }

        if (grid == solution) {
            // Player has won
            move(22, middle);
            clrtoeol();
            printw("Winner, winner, chicken dinner!");
            move(y, x);
            refresh();
            break;
        }
    }
    getch();
    endwin();
}