#include "Solver.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <string.h>
#include <stdexcept>

#define SIZE 9

Solver::Solver() {
    solutions = 0;
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

Solver::Solver(int board[9][9]) {
    solutions = 0;
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            grid[i][j] = board[i][j];
        }
    }
}

Solver::Solver(int **board) {
    solutions = 0;
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            grid[i][j] = board[i][j];
        }
    }
}

Solver::Solver(std::array<std::array<int, 9>, 9> board) {
    solutions = 0;
    grid = board;
}

Solver::Solver(const char *board) {
    solutions = 0;
    auto idx = 0;
    if (strlen(board) != 81)
        throw std::invalid_argument("Wrong amount of digits to make a 9x9 sudoku");
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            grid[i][j] = board[idx++] - '0';
        }
    }
}

std::array<std::array<int, 9>, 9> Solver::getGrid() {
    return solution;
}

bool Solver::isSafe(int row, int col, int num) {

    // Check for same numb in same row
    for (auto i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) return false;
    }

    // Check for same numb in same col
    for (auto i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) return false;
    }

    // Check for same numb in same box
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (auto i = boxRow; i < boxRow + 3; i++) {
        for (auto j = boxCol; j < boxCol + 3; j++) {
            if (grid[i][j] == num) return false;
        }
    }
    
    return true; // All checks passed
}


bool Solver::backtrack(int row, int col) {
    // Has reached the end of the board, return true
    if (row == SIZE - 1 && col == SIZE) {
        solutions++;
        solution = grid;
        return true;
    }

    // Recahed the end of row, go to next
    if (col == SIZE) {
        col = 0;
        row++;
    }

    // Position already has value, go to next
    if (grid[row][col] > 0) {
        return backtrack(row, col + 1);
    }

    // Here comes the fun part
    // Create array with randomness instead of normal loop
    // used to generate unique puzzles
    std::array<int, 9> nums {1,2,3,4,5,6,7,8,9};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (nums.begin(), nums.end(), std::default_random_engine(seed));

    //for (auto num = 1; num <= SIZE; num++) {
    for (auto num : nums) {
        // Check if safe to place num
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (backtrack(row, col + 1) && solutions > 1)
            //if (backtrack(row, col +1))
                return true;
        }
    }
    // Number was wrong, reset
    grid[row][col] = 0;
    return false;
}

void Solver::solve() {
    backtrack(0, 0);
}

bool Solver::isUnique() {
    return solutions == 1;
}