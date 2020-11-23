#include "Generator.h"
#include <array>
#include <algorithm>
#include <random>
#include <chrono>

#define SIZE 9

Generator::Generator() {

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

    for (auto cell: cells) {
        grid[cell.row][cell.col] = 0;
        solver = Solver(grid);
        solver.solve();
        if (!solver.isUnique()) {
            // Removal of value does not produce unique solution
            // Put it back
            grid[cell.row][cell.col] = cell.val;
        }
    }
}


std::array<std::array<int, 9>, 9> Generator::getGrid() {
    return grid;
}

std::array<std::array<int, 9>, 9> Generator::getSolution() {
    return solver.getGrid();
}
