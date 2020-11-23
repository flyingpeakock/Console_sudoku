#include <iostream>
#include "Generator.h"

#define SIZE 9

int main() {
    // Test grid for checking uniqueness
    int board[9][9] = {
        {0,6,0,0,5,0,4,0,0},
        {1,0,0,0,0,9,5,0,0},
        {4,0,8,0,0,0,0,6,2},
        {0,8,6,0,0,0,0,7,0},
        {0,0,1,0,0,0,0,4,0},
        {0,0,0,8,7,0,0,0,0},
        {0,0,0,9,2,3,0,1,0},
        {0,3,0,5,4,0,0,2,0},
        {0,0,0,0,0,0,0,0,0}
    };


    Generator gen;
    auto grid = gen.getGrid();
    auto solution = gen.getSolution();
    std::cout << "Generated board\n";
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Solution\n";
    for (auto i = 0; i < SIZE; i++) {
        for (auto j = 0; j < SIZE; j++) {
            std::cout << solution[i][j] << ' ';
        }
        std::cout << '\n';
    }
}