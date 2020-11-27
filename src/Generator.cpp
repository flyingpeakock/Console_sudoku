#include "Generator.h"
#include <array>
#include <algorithm>
#include <random>
#include <chrono>

#define SIZE 9

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

    if (maxUnknowns == 0)
        maxUnknowns = 81;
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
