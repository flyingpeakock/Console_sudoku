#include "Generator.h"
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <string.h>
#include <stdexcept>

#define SIZE 9

Generator::Generator():Generator(81){};

Generator::Generator(const char *gridString) {
    if (strlen(gridString) != 81)
        throw std::invalid_argument("Wrong amount of digits for a sudoku puzzle");
    
    auto idx = 0;
    for (auto i = 0; i < 9; i++) {
        for (auto j = 0; j < 9; j++) {
            grid[i][j] = gridString[idx++] - '0';
        }
    }
    solver = Solver(gridString);
    solver.solve();
}

Generator::Generator(int maxUnknowns) {

    struct Cell
    {
        int row;
        int col;
        int val;
    };
    

    solver = Solver();
    solver.solve();
    grid = solver.getGrid();

    std::array<Cell, SIZE*SIZE> cells;
    int count = 0;
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            cells[count].row = i;
            cells[count].col = j;
            cells[count].val = grid[i][j];
            count++;
        }
    }

    // Shuffle array to randomly remove positions
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (cells.begin(), cells.end(), std::default_random_engine(seed));

    int unknowns = 0;
    for (auto cell: cells) {
        grid[cell.row][cell.col] = 0;
        solver = Solver(grid);
        solver.solve();
        if (!solver.isUnique()) {
            // Removal of value does not produce unique solution
            // Put it back
            grid[cell.row][cell.col] = cell.val;
        }
        else
            unknowns++;
        if (unknowns == maxUnknowns)
            break;
    }

    // Solve again incase last removal broke the puzzle
    solver = Solver(grid);
    solver.solve();
}


std::array<std::array<int, 9>, 9> Generator::getGrid() {
    return grid;
}

std::array<std::array<int, 9>, 9> Generator::getSolution() {
    return solver.getGrid();
}
