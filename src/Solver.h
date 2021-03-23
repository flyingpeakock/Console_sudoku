#pragma once
#include <array>

class Solver {
    private:
        std::array<std::array<int, 9>, 9> grid;
        std::array<std::array<int, 9>, 9> solution;
        bool isSafe(int row, int col, int num);
        bool backtrack(int row, int col);
        int solutions;
    public:
        Solver();
        Solver(int board[9][9]);
        Solver(int **board);
        Solver(std::array<std::array<int, 9>, 9> board);
        Solver(const char *board);
        std::array<std::array<int, 9>, 9> getGrid();
        void solve();
        bool isUnique();
        void changeGrid(int **board);
};